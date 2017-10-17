#include <xc.h>
#include "trak32.h"
#include "trakaccel.h"
#include "trakhardware.h"

//lowest level accel/mangnetometer SPI functions
void initAccelSPI(void)
{
    SPI2CONbits.ON = 0;     //disable SPI module
    SPI2CON = 0x00;
    SPI2BRG = 0x20;     //24MHz Fpb = 6MHz SPI clock, accel max clk = 10MHz
        
    SPI2CONbits.SMP = 0;
    SPI2CONbits.CKE = 1;
    SPI2CONbits.CKP = 1;
    SPI2CONbits.MSTEN = 1;
    SPI2CONbits.ON = 1;     //enable SPI module
}

void accelRead(uint8 regAddress, uint8 numBytes, uint8* buffer)
{
    uint8 index;
    uint8 delay;
    
    regAddress = regAddress | 0x80;
    //regAddress = 0xF8;
    SPI_ACCEL_CS = ACCEL_CS_ENABLE;
    SPI2BUF = regAddress;
    while(!SPI2STATbits.SPIBUSY);
   
    for(index = 0; index < numBytes; index++)   //read requested number of bytes
    {
        SPI2BUF = 0x00;   
        while(!SPI2STATbits.SPIBUSY); 
        //for(delay = 0; delay < 254; delay++);
        //while(!SPI2STATbits.SPIRBF);
        buffer[index] = SPI2BUF;
    }
    SPI_ACCEL_CS = ACCEL_CS_DISABLE;       
}

void accelWrite(uint8 regAddress, uint8 numBytes, uint8* buffer)
{
    uint8 index;
    
    SPI_ACCEL_CS = ACCEL_CS_ENABLE;
    SPI2BUF = regAddress;
    while(!SPI2STATbits.SPIBUSY);
   
    for(index = 0; index < numBytes; index++)   //read requested number of bytes
    {
        SPI2BUF = buffer[index];
        while(!SPI2STATbits.SPIBUSY); 
    }
    SPI_ACCEL_CS = ACCEL_CS_DISABLE;      
}

void magRead(uint8 regAddress, uint8 numBytes, uint8* buffer)
{
    uint8 index;
    
    regAddress = regAddress + 0x80;
   
    SPI_MAG_CS = ACCEL_CS_ENABLE;
    SPI2BUF = regAddress;
    while(!SPI2STATbits.SPIBUSY);
   
    for(index = 0; index < numBytes; index++)   //read requested number of bytes
    {
        SPI2BUF = 0x00;   
        while(!SPI2STATbits.SPIBUSY); 
        buffer[index] = SPI2BUF;
    }
    SPI_MAG_CS = ACCEL_CS_DISABLE;       
}

void magWrite(uint8 regAddress, uint8 numBytes, uint8* buffer)
{
    uint8 index;
    
    SPI_MAG_CS = ACCEL_CS_ENABLE;
    SPI2BUF = regAddress;
    while(!SPI2STATbits.SPIBUSY);
   
    for(index = 0; index < numBytes; index++)   //read requested number of bytes
    {
        SPI2BUF = buffer[index];
        while(!SPI2STATbits.SPIBUSY); 
    }
    SPI_MAG_CS = ACCEL_CS_DISABLE;      
}

//accel/magnetometer tests
RETURN_T accelTest(void)
{
    uint8 accelData[2];
   
    initAccelSPI();
    accelRead(ACCEL_REG_WHO_AM_I, 0x01, accelData);
    if(accelData[0] == ACCEL_WHO_AM_I_ID)
    {
        return RETURN_SUCCESS;
    }
    else
    {
        return RETURN_ERROR;        
    }           
}

RETURN_T magTest(void)
{
    uint8 magData[2];
   
    initAccelSPI();
    magRead(MAG_REG_WHO_AM_I_M, 0x01, magData);
    if(magData[0] == MAG_WHO_AM_I_ID)
    {
        return RETURN_SUCCESS;
    }
    else
    {
        return RETURN_ERROR;        
    }           
}


//functions to read accel/gyro/magnetometer values