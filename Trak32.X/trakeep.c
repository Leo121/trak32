#include <xc.h>
#include "trak32.h"
#include "trakhardware.h"
#include "trakeep.h"

#define SPI_CS_EEP SPI_SPARE1_CS

void spiEEPcs(EEP_SELECT_T eepNum, uint8 csPinState);

void initEEPspi(void)
{
    SPI2CONbits.ON = 0;     //enable SPI module
    SPI2BRG = 0x08;     //24MHz Fpb = 12MHz SPI clock
        
    SPI2CONbits.SMP = 0;
    SPI2CONbits.CKE = 0;
    SPI2CONbits.CKP = 0;
    SPI2CONbits.MSTEN = 1;
    SPI2CONbits.ON = 1;     //enable SPI module
}

void spiEEPread(EEP_SELECT_T eepNum, uint16 endingAddressOffset, uint16 beginningAddress, uint8 *databuffer)
{       
    uint16 index;
    uint8 command[4];
   
    initEEPspi();
   
    command[0] = EEP_READ_COMMAND;
    command[1] = 0x00;
    command[2] = beginningAddress >> 8;
    command[3] = beginningAddress & 0x00FF;
   
    //SPI_CS_EEP = EEP_CS_ENABLE;
    spiEEPcs(eepNum, EEP_CS_ENABLE);
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
    //SPI_CS_EEP = EEP_CS_DISABLE;   
    spiEEPcs(eepNum, EEP_CS_DISABLE);
}

void spiEEPwrite(EEP_SELECT_T eepNum, uint16 endingAddressOffset, uint16 beginningAddress, uint8 *databuffer)
{
    uint16 index;
    uint8 command[4];
    uint8 status;
   
    initEEPspi();

    command[0] = EEP_WRITE_COMMAND;
    command[1] = 0x00;
    command[2] = beginningAddress >> 8;
    command[3] = beginningAddress & 0x00FF;

    //SPI_CS_EEP = EEP_CS_ENABLE;      
    spiEEPcs(eepNum, EEP_CS_ENABLE);
    SPI2BUF = EEP_WREN_COMMAND;
    while(!SPI2STATbits.SPIBUSY);
    //SPI_CS_EEP = EEP_CS_DISABLE;               //chip select has to be released for write enable latch
    spiEEPcs(eepNum, EEP_CS_DISABLE);
           
    //SPI_CS_EEP = EEP_CS_ENABLE;      
    spiEEPcs(eepNum, EEP_CS_ENABLE);
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
    //SPI_CS_EEP = EEP_CS_DISABLE;             //chip select has to be released for write to occur
    spiEEPcs(eepNum, EEP_CS_DISABLE);

    status = 0x01;
    //SPI_CS_EEP = EEP_CS_ENABLE;      
    spiEEPcs(eepNum, EEP_CS_ENABLE);
    while(status && 0x01)
    {
        SPI2BUF = EEP_RDSR_COMMAND;
        while(!SPI2STATbits.SPIBUSY);
        SPI2BUF = 0x00;   
        while(!SPI2STATbits.SPIBUSY); 
        status = SPI2BUF;
    }
    //SPI_CS_EEP = EEP_CS_DISABLE;
    spiEEPcs(eepNum, EEP_CS_DISABLE);
}


void spiEEPpageErase(EEP_SELECT_T eepNum, uint16 beginningAddress)
{
    uint8 command[4];
    uint8 status;
   
    initEEPspi();

    command[0] = EEP_PE_COMMAND;
    command[1] = 0x00;
    command[2] = beginningAddress >> 8;
    command[3] = beginningAddress & 0x00FF;

    //SPI_CS_EEP = EEP_CS_ENABLE;      
    spiEEPcs(eepNum, EEP_CS_ENABLE);
    SPI2BUF = EEP_WREN_COMMAND;
    while(!SPI2STATbits.SPIBUSY);
    //SPI_CS_EEP = EEP_CS_DISABLE;               //chip select has to be released for write enable latch
    spiEEPcs(eepNum, EEP_CS_DISABLE);

    status = 0x01;
    //SPI_CS_EEP = EEP_CS_ENABLE;      
    spiEEPcs(eepNum, EEP_CS_ENABLE);
    while(status && 0x01)
    {
        SPI2BUF = EEP_RDSR_COMMAND;
        while(!SPI2STATbits.SPIBUSY);
        SPI2BUF = 0x00;   
        while(!SPI2STATbits.SPIBUSY); 
        status = SPI2BUF;
    }
    //SPI_CS_EEP = EEP_CS_DISABLE;
    spiEEPcs(eepNum, EEP_CS_DISABLE);      
}

uint16 blockToAddress(uint8 blockNumber)
{
    return blockNumber * 256;
}

RETURN_T eepTest(EEP_SELECT_T eepNum)
{
    uint8 status;
   
    initEEPspi();
    //SPI_CS_EEP = EEP_CS_ENABLE;      
    spiEEPcs(eepNum, EEP_CS_ENABLE);
    SPI2BUF = EEP_RDSR_COMMAND;
    while(!SPI2STATbits.SPIBUSY);
    SPI2BUF = 0x00;   
    while(!SPI2STATbits.SPIBUSY); 
    status = SPI2BUF;
    //SPI_CS_EEP = EEP_CS_DISABLE;
    spiEEPcs(eepNum, EEP_CS_DISABLE);
    if(status == 0xFF)
    {
        return RETURN_ERROR;
    }
    else
    {
        return RETURN_SUCCESS;
    }
}

void spiEEPcs(EEP_SELECT_T eepNum, uint8 csPinState)
{
    switch(eepNum)
    {
        case EEP_1:
            SPI_SPARE1_CS = csPinState;
            break;
        case EEP_2:
            SPI_SPARE2_CS = csPinState;
            break;
        default:
            break;
    }
    
}