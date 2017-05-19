/* 
 * File:   trakLEDs.h
 * Author: KMW
 *
 * Created on January 21, 2017, 4:19 PM
 */

#ifndef TRAKLEDS_H
#define	TRAKLEDS_H

#ifdef	__cplusplus
extern "C" {
#endif


typedef enum{
    LED_STATE_OFF = 0,
    LED_STATE_ON = 1,
    LED_TOGGLE,
    LED_BAD_STATE = 0xFF
}LED_STATE;

typedef enum{
    LED_1,
    LED_2,
    LED_3,
    LED_4
}LED_HW;

extern LED_STATE SetLED(LED_HW LEDnum, LED_STATE LEDstate, uint16 LEDontime);
extern LED_STATE ReadLED(LED_HW LEDnum);



#ifdef	__cplusplus
}
#endif

#endif	/* TRAKLEDS_H */

