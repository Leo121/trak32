/* 
 * File:   trakeep.h
 * Author: KMW
 *
 * Created on May 6, 2017, 9:57 AM
 */

#ifndef TRAKEEP_H
#define	TRAKEEP_H

#ifdef	__cplusplus
extern "C" {
#endif

#define EEP_CS_ENABLE   0
#define EEP_CS_DISABLE  1    
    
    
//see page 7 of 25AA1024 datasheet
#define EEP_READ_COMMAND    0b00000011      //read
#define EEP_WRITE_COMMAND   0b00000010      //write
#define EEP_WREN_COMMAND    0b00000110      //write enable
#define EEP_WRDI_COMMAND    0b00000100      //write disable
#define EEP_RDSR_COMMAND    0b00000101      //read status register
#define EEP_WRSR_COMMAND    0b00000001      //write status register
#define EEP_PE_COMMAND      0b01000010      //page erase
#define EEP_SE_COMMAND      0b11011000      //sector erase
#define EEP_CE_COMMAND      0b11000111      //chip erase
#define EEP_RDID_COMMAND    0b10101011      //relase from deep power down/read ESN
#define EEP_DPD_COMMAND     0b10111001      //deep power down
   
extern void initEEPspi(void);
extern void spiEEPread(uint16 endingAddressOffset, uint16 beginningAddress, uint8 *databuffer);
extern void spiEEPwrite(uint16 endingAddressOffset, uint16 beginningAddress, uint8 *databuffer);
extern uint16 blockToAddress(uint8 blockNumber);
extern void spiEEPpageErase(uint16 beginningAddress);

#ifdef	__cplusplus
}
#endif

#endif	/* TRAKEEP_H */

