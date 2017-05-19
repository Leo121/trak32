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

extern uint16 boardTemperature;
extern uint16 rhMotorTemperature;
extern uint16 lhMotorTemperature;
extern uint16 ambientLightLevel;
extern uint16 vbat1;
extern uint16 vbat2;
        
extern uint16 readADCbyChannel(uint8 channel);
extern void readBoardTemp(void);
extern void readRHmotorTemp(void);
extern void readLHmotorTemp(void);
extern void readLightSensor(void);
extern void readVbat1(void);
extern void readVbat2(void);

extern void calculateTemperature(uint16 tempADC);
extern void calculateVbat1(uint16 vbat1ADC);
extern void calculateVbat2(uint16 vbat2ADC);
extern void calculateLightLevel(uint16 lightADC);

extern void InitializeADC(void);
extern void SelectAnalogChannel(uint8 SelectChannel);    
extern uint16 MeasureAnalogInputs(void);
void SampleDelay(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TRAKADC_H */

