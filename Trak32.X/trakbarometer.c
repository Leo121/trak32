#include <xc.h>
#include "trakhardware.h"
#include "trakbarometer.h"


union{
    uint16 a0;
    uint16 b1;
    uint16 b2;
    uint16 c12; 
    uint8 buffer[8];
}barometerCoefficents;

union{
    uint16 pressureADC;
    uint16 temperatureADC;
    uint8 buffer[4];
}barometerResults;


uint8 readCoefCommands[8] = {0x88, 0x8A, 0x8C, 0x8E, 0x90, 0x92, 0x94, 0x96};
uint8 readBaroADCcommands[4] = {BARO_CMD_READ_PRES_H, BARO_CMD_READ_PRES_L, BARO_CMD_READ_TEMP_H, BARO_CMD_READ_TEMP_L};

float currentBarometricPressure;
float currentAirTemperature;        //datasheet does not specify temp ADC to degrees coefficient

void initBarometerSPI(void)
{
//spi port
    SPI_CLK_TRIS = 0;
    SPI_MOSI_TRIS = 0;
    SPI_MISO_TRIS = 1;
//spi barometric sensor select
    SPI_BARO_CS_TRIS = 0;
        
    SPI2BRG = 0x03;     //24MHz Fpb = 6MHz SPI clock, barometer max clk = 8MHz
        
    SPI2CONbits.SMP = 1;
    SPI2CONbits.CKE = 1;
    SPI2CONbits.CKP = 1;
    SPI2CONbits.MSTEN = 1;
    SPI2CONbits.ON = 1;     //enable SPI module
}

PERIPHERAL_STATUS_T checkBarometer(void)
{
    readBarometerCoefficents();
    if(barometerCoefficents.a0 == 0xFFFF)
    {
       barometerStatus = PERIPHERAL_ERROR; 
    }
    else
    {
       barometerStatus = PERIPHERAL_OK; 
    }
    return barometerStatus;
}


void readBarometerCoefficents(void)
{
    uint8 index;
    
    SPI_BARO_CS = 0;
    for(index = 0; index < sizeof(readCoefCommands); index++)
    {
        barometerCoefficents.buffer[index] = simpleCommandReadSPI(readCoefCommands[index]);
    }    
    SPI_BARO_CS = 1;
}

void readBarometer(void)
{
    uint8 index;
    
    SPI_BARO_CS = 0;
    simpleCommandReadSPI(BARO_CMD_CONVERT);
    SPI_BARO_CS = 1;

//start conversion takes 1.6ms
    
    SPI_BARO_CS = 0;
    for(index = 0; index < sizeof(readBaroADCcommands); index++)
    {
        barometerResults.buffer[index] = simpleCommandReadSPI(readBaroADCcommands[index]);
    }    
    SPI_BARO_CS = 0;
    
}

void calculateBarometerPressureTemp(void)
{
    float a0, b1, b2, c12;
    //convert coefficients to floats
    //
    a0 = convertBaroFPvalueToFloat(barometerCoefficents.a0, BARO_COEF_A0_INT, BARO_COEF_A0_FRAC, BARO_COEF_A0_ZEROPAD);
    b1 = convertBaroFPvalueToFloat(barometerCoefficents.b1, BARO_COEF_B1_INT, BARO_COEF_B1_FRAC, BARO_COEF_B1_ZEROPAD);
    b2 = convertBaroFPvalueToFloat(barometerCoefficents.b2, BARO_COEF_B2_INT, BARO_COEF_B2_FRAC, BARO_COEF_B2_ZEROPAD);
    c12 = convertBaroFPvalueToFloat(barometerCoefficents.c12, BARO_COEF_C12_INT, BARO_COEF_C12_FRAC, BARO_COEF_C12_ZEROPAD);
    currentBarometricPressure = a0 + (b1 + c12 * barometerResults.temperatureADC) * barometerResults.pressureADC + b2 * barometerResults.temperatureADC;
    
    currentBarometricPressure = currentBarometricPressure * (115-50/1023) + 50;
}

void getBarometerReading(void)
{
    initBarometerSPI();
    readBarometerCoefficents();
    readBarometer();
    calculateBarometerPressureTemp();
}

float convertBaroFPvalueToFloat(uint16 baroValue, uint8 numInt, uint8 numFrac, uint8 zeroPad)
{
    float returnvalue = 0;
    float sign = 1;
    float fraction = 2;
    uint8 index;
    uint16 baroHold;
    
    if(baroValue && 0x80)
    {
        sign = -1;
        baroValue ^= 0x7F;
    }
    
    baroHold = baroValue;
    
    for(index = 0; index < (numFrac + zeroPad); index++)
    {
        fraction = fraction * 2;
    }
    
    for(index = 0; index < numFrac; index++)
    {
        if(baroValue && 0x01)
        {
            returnvalue = returnvalue + 1/fraction;
        }
        fraction = fraction / 2;
        
        baroValue = baroValue >> 1;
    }
        
    if(numInt > 0)
    {
        baroHold = baroHold >> (numFrac + zeroPad);
        returnvalue = returnvalue + baroHold;
    }

    returnvalue = returnvalue * sign;    
    
    return returnvalue;
}

