#include <xc.h>
#include "trakhardware.h"
#include "trakLEDs.h"


LED_STATE SetLED(LED_HW LEDnum, LED_STATE LEDstate, uint16 LEDontime)
{
    LED_STATE SetLEDreturn = LED_BAD_STATE;
    
    switch(LEDstate)
    {
        case LED_STATE_ON:
            switch(LEDnum)
            {
                case LED_1:
                    LED_ONB1 = LED_ON;
                    SetLEDreturn = LED_ON;
                    break;
                case LED_2:
                    LED_ONB2 = LED_ON;
                    SetLEDreturn = LED_ON;
                    break;
                case LED_3:
                    LED_PI1 = LED_ON;
                    SetLEDreturn = LED_ON;
                    break;
                case LED_4:
                    LED_PI2 = LED_ON;
                    SetLEDreturn = LED_ON;
                    break;                    
            }
            break;
            
        case LED_STATE_OFF:
            switch(LEDnum)
            {
                case LED_1:
                    LED_ONB1 = LED_OFF;
                    SetLEDreturn = LED_OFF;
                    break;
                case LED_2:
                    LED_ONB2 = LED_OFF;
                    SetLEDreturn = LED_OFF;
                    break;
                case LED_3:
                    LED_PI1 = LED_OFF;
                    SetLEDreturn = LED_OFF;
                    break;
                case LED_4:
                    LED_PI2 = LED_OFF;
                    SetLEDreturn = LED_OFF;
                    break;
            }   
            break;
        
        case LED_TOGGLE:        
            switch(LEDnum)
            {
                case LED_1:
                    LED_ONB1 = LED_ON;
//                    fToggleLED1 = TRUE;
//                    LED1ToggleCounts = LEDontime;
                    SetLEDreturn = LED_TOGGLE;
                    break;
                case LED_2:
                    LED_ONB2 = LED_ON;
//                    fToggleLED2 = TRUE;
//                    LED2ToggleCounts = LEDontime;
                    SetLEDreturn = LED_TOGGLE;
                    break;
                case LED_3:
                    LED_PI1 = LED_ON;
//                    fToggleLED3 = TRUE;
//                    LED3ToggleCounts = LEDontime;
                    SetLEDreturn = LED_TOGGLE;
                    break;
                case LED_4:
                    LED_PI2 = LED_ON;
//                    fToggleLED4 = TRUE;
//                    LED4ToggleCounts = LEDontime;
                    SetLEDreturn = LED_TOGGLE;
                    break;                
            }
            break;

    }
    
    return SetLEDreturn;
}


LED_STATE ReadLED(LED_HW LEDnum)
{
    LED_STATE ReadLEDreturn;
    
    switch(LEDnum)
    {
        case LED_1:
            if(LED_ONB1_PORT == LED_OFF)
            {
                ReadLEDreturn = LED_OFF;
            }
            else
            {
                ReadLEDreturn = LED_ON;
            }
            break;
            
        case LED_2:
            if(LED_ONB2_PORT == LED_OFF)
            {
                ReadLEDreturn = LED_OFF;
            }
            else
            {
                ReadLEDreturn = LED_ON;
            }
            break;
 
        case LED_3:
            if(LED_PI1_PORT == LED_OFF)
            {
                ReadLEDreturn = LED_OFF;
            }
            else
            {
                ReadLEDreturn = LED_ON;
            }
            break;

        case LED_4:
            if(LED_PI2_PORT == LED_OFF)
            {
                ReadLEDreturn = LED_OFF;
            }
            else
            {
                ReadLEDreturn = LED_ON;
            }
            break;

        default:
            ReadLEDreturn = LED_BAD_STATE;
            break;
    }
    
    return ReadLEDreturn;
}


