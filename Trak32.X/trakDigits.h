/* 
 * File:   trakDigits.h
 * Author: KMW
 *
 * Created on May 10, 2017, 11:06 PM
 */

#ifndef TRAKDIGITS_H
#define	TRAKDIGITS_H

#ifdef	__cplusplus
extern "C" {
#endif

//header file for STP16DPP LED digit driver

    
#define PFE_VERSION
        
#ifdef PFE_VERSION

//left digit connections are:    E D C G DP F B A 
#define cLDIGIT_0	0b11100111
#define cLDIGIT_1	0b00100010
#define cLDIGIT_2	0b11010011
#define cLDIGIT_3	0b01110011
#define cLDIGIT_4	0b00110110
#define cLDIGIT_5	0b01110101
#define cLDIGIT_6	0b11110101
#define cLDIGIT_7	0b00100011
#define cLDIGIT_8	0b11110111
#define cLDIGIT_9	0b00110111

#define cLDIGIT_DP	0b00001000

//right digit connections are:    B A F DP G C D E 
#define cRDIGIT_0	0b11100111
#define cRDIGIT_1	0b10000100
#define cRDIGIT_2	0b11001011
#define cRDIGIT_3	0b11001110
#define cRDIGIT_4	0b10101100
#define cRDIGIT_5	0b01101110
#define cRDIGIT_6	0b01101111
#define cRDIGIT_7	0b11000100
#define cRDIGIT_8	0b11101111
#define cRDIGIT_9	0b11101100

#define cRDIGIT_DP	0b00010000



#elif TSSOP_LED

//left digit connections are:   MSB C DP D E G F B A LSB
#define cLDIGIT_0	0b10110111
#define cLDIGIT_1	0b10000010
#define cLDIGIT_2	0b00111011
#define cLDIGIT_3	0b10101011
#define cLDIGIT_4	0b01110010
#define cLDIGIT_5	0b10110110
#define cLDIGIT_6	0b10111110
#define cLDIGIT_7	0b11000010
#define cLDIGIT_8	0b11111110
#define cLDIGIT_9	0b11110010

#define cLDIGIT_DP	0b01000000

//right digit connections are:   MSB G DP F A B C D E LSB
#define cRDIGIT_0	0b00111111
#define cRDIGIT_1	0b00001100
#define cRDIGIT_2	0b10011011
#define cRDIGIT_3	0b10011110
#define cRDIGIT_4	0b10101100
#define cRDIGIT_5	0b10110110
#define cRDIGIT_6	0b10110111
#define cRDIGIT_7	0b00011100
#define cRDIGIT_8	0b10111111
#define cRDIGIT_9	0b10111100

#define cRDIGIT_DP	0b01000000


#else

//left digit connections are:   MSB E D C DP G F A B LSB
#define cLDIGIT_0	0b11100111
#define cLDIGIT_1	0b10000100
#define cLDIGIT_2	0b11001011
#define cLDIGIT_3	0b11001110
#define cLDIGIT_4	0b10110100
#define cLDIGIT_5	0b01110110
#define cLDIGIT_6	0b01110111
#define cLDIGIT_7	0b11000100
#define cLDIGIT_8	0b11110111
#define cLDIGIT_9	0b11110100

#define cLDIGIT_DP	0b00001000

//right digit connections are:   MSB B A F DP G C D E LSB
//right digit connections are:   MSB E D C G DP F A B LSB			this is the correct one
#define cRDIGIT_0	0b11100111
#define cRDIGIT_1	0b00100001
#define cRDIGIT_2	0b11010011
#define cRDIGIT_3	0b01110011
#define cRDIGIT_4	0b00110101
#define cRDIGIT_5	0b01110110
#define cRDIGIT_6	0b11110110
#define cRDIGIT_7	0b00100011
#define cRDIGIT_8	0b11110111
#define cRDIGIT_9	0b00110111

#define cRDIGIT_DP	0b00001000


#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TRAKDIGITS_H */

