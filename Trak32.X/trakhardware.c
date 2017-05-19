#include <p32xxxx.h>
#include <plib.h>
#include <xc.h>
#include "trakhardware.h"
#include "common.h"


uint16 DelayTicks;
uint32 SystemTicks = 0;

void InitializeHardware(void)
{
    DDPCONbits.JTAGEN = 0;
    DDPCONbits.TROEN = 0;
    
//PPS    
//    CFGCONbits.IOLOCK = 0;      //clear to allow writes to port select registers
//    U2RXR = 0b0011;     //U2RX pin per page 240 of family datasheet
//    RPB14R = 0b0010;    //U2TX pin per page 244 of family datasheet
//    RPF1R = 0b1011;     //RF1 = OC3
//    RPF0R = 0b1011;     //RF0 = OC4
//    RPD1R = 0b1011;     //RD1 = OC2
//    RPD0R = 0b1100;     //RD0 = OC1 -- sound PWM            
//    CFGCONbits.IOLOCK = 1;      //set to lock it

    AD1PCFG = 0xFFFF;

    LED_ONB1 = 0;
    LED_ONB2 = 0;
    LED_ONB1_TRIS = 0;
    LED_ONB2_TRIS = 0;
    
    COLOR_SENSE_LED_TRIS = 0;
        
    InitializeTimer3();
    InitializeUART2();          //UART2 -- debug
    InitializeUART1();          //UART1 -- Pi

//    InitializeADC();
//    InitializeLEDPWMs();
//    InitializeSoundPWM();
    
 
}



void DelayByCounts(uint16 delayValue)
{
    DelayTicks = delayValue;
    while(DelayTicks > 0);    
}


void InitializeSoundPWM(void)
{
    OC1CON = 0x0000; // Turn off the OC1 when performing the setup
    OC1R = 0x007F; // Initialize primary Compare register
    OC1RS = 0x007F; // Initialize secondary Compare register
    OC1CON = 0x0006; // Configure for PWM mode without Fault pin
    OC1CONSET = 0x8000; // Enable OC1
}


//void SelectAnalogChannel(uint8 SelectChannel)
//{
//    switch(SelectChannel)
//    {
//        case 1:
//        	SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN3 |  ADC_CH0_NEG_SAMPLEB_NVREF); // configure to sample AN4 & AN5
//            break;
//        case 2:
//        	SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN2 |  ADC_CH0_NEG_SAMPLEB_NVREF); // configure to sample AN4 & AN5
//            break;
//        case 3:
//            SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN4 |  ADC_CH0_NEG_SAMPLEB_NVREF); // configure to sample AN4 & AN5
//            break;
//        case 4:
//            SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN5 |  ADC_CH0_NEG_SAMPLEB_NVREF); // configure to sample AN4 & AN5
//            break;
//        default:
//            break;
//    }
//}



uint16 ADCRead(void)
{
    uint16 tempdata;

    //TODO -- ADC code        
    AD1CON1bits.SAMP = 1;
    AD1CON1bits.DONE = FALSE;   /* Ensure Persistent bits are cleared */
    IFS1CLR = 0x0002;
    while(!AD1CON1bits.DONE);   /* Wait for conversion to be completed */
    tempdata = ADC1BUF0;    /* Read ADC Buffer */
    AD1CON1bits.DONE = FALSE;   /* Clear Persistent bits */
    IFS1CLR = 0x0002;

    return tempdata;
}

uint8 simpleCommandReadSPI(uint8 command)
{
    SPI2BUF = command;
    while(!SPI2STATbits.SPIBUSY);
    SPI2BUF = 0x00;
    while(!SPI2STATbits.SPIBUSY);
    return SPI2BUF;
}

void readSPIcommand(uint8 cmdLen, uint8 *cmdBuffer, uint8 dataLen, uint8 * dataBuffer)
{
    uint16 index;
    
    for(index = 0; index < cmdLen; index++)      //send read command and address
    {
        SPI2BUF = cmdBuffer[index];
        while(!SPI2STATbits.SPIBUSY);
    }
    
    for(index = 0; index < dataLen; index++)
    {
        SPI2BUF = 0x00;
        while(!SPI2STATbits.SPIBUSY);
        dataBuffer[index] = SPI2BUF;
    }    
}

void writeSPIcommand(uint8 cmdLen, uint8 *cmdBuffer, uint8 dataLen, uint8 * dataBuffer)
{
    uint16 index;
    
    for(index = 0; index < cmdLen; index++)      //send read command and address
    {
        SPI2BUF = cmdBuffer[index];
        while(!SPI2STATbits.SPIBUSY);
    }
    
    for(index = 0; index < dataLen; index++)
    {
        SPI2BUF = dataBuffer[index];
        while(!SPI2STATbits.SPIBUSY);
    }        
}