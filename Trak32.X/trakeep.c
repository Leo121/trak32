#include <xc.h>
#include "trak32.h"
#include "trakhardware.h"
#include "trakeep.h"

#define SPI_CS_EEP SPI_SPARE1_CS

void initEEPspi(void)
{
    SPI2BRG = 0x00;     //24MHz Fpb = 12MHz SPI clock
        
    SPI2CONbits.SMP = 1;
    SPI2CONbits.CKE = 1;
    SPI2CONbits.CKP = 1;
    SPI2CONbits.MSTEN = 1;
    SPI2CONbits.ON = 1;     //enable SPI module
}

void spiEEPread(uint16 endingAddressOffset, uint16 beginningAddress, uint8 *databuffer)
{       
    uint16 index;
    uint8 command[4];
   
    initEEPspi();
   
    command[0] = EEP_READ_COMMAND;
    command[1] = 0x00;
    command[2] = beginningAddress >> 8;
    command[3] = beginningAddress & 0x00FF;
   
    SPI_CS_EEP = EEP_CS_ENABLE;
    for(index = 0; index < 4; index++)      //send read command and address
    {
        SPI2BUF = command[index];
        while(!SPI2STATbits.SPIBUSY);
    }
   
    for(index = 0; index < endingAddressOffset + 1; index++)   //read requested number of bytes
    {
        SPI2BUF = 0x00;   
        while(!SPI2STATbits.SPIBUSY); 
        databuffer[index] = SPI2BUF;
    }
    SPI_CS_EEP = EEP_CS_DISABLE;   
}

void spiEEPwrite(uint16 endingAddressOffset, uint16 beginningAddress, uint8 *databuffer)
{
    uint16 index;
    uint8 command[4];
    uint8 status;
   
    initEEPspi();

    command[0] = EEP_WRITE_COMMAND;
    command[1] = 0x00;
    command[2] = beginningAddress >> 8;
    command[3] = beginningAddress & 0x00FF;

    SPI_CS_EEP = EEP_CS_ENABLE;      
    SPI2BUF = EEP_WREN_COMMAND;
    while(!SPI2STATbits.SPIBUSY);
    SPI_CS_EEP = EEP_CS_DISABLE;               //chip select has to be released for write enable latch
           
    SPI_CS_EEP = EEP_CS_ENABLE;      
    for(index = 0; index < 4; index++)
    {
        SPI2BUF = command[index];
        while(!SPI2STATbits.SPIBUSY);
    }
    for(index = 0; index < endingAddressOffset + 1; index++)
    {
        SPI2BUF = databuffer[index];
        while(!SPI2STATbits.SPIBUSY); 
    }   
    SPI_CS_EEP = EEP_CS_DISABLE;             //chip select has to be released for write to occur

    status = 0x01;
    SPI_CS_EEP = EEP_CS_ENABLE;      
    while(status && 0x01)
    {
        SPI2BUF = EEP_RDSR_COMMAND;
        while(!SPI2STATbits.SPIBUSY);
        SPI2BUF = 0x00;   
        while(!SPI2STATbits.SPIBUSY); 
        status = SPI2BUF;
    }
    SPI_CS_EEP = EEP_CS_DISABLE;
}


void spiEEPpageErase(uint16 beginningAddress)
{
    uint8 command[4];
    uint8 status;
   
    initEEPspi();

    command[0] = EEP_PE_COMMAND;
    command[1] = 0x00;
    command[2] = beginningAddress >> 8;
    command[3] = beginningAddress & 0x00FF;

    SPI_CS_EEP = EEP_CS_ENABLE;      
    SPI2BUF = EEP_WREN_COMMAND;
    while(!SPI2STATbits.SPIBUSY);
    SPI_CS_EEP = EEP_CS_DISABLE;               //chip select has to be released for write enable latch
           
    status = 0x01;
    SPI_CS_EEP = EEP_CS_ENABLE;      
    while(status && 0x01)
    {
        SPI2BUF = EEP_RDSR_COMMAND;
        while(!SPI2STATbits.SPIBUSY);
        SPI2BUF = 0x00;   
        while(!SPI2STATbits.SPIBUSY); 
        status = SPI2BUF;
    }
    SPI_CS_EEP = EEP_CS_DISABLE;
   
   
}

uint16 blockToAddress(uint8 blockNumber)
{
    return blockNumber * 256;
}

