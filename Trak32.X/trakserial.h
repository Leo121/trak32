/* 
 * File:   trakserial.h
 * Author: KMW
 *
 * Created on January 13, 2017, 1:57 PM
 */

#ifndef TRAKSERIAL_H
#define	TRAKSERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TX1_BUFFER_LENGTH   127
#define RX1_BUFFER_LENGTH   127    
#define TX2_BUFFER_LENGTH   127    
#define RX2_BUFFER_LENGTH   127    

typedef enum
{
    RECEIVING_DATA,
    RECEIVED_COMMAND
}RX_DATA_STATE_T;
    
extern unsigned char TX1buffer[];
extern unsigned char TX1ptr;
extern unsigned char TX1length;
extern unsigned char TX1enabled;

extern unsigned char RX1buffer[];
extern unsigned char RX1ptr;
extern unsigned char RX1mode;
extern unsigned char RX1packetlength;
extern RX_DATA_STATE_T RX1DataFlag;

extern unsigned char TX2buffer[];
extern unsigned char TX2ptr;
extern unsigned char TX2length;
extern unsigned char TX2enabled;

extern unsigned char RX2buffer[];
extern unsigned char RX2inputptr;
extern unsigned char RX2mode;
extern unsigned char RX2packetlength;
extern RX_DATA_STATE_T RX2DataFlag;    
    
    
    
extern void InitializeUART1(void);
extern void InitializeUART2(void);
    
extern void kickU1TX(void);
extern void kickU2TX(void);    



#ifdef	__cplusplus
}
#endif

#endif	/* TRAKSERIAL_H */

