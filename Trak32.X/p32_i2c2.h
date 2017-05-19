#ifndef P32_I2C2_H
#define P32_I2C2_H

#include "GenericTypeDefs.h"
#include "common.h"


//#define SYS_CLOCK 32000000
#define FCL        400000 // Check the max speed supported by your peripheral!!

#define GetSystemClock() (SYS_CLOCK)
#define GetPeripheralClock() (SYS_CLOCK) //if FPBDIV = DIV_1, check this
#define GetInstructionClock() (SYS_CLOCK)

extern void drvI2C2Init(void);
extern BOOL drvI2C2ReadRegisters(uint8 reg, uint8* rxPtr, uint8 len, uint8 slave_adr);
extern BOOL drvI2C2WriteRegisters(uint8 reg, uint8* data, uint8 len, uint8 slave_adr);
extern BOOL drvI2C2WriteByte(uint8 reg, uint8 byte, uint8 slave_adr);
extern BOOL drvI2C2ReadByte(uint8 reg, uint8* byte, uint8 slave_adr);

#endif
