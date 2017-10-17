/* 
 * File:   trakaccel.h
 * Author: KMW
 *
 * Created on May 6, 2017, 12:29 PM
 */

#ifndef TRAKACCEL_H
#define	TRAKACCEL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "common.h"    
    
#define ACCEL_CS_ENABLE   0
#define ACCEL_CS_DISABLE  1    
    
//accelerometer SPI register addresses
#define    ACCEL_REG_ACT_THS    0x04
#define    ACCEL_REG_ACT_DUR    0x05 
#define    ACCEL_REG_INT_GEN_CFG_XL    0x06
#define    ACCEL_REG_INT_GEN_THS_X_XL    0x07
#define    ACCEL_REG_INT_GEN_THS_Y_XL    0x08
#define    ACCEL_REG_INT_GEN_THS_Z_XL    0x09
#define    ACCEL_REG_INT_GEN_DUR_XL    0x0A
#define    ACCEL_REG_REFERENCE_G    0x0B
#define    ACCEL_REG_INT1_CTRL    0x0C
#define    ACCEL_REG_INT2_CTRL    0x0D
#define    ACCEL_REG_WHO_AM_I    0x0F
#define    ACCEL_REG_CTRL_REG1_G    0x10
#define    ACCEL_REG_CTRL_REG2_G    0x11
#define    ACCEL_REG_CTRL_REG3_G    0x12
#define    ACCEL_REG_ORIENT_CFG_G    0x13
#define    ACCEL_REG_INT_GEN_SRC_G    0x14
#define    ACCEL_REG_OUT_TEMP_L    0x15
#define    ACCEL_REG_OUT_TEMP_H    0x16
#define    ACCEL_REG_STATUS_REG_1    0x17
#define    ACCEL_REG_OUT_X_L_G    0x18
#define    ACCEL_REG_OUT_X_H_G    0x19
#define    ACCEL_REG_OUT_Y_L_G    0x1A
#define    ACCEL_REG_OUT_Y_H_G    0x1B
#define    ACCEL_REG_OUT_Z_L_G    0x1C
#define    ACCEL_REG_OUT_Z_H_G    0x1D
#define    ACCEL_REG_CTRL_REG4    0x1E
#define    ACCEL_REG_CTRL_REG5_XL    0x1F
#define    ACCEL_REG_CTRL_REG6_XL    0x20
#define    ACCEL_REG_CTRL_REG7_XL    0x21
#define    ACCEL_REG_CTRL_REG8    0x22
#define    ACCEL_REG_CTRL_REG9    0x23
#define    ACCEL_REG_CTRL_REG10    0x24
#define    ACCEL_REG_INT_GEN_SRC_XL    0x26
#define    ACCEL_REG_STATUS_REG_2    0x27
#define    ACCEL_REG_OUT_X_L_XL    0x28
#define    ACCEL_REG_OUT_X_H_XL    0x29
#define    ACCEL_REG_OUT_Y_L_XL    0x2A
#define    ACCEL_REG_OUT_Y_H_XL    0x2B
#define    ACCEL_REG_OUT_Z_L_XL    0x2C
#define    ACCEL_REG_OUT_Z_H_XL    0x2D
#define    ACCEL_REG_FIFO_CTRL    0x2E
#define    ACCEL_REG_FIFO_SRC    0x2F
#define    ACCEL_REG_INT_GEN_CFG_G    0x30
#define    ACCEL_REG_INT_GEN_THS_XH_G    0x31 
#define    ACCEL_REG_INT_GEN_THS_XL_G    0x32 
#define    ACCEL_REG_INT_GEN_THS_YH_G    0x33 
#define    ACCEL_REG_INT_GEN_THS_YL_G     0x34 
#define    ACCEL_REG_INT_GEN_THS_ZH_G    0x35 
#define    ACCEL_REG_INT_GEN_THS_ZL_G    0x36 
#define    ACCEL_REG_INT_GEN_DUR_G    0x37 


//magnetomer SPI register addresses
#define    MAG_REG_OFFSET_X_REG_L_M    0x05 
#define    MAG_REG_OFFSET_X_REG_H_M    0x06
#define    MAG_REG_OFFSET_Y_REG_L_M    0x07
#define    MAG_REG_OFFSET_Y_REG_H_M    0x08
#define    MAG_REG_OFFSET_Z_REG_L_M    0x09
#define    MAG_REG_OFFSET_Z_REG_H_M    0x0A
#define    MAG_REG_WHO_AM_I_M    0x0F
#define    MAG_REG_CTRL_REG1_M    0x20
#define    MAG_REG_CTRL_REG2_M    0x21
#define    MAG_REG_CTRL_REG3_M    0x22
#define    MAG_REG_CTRL_REG4_M    0x23
#define    MAG_REG_CTRL_REG5_M    0x24
#define    MAG_REG_STATUS_REG_M    0x27
#define    MAG_REG_OUT_X_L_M    0x28
#define    MAG_REG_OUT_X_H_M    0x29
#define    MAG_REG_OUT_Y_L_M    0x2A
#define    MAG_REG_OUT_Y_H_M    0x2B
#define    MAG_REG_OUT_Z_L_M    0x2C
#define    MAG_REG_OUT_Z_H_M    0x2D
#define    MAG_REG_INT_CFG_M    0x30
#define    MAG_REG_INT_SRC_M    0x31
#define    MAG_REG_INT_THS_L_M    0x32
#define    MAG_REG_INT_THS_H_M    0x33

    
//accel/magnetometer ID    
#define ACCEL_WHO_AM_I_ID   0x68    
#define MAG_WHO_AM_I_ID     0x3D
    
extern void initAccelSPI(void);
extern void accelRead(uint8 regAddress, uint8 numBytes, uint8* buffer);
extern void accelWrite(uint8 regAddress, uint8 numBytes, uint8* buffer);
extern void magRead(uint8 regAddress, uint8 numBytes, uint8* buffer);
extern void magWrite(uint8 regAddress, uint8 numBytes, uint8* buffer);

extern RETURN_T accelTest(void);
extern RETURN_T magTest(void);

//readAccels();
//readGyros();
//readMagnetometer();


#ifdef	__cplusplus
}
#endif

#endif	/* TRAKACCEL_H */

