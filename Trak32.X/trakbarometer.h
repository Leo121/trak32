/* 
 * File:   trakbarometer.h
 * Author: KMW
 *
 * Created on May 4, 2017, 10:13 PM
 */

#ifndef TRAKBAROMETER_H
#define	TRAKBAROMETER_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#define BARO_CMD_CONVERT        0x24
#define BARO_CMD_READ_PRES_H    0x80
#define BARO_CMD_READ_PRES_L    0x82
#define BARO_CMD_READ_TEMP_H    0x84
#define BARO_CMD_READ_TEMP_L    0x86
#define BARO_CMD_READ_COEF      0x88

#define BARO_COEF_A0_FRAC       3
#define BARO_COEF_B1_FRAC       13
#define BARO_COEF_B2_FRAC       14
#define BARO_COEF_C11_FRAC      11
#define BARO_COEF_C12_FRAC      13   
#define BARO_COEF_C22_FRAC      10

#define BARO_COEF_A0_INT        12
#define BARO_COEF_B1_INT        2
#define BARO_COEF_B2_INT        1
#define BARO_COEF_C11_INT       0
#define BARO_COEF_C12_INT       0   
#define BARO_COEF_C22_INT       0

#define BARO_COEF_A0_ZEROPAD    0
#define BARO_COEF_B1_ZEROPAD    0
#define BARO_COEF_B2_ZEROPAD    0
#define BARO_COEF_C11_ZEROPAD   11
#define BARO_COEF_C12_ZEROPAD   9   
#define BARO_COEF_C22_ZEROPAD   15

    
extern uint8 readCoefCommands[];

extern float currentBarometricPressure;
extern float currentAirTemperature;
    
extern void initBarometerSPI(void);

extern void readBarometerCoefficents(void);
extern void readBarometer(void);
extern void calculateBarometerPressureTemp(void);
extern void getBarometerReading(void);
extern float convertBaroFPvalueToFloat(uint16 baroValue, uint8 numInt, uint8 numFrac, uint8 zeroPad);

#ifdef	__cplusplus
}
#endif

#endif	/* TRAKBAROMETER_H */

