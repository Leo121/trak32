//-----------------------------------------------------------------------------
//
//  Generic i2c driver
//
//  Author: Govind Mukundan
//
//
//  ********************************* HISTORY ********************************
//
//  Version : 1.0
//  Date :
//  Description: Initial version
//
//
//-----------------------------------------------------------------------------

#include <xc.h>
#include "common.h"
#include "p32_i2c2.h"

static void I2C2Idle(void);
static BOOL I2C2Start(void);
static void I2C2Stop(void);
static BOOL I2C2SendByte(uint8 data);


void drvI2C2Init(void) 
{
    uint16 temp = 0;
    I2C2CON = 0; // reset bits to 0
    I2C2CONbits.I2CEN = 0; // disable module
    I2C2BRG = (GetPeripheralClock() / FCL) - (GetPeripheralClock() / 10000000) - 1; //Formula from datasheet
    //I2C2BRG = ((SSMGetCurrentPeripheralClock() / (2 * Fsck)) - 1);
    I2C2STAT = 0;
    I2C2CONbits.I2CSIDL = 1; // dont operate in idle mode
    //I2C2CONbits.SCLREL = 1;
    I2C2CONbits.I2CEN = 1; // enable module
    temp = I2C2RCV; // clear RBF flag
}



static void I2C2Idle(void) 
{
    uint8 t = 255;
    /* Wait until I2C Bus is Inactive */
    while (I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN ||
            I2C2CONbits.RSEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT || t--);
}

static BOOL I2C2Start(void) 
{
    // wait for module idle
    I2C2Idle();
    // Enable the Start condition
    I2C2CONbits.SEN = 1;

    // Check for collisions
    if (I2C2STATbits.BCL) 
    {
        return (FALSE);
    }
    else 
    {
        // wait for module idle
        I2C2Idle();
        return (TRUE);
    }
}

static void I2C2Stop(void) 
{
    int x = 0;
    // wait for module idle
    I2C2Idle();
    //initiate stop bit
    I2C2CONbits.PEN = 1;

    //wait for hardware clear of stop bit
    while (I2C2CONbits.PEN) 
    {
        if (x++ > 50) break;
    }
    I2C2CONbits.RCEN = 0;
    // IFS1bits.MI2C1IF = 0; // Clear Interrupt
    I2C2STATbits.IWCOL = 0;
    I2C2STATbits.BCL = 0;
    // wait for module idle
    I2C2Idle();
}

BOOL I2C2SendByte(uint8 data) 
{
    //while(I2C2STATbits.TBF); //Wait till data is transmitted.
    // Send the byte
    I2C2TRN = data;

    // Check for collisions
    if ((I2C2STATbits.IWCOL == 1)) 
    {
        return (FALSE);
    } 
    else 
    {
        while (I2C2STATbits.TRSTAT); // wait until write cycle is complete
        if ((I2C2STATbits.BCL == 1)) 
        {
            return (FALSE);
        }
        else 
        {
            // wait for module idle
            I2C2Idle();
            return (TRUE);
        }
    }
}


/**
 * @brief Read data from an I2C slave
 *
 * This function can be used to read one or more sequential registers from a slave.
 * To read multiple registers, the slave must support multi-byte reads.
 *
 * @param reg The register to start reading from (uint8)
 * @param rxPtr A pointer to where the read data should be stored (uint8*)
 * @param len Number of bytes/registers to read
 * @param slave_adr The 7 bit address of the slave without the R/W bits set
 * @return Boolean indicating if operation completed successfully or not
 */
BOOL drvI2C2ReadRegisters(uint8 reg, uint8* rxPtr, uint8 len, uint8 slave_adr) 
{
    uint8 i, flag, ret, j;
    
    flag = 0;
    ret = FALSE;
    for (i = 0; i < 100; i++) // wait for ACK for some time
    {
        //1. i2c start
        I2C2Start();
        //2. Set Slave in W Mode
        I2C2SendByte((slave_adr << 1) | 0);
        //3. Check ACK
        I2C2Idle();
        if (I2C2STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            flag = 1;
            break;
        }
    }

    if (!flag) return FALSE; // Exit if there was a problem
    flag = 0;
    // 4.if write cmd was successful, put the regno on the bus
    I2C2SendByte(reg);
    if (I2C2STATbits.ACKSTAT != 0) // Did we receive an ACK ?
    {
        return FALSE; // Exit if there was a problem
    }
    // Now that the register address is setup, we can ask the slave to enter read mode.
    for (j = 0; j < 100; j++) {
        //5.Issue a repeated start = a start cond without a prior stop
        I2C2Start();
        //6. Set Slave in R mode
        I2C2SendByte((slave_adr << 1) | 1);
        //7. Check ACK
        if (I2C2STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            flag = 1;
            break;
        }
    }

    if (!flag) return FALSE; // Exit if there was a problem

    for (i = 0; i < len; i++) //read all the bytes
    {
        I2C2Idle();
        // got the ack, processor is in read mode
        //8. read the register
        I2C2CONbits.RCEN = 1; // enable master read
        while (I2C2CONbits.RCEN); // wait for byte to be received !(I2C2STATbits.RBF)

        I2C2Idle();
        I2C2STATbits.I2COV = 0;
        *(rxPtr + i) = I2C2RCV;

        if ((i + 1) == len) {
            //9. Generate a NACK on last byte
            I2C2CONbits.ACKDT = 1; // send nack
            I2C2CONbits.ACKEN = 1;
            //10. generate a stop
            I2C2Stop();
        } else {
            I2C2CONbits.ACKDT = 0; // send ACK for sequential reads
            I2C2CONbits.ACKEN = 1;
        }

        ret = TRUE;
    }
    return ret;
}

/**
 * @brief Write data into an I2C slave
 *
 * This function can be used to write one or more sequential registers from a slave.
 * To write multiple registers, the slave must support multi-byte writes.
 *
 * @param reg The register to start writing to (uint8)
 * @param rxPtr A pointer to where the data should be fetched from (uint8*)
 * @param len Number of bytes/registers to write
 * @param slave_adr The 7 bit address of the slave without the R/W bits set
 *
 * @return Boolean indicating if operation completed successfully or not
 */
BOOL drvI2C2WriteRegisters(uint8 adr, uint8* data, uint8 len, uint8 slave_adr) {
    uint8 i, flag, j;
    flag = 0;
    for (i = 0; i < 100; i++) {
        //1. i2c start
        I2C2Start();
        //2. Set  in W Mode
        I2C2SendByte((slave_adr << 1) | 0);
        //3. Check ACK
        I2C2Idle();
        if (I2C2STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            flag = 1;
            break;
        }
    }

    if (!flag) return (FALSE); // Exit if there was a problem
    // 4.if write cmd was successful, put the adress on the bus
    I2C2SendByte(adr);
    I2C2Idle();
    for (j = 0; j < len; j++) {
        if (I2C2STATbits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            I2C2SendByte(*(data + j));
        }
        else 
        {
            return FALSE;
        }
    }
    I2C2Stop();

    return TRUE;

}

/**
 * @brief A wrapper around drvI2C2WriteRegisters() to write only a byte of data
 *
 * @param reg The register to start reading from (uint8)
 * @param byte The byte to write
 * @param slave_adr The 7 bit address of the slave without the R/W bits set
 * @return Boolean indicating if operation completed successfully or not
 */
BOOL drvI2C2WriteByte(uint8 reg, uint8 byte, uint8 slave_adr) 
{
    return (drvI2C2WriteRegisters(reg, &byte, 1, slave_adr));
}

/**
 * @brief A wrapper around drvI2C2ReadRegisters() to write only a byte of data
 *
 * @param reg The register to start reading from (uint8)
 * @param byte The byte to write
 * @param slave_adr The 7 bit address of the slave without the R/W bits set
 * @return Boolean indicating if operation completed successfully or not
 */
BOOL drvI2C2ReadByte(uint8 reg, uint8* byte, uint8 slave_adr) 
{
    return (drvI2C2ReadRegisters(reg, byte, 1, slave_adr));
}


//extern BOOL drvI2C2ReadRegisters(uint8 reg, uint8* rxPtr, uint8 len, uint8 slave_adr);

