/* 
 * File:   trakADC.h
 * Author: KMW
 *
 * Created on May 7, 2017, 12:02 AM
 */

#ifndef TRAKADC_H
#define	TRAKADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ADC_VREF        3.3
#define ADC_MAX_COUNTS  1023

#define TEMP_V_OFFSET   0.500
#define TEMP_V_PER_DEGC 0.010
    
#define ADC_CH2_GAIN        2
#define ADC_CH3_GAIN        2    
#define ADC_CH4_GAIN        2    
#define ADC_CH5_GAIN        1    
#define ADC_CH10_GAIN       1    
#define ADC_CH11_GAIN       1    
#define ADC_CH6_GAIN        1    
#define ADC_CH7_GAIN        1    
#define ADC_CH8_GAIN        1    
#define ADC_CH9_GAIN        1    
    
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
    
    
extern uint16 boardTemperature;
extern uint16 rhMotorTemperature;
extern uint16 lhMotorTemperature;
extern uint16 ambientLightLevel;
extern uint16 vbat1;
extern uint16 vbat2;
        
extern uint16 readADCbyChannel(uint8 channel);
extern void readADCvoltageChannel(uint8 channel, float* result);
extern void readBoardTemp(float* result);
extern void readRHmotorTemp(float* result);
extern void readLHmotorTemp(float* result);
extern void voltageToTemp(float voltage, float* result);
extern void readLightSensor(void);
extern void readVbat1(void);
extern void readVbat2(void);

extern void calculateTemperature(uint16 tempADC);
extern void calculateVbat1(uint16 vbat1ADC);
extern void calculateVbat2(uint16 vbat2ADC);
extern void calculateLightLevel(uint16 lightADC);

extern uint8 gainFromADCchannel(uint8 adcChannel);

extern void InitializeADC(void);
extern void SelectAnalogChannel(uint8 SelectChannel);    
extern uint16 MeasureAnalogInputs(void);
void SampleDelay(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TRAKADC_H */

