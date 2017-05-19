//#include <p32xxxx.h>
//#include <plib.h>
#include <xc.h>
//#include "hardware.h"
#include "trakhardware.h"
#include "common.h"
#include "p32_i2c2.h"
#include "TCS34725.h"


BOOL _tcs34725Initialised = FALSE;
tcs34725Gain_t _tcs34725Gain = TCS34725_GAIN_16X;
tcs34725IntegrationTime_t _tcs34725IntegrationTime = TCS34725_INTEGRATIONTIME_2_4MS;


BOOL MeasureColor(LED_STATE_T colorSenseLEDstate, RGBC_COLOR_T *colorRGBC)
{    
    BOOL retvalue = FALSE;
    uint16 red = 0;
    uint16 green = 0;
    uint16 blue = 0;
    uint16 clear = 0;
    
    COLOR_SENSE_LED = colorSenseLEDstate;
    DelayByCounts(3);    //insert short delay?    
    retvalue = TCS34725getRawData(&red, &green, &blue, &clear);
    colorRGBC->red16value = red;
    colorRGBC->green16value = green;
    colorRGBC->blue16value = blue;
    colorRGBC->clear16value = blue;

    COLOR_SENSE_LED = LED_OFF;    
    
    return retvalue;
}




BOOL TCS34725initialize(void)
{           
    uint8 idTCS34725;
    BOOL Success = TRUE;
    
      /* Make sure we're actually connected */
    drvI2C2Init();
    Success = TCS34725readbyte(TCS34725_ID, &idTCS34725);
    if(Success)
    {
        if ((idTCS34725 != 0x44) && (idTCS34725 != 0x10))
        {
            Success = FALSE;
        }
        else
        {
            Success = TCS34725setIntegrationTime(_tcs34725IntegrationTime);
            Success = TCS34725setGain(_tcs34725Gain);
            Success = TCS34725enable();

            _tcs34725Initialised = TRUE;
        }
    }
    else
    {
        Success = FALSE;
    }
    
    return Success;
}

BOOL TCS34725setIntegrationTime(tcs34725IntegrationTime_t it)
{
  /* Update the timing register */
    TCS34725writebyte(TCS34725_ATIME, it);
//
//  /* Update value placeholders */
  _tcs34725IntegrationTime = it;
//    
}

BOOL TCS34725setGain(tcs34725Gain_t gain)
{
//  /* Update the timing register */
    TCS34725writebyte(TCS34725_CONTROL, gain);
//
//  /* Update value placeholders */
  _tcs34725Gain = gain;
//}
    
}

BOOL TCS34725getRawData(uint16 *r, uint16 *g, uint16 *b, uint16 *c)
{
    BOOL retvalue = FALSE;

    if (!_tcs34725Initialised) TCS34725initialize();
    
    retvalue = TCS34725readuint16(TCS34725_CDATAL, c);
    retvalue = TCS34725readuint16(TCS34725_RDATAL, r);
    retvalue = TCS34725readuint16(TCS34725_GDATAL, g);
    retvalue = TCS34725readuint16(TCS34725_BDATAL, b);
    
    return retvalue;    
}

BOOL TCS34725enable(void)
{
    BOOL retvalue = TRUE;
    retvalue = TCS34725writebyte(TCS34725_ENABLE, TCS34725_ENABLE_PON);
    DelayByCounts(1);
    retvalue = TCS34725writebyte(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);  
    return retvalue;
}

BOOL TCS34725disable(void)
{
    BOOL retvalue = TRUE;
    uint8 reg = 0;
    retvalue = TCS34725readbyte(TCS34725_ENABLE, &reg);
    retvalue = TCS34725writebyte(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
    return retvalue;    
}


//Specific handlers for TCS34725
BOOL TCS34725writebyte(uint8 reg, uint8 data)
{
//    uint8 i2cData[10], ctrlreg, databyte;
//    I2C_7_BIT_ADDRESS SlaveAddress;
    
    // Initialize the data buffer
//    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, TCS34725_ADDRESS, I2C_WRITE);
    
    
    return drvI2C2WriteByte((TCS34725_COMMAND_BIT | reg), data, TCS34725_ADDRESS);

//    i2cData[0] = SlaveAddress.byte;
//    i2cData[1] = (TCS34725_COMMAND_BIT | reg);
//    i2cData[2] = data;
//
//    return WriteI2CBytes(i2cData, 3);    
}


BOOL TCS34725readbyte(uint8 reg, uint8* data)
{
//    BOOL Success;    
//    uint8 i2cbuffer[2];
//    I2C_7_BIT_ADDRESS SlaveAddress;
//
//    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, TCS34725_ADDRESS, I2C_WRITE);    
//    i2cbuffer[0] = SlaveAddress.byte;
//    i2cbuffer[1] = TCS34725_COMMAND_BIT | reg;

    return drvI2C2ReadByte((TCS34725_COMMAND_BIT | reg), data, TCS34725_ADDRESS);
//    return Success;
}

BOOL TCS34725readuint16(uint8 reg, uint16 *data)
{
    BOOL Success; 
    union{
        uint8 i2cdata8[2];
        uint16 i2cdata16;
    }read16i2c;
    
    uint8 i2cbuffer[2];
    
//    I2C_7_BIT_ADDRESS SlaveAddress;
//
//    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, TCS34725_ADDRESS, I2C_READ);    
//    i2cbuffer[0] = SlaveAddress.byte;
//    i2cbuffer[1] = TCS34725_COMMAND_BIT | reg;
    
    Success = drvI2C2ReadRegisters((TCS34725_COMMAND_BIT | reg), i2cbuffer, 2, TCS34725_ADDRESS);
    if(Success)
    {
        read16i2c.i2cdata8[0] = i2cbuffer[0];
        read16i2c.i2cdata8[1] = i2cbuffer[1];
    }
    
    *data = read16i2c.i2cdata16;
    
    return Success;    
}
