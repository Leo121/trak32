/* 
 * File:   common.h
 * Author: KMW
 *
 * Created on January 13, 2017, 4:21 PM
 */

#ifndef TRAKINTS_H
#define	TRAKINTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MASTER_COUNT_TICKS  50
#define ANALOG_SAMPLE_TICKS 75    
    
    
extern uint16 MasterStateCtr;
extern uint16 AnalogSampleCtr;



extern void InitializeInterrupts(void);   

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

