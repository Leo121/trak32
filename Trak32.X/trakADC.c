#include <xc.h>
#include "GenericTypeDefs.h"
#include "common.h"
#include "trakhardware.h"
#include "trakADC.h"

//analog globals
uint16 boardTemperature;
uint16 rhMotorTemperature;
uint16 lhMotorTemperature;
uint16 ambientLightLevel;
uint16 vbat1;
uint16 vbat2;


//analog functions
uint16 readADCbyChannel(uint8 channel)
{
    SelectAnalogChannel(channel);
    return MeasureAnalogInputs();
}

void readADCvoltageChannel(uint8 channel, float* result)
{
    uint8 gain;
    float voltage;
    gain = gainFromADCchannel(channel);
    voltage = (float) readADCbyChannel(channel);
    voltage = (voltage/(float)ADC_MAX_COUNTS) * (float)ADC_VREF;
    voltage = voltage / gain;
    
    //return voltage;
    *result = voltage;
}

void readBoardTemp(float* result)
{
    SelectAnalogChannel(aONB_TEMP_CH);
    boardTemperature = MeasureAnalogInputs();        
}

void readRHmotorTemp(float* result)
{    
    SelectAnalogChannel(aRMOTOR_TEMP_CH);
    rhMotorTemperature = MeasureAnalogInputs();        
}

void readLHmotorTemp(float* result)
{
    SelectAnalogChannel(aLMOTOR_TEMP_CH);
    lhMotorTemperature = MeasureAnalogInputs();        
}

void voltageToTemp(float voltage, float* result)
{
    float tempInC = voltage - TEMP_V_OFFSET;
    tempInC = tempInC/TEMP_V_PER_DEGC;
    *result = tempInC;    
}


void readLightSensor(void)
{
    SelectAnalogChannel(aLIGHT_SENSE_CH);
    ambientLightLevel = MeasureAnalogInputs();            
}

void readVbat1(void)
{
    SelectAnalogChannel(aBAT1_CH);
    vbat1 = MeasureAnalogInputs();    
}

void readVbat2(void)
{
    SelectAnalogChannel(aBAT2_CH);
    vbat2 = MeasureAnalogInputs();
}


void calculateTemperature(uint16 tempADC)
{
    
}

void calculateVbat1(uint16 vbat1ADC)
{
    
}

void calculateVbat2(uint16 vbat2ADC)
{
    
}

void calculateLightLevel(uint16 lightADC)
{
    
}


void InitializeADC(void)
{
// Turn module on | ouput in integer | trigger mode auto | enable autosample
#define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG16 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON

            // ADC ref external    | disable offset test    | disable scan mode | perform 2 samples | use dual buffers | use alternate mode
#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_ON | ADC_ALT_INPUT_ON

// 				  use ADC internal clock | set sample time
#define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15

//               set AN2, AN3 and AN4 as analog inputs
#define PARAM4	ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN4_ANA

// do not assign channels to scan
#define PARAM5	SKIP_SCAN_ALL

    //initialization steps taken from PIC32Mxx datasheet, p503
//#define aONB_TEMP_CH            2
//#define aLMOTOR_TEMP_CH         3    
//#define aRMOTOR_TEMP_CH         4    
//#define aLIGHT_SENSE_CH         5    
//#define aBAT1_CH                10    
//#define aBAT2_CH                11    
//#define aSPARE1_CH              6    
//#define aSPARE2_CH              7    
//#define aSPARE3_CH              8    
//#define aSPARE4_CH              9    
    
    AD1PCFG = 0xF003;
            
                //select ADC MUX
                //select format
                //select sample clock
                //select Vref
                //select scan mode

	// configure and enable the ADC
    AD1CON1bits.ADON = 0;       //ADC should be off before changing settings
    AD1CON1 = 0x00E4;
    AD1CON2 = 0x20;
    SelectAnalogChannel(0);
//	OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using parameter define above
//
    AD1CON1bits.ADON = 1;       // Enable the ADC

}


void SelectAnalogChannel(uint8 SelectChannel)
{
    uint32 channel = SelectChannel << 16;
    AD1CHS = channel;
}

/***************************************************************************/
uint16 MeasureAnalogInputs(void)
{
    unsigned int tempdata;
    //unsigned int offset;

    AD1CON1bits.SAMP = 1;
    AD1CON1bits.DONE = FALSE;   /* Ensure Persistent bits are cleared */
    IFS1CLR = 0x0002;
    while(!AD1CON1bits.DONE);    /* Wait for conversion to be completed */
    tempdata = ADC1BUF0;        /* Read ADC Buffer */
    AD1CON1bits.DONE = FALSE;    /* Clear Persistent bits */
    IFS1CLR = 0x0002;
    return tempdata;
}


void SampleDelay(void)
{
	int i;
	for(i = 1; i < 50; i++)
	{
            Nop();
	}
}


uint8 gainFromADCchannel(uint8 adcChannel)
{
    uint8 gain;
    
    switch(adcChannel)
    {
        case 2:
            gain = ADC_CH2_GAIN;
            break;
        case 3:
            gain = ADC_CH3_GAIN;
            break;
        case 4:
            gain = ADC_CH4_GAIN;
            break;
        case 5:
            gain = ADC_CH5_GAIN;
            break;
        case 6:
            gain = ADC_CH6_GAIN;
            break;
        case 7:
            gain = ADC_CH7_GAIN;
            break;
        case 8:
            gain = ADC_CH8_GAIN;
            break;
        case 9:
            gain = ADC_CH9_GAIN;
            break;
        case 10:
            gain = ADC_CH10_GAIN;
            break;
        case 11:
            gain = ADC_CH11_GAIN;
            break;
        default:
            gain = BAD_STATE;
            break;
    }
    return gain;
}