/* 
 * File:   common.h
 * Author: KMW
 *
 * Created on January 13, 2017, 4:21 PM
 */

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif


    
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef short int16;
typedef int int32;
typedef long long int64;

//#ifndef TRUE
//#define TRUE 1
//#endif
//
//#ifndef FALSE
//#define FALSE 0
//#endif

typedef enum{
    RETURN_ERROR,
    RETURN_SUCCESS
}RETURN_T;

#define BAD_STATE 0xFF      //numerous hardware types may return a bad state, this will be 0xFF


//#define TRUE 1
//#define FALSE 0


#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

