
// Includes Section
#include "common.h"
#include "trakhardware.h"
#include <p32xxxx.h>
#include <plib.h>
#include <xc.h>
#include <stdio.h>
#include "trakserial.h"
#include "trakcommands.h"


// Configuration Section
#ifndef OVERRIDE_CONFIG_BITS

    #pragma config FMIIEN = OFF             // Ethernet RMII/MII Enable (RMII Enabled)
    #pragma config FETHIO = OFF             // Ethernet I/O Pin Select (Alternate Ethernet I/O)


    #pragma config UPLLEN   = OFF            // USB PLL Enabled
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLMUL  = MUL_24        // PLL Multiplier		was 16
    #pragma config FPLLODIV = DIV_4         // PLL Output Divider   was 1
        //8MHz / 2 * 24 / 4 = 24MHz

    //#pragma config FNOSC = FRCPLL              // Oscillator Selection Bits (Fast RC Osc with PLL)
    #pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc with PLL)

    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer 
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    //#pragma config POSCMOD  = OFF            // Primary Oscillator


    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable
    //#pragma config FNOSC    = PRIPLL        // Oscillator Selection
//    #pragma config FNOSC    = PRI        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = ON           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx1      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = ON           // Debugger Disabled for Starter Kit


#endif // OVERRIDE_CONFIG_BITS




/*************************************************************************
 Global Data
 *************************************************************************/



/*************************************************************************
 Main entry point
 *************************************************************************/
//#pragma code
int main(void)
{
    InitializeHardware();
    INTEnableSystemMultiVectoredInt();
    
    LED_ONB1 = 1;
    LED_ONB2 = 1;
    DelayByCounts(1000);
    LED_ONB1 = 1;
    LED_ONB2 = 0;    
    
    sprintf(TX2buffer, "Boot!\r\n");
    kickU2TX();
    
    while(1)
    {
        if(RX2DataFlag == RECEIVED_COMMAND)
        {
            //ParseU2Command();
            //ExtractCommand();
            memcpy(RXcmdbuffer, RX2buffer, RX2inputptr);
            RX2DataFlag = RECEIVING_DATA;
            RX2inputptr = 0;
            
            InterpretCommands(RXcmdbuffer);
            RX2DataFlag = RECEIVING_DATA;
        }
    }
}




/*************************************************************************
 general exception handler
 *************************************************************************/

void _general_exception_handler(unsigned cause, unsigned status)
{
    Nop();
    Nop();
}

/*************************************************************************
 Interrupts
 *************************************************************************/

///*************************************************************************
// Timer 3 ISR
//
// Used to de-bounce buttons
// *************************************************************************/
//
//void __ISR(_TIMER_3_VECTOR, ipl2) _T3Interrupt(void)
//{
////     BOOL NewState;
////     LEDTimer++;
//
//     // Clear the interrupt flag
//     mT3ClearIntFlag();
//
///*     // Debounce Mouse X Button
//     NewState = mGetMouseX() ? FALSE : TRUE;
//     if (NewState == MouseXPressed)
//         MouseXTimer   = 0;
//     else
//         MouseXTimer++;
//     if (MouseXTimer > BUTTON_DEBOUNCE_LIMIT)
//     {
//         MouseXPressed = NewState;
//         AnyKeyPressed = TRUE;
//     }
//
//     // Debounce Mouse Y Button
//     NewState = mGetMouseY() ? FALSE : TRUE;
//     if (NewState == MouseYPressed)
//         MouseYTimer   = 0;
//     else
//         MouseYTimer++;
//     if (MouseYTimer > BUTTON_DEBOUNCE_LIMIT)
//     {
//         MouseYPressed = NewState;
//         AnyKeyPressed = TRUE;
//     }
//
//     // Debounce Mouse Left Button
//     NewState = mGetMouseLeftButton() ? FALSE : TRUE;
//     if (NewState == MouseLeftPressed)
//         MouseLeftTimer   = 0;
//     else
//         MouseLeftTimer++;
//     if (MouseLeftTimer > BUTTON_DEBOUNCE_LIMIT)
//     {
//         MouseLeftPressed = NewState;
//         AnyKeyPressed    = TRUE;
//     }*/
//}
//

///*************************************************************************
// Change Notice ISR
//
// Used for remote wake up
// *************************************************************************/
//void __ISR(_CHANGE_NOTICE_VECTOR, ipl3) ChangeNotice_Handler(void)
//{
///*    unsigned int temp;
//
//    // clear the mismatch condition
//    temp = mPORTDRead();
//
//    // clear the interrupt flag
//    mCNClearIntFlag();
//
//    // Clear the suspended state
//    if ( Suspended && RemoteWakeEnabled )
//    {
//        Suspended = FALSE;
//        HIDSignalResume();
//
//    }*/
//}
//
///*************************************************************************
// USB ISR
//
// Necessary to wake up device when sleeping
// *************************************************************************/
//#ifdef SLEEP_WHEN_SUSPENDED
//    void __ISR(_USB1_VECTOR, ipl6) _USB1Interrupt(void)		//was 14, redundant with MiWi RX int
//    {
//        U1OTGIRbits.ACTVIF = 1;
//        U1OTGIEbits.ACTVIE = 0;
//        IFS1CLR = 0x02000000; // USBIF
//    }
//#endif






// We are taking Timer 3  to schedule input report transfers

// NOTE - The datasheet doesn't state this, but the timer does get reset to 0
// after a period register match.  So we don't have to worry about resetting
// the timer manually.

#define STOP_TIMER_IN_IDLE_MODE     0x2000
#define TIMER_SOURCE_INTERNAL       0x0000
#define TIMER_ON                    0x8000
#define GATED_TIME_DISABLED         0x0000
#define TIMER_16BIT_MODE            0x0000

#define TIMER_PRESCALER_1           0x0000
#define TIMER_PRESCALER_8           0x0010
#define TIMER_PRESCALER_64          0x0020
#define TIMER_PRESCALER_256         0x0030
#define TIMER_INTERRUPT_PRIORITY    0x0001


#define TIMER_PRESCALER             TIMER_PRESCALER_8   // 8MHz: TIMER_PRESCALER_1
//#define TIMER_PERIOD                50000                // 10ms=20000, 1ms=2000
#define TIMER_PERIOD                12000


/****************************************************************************
  Function:
     void InitializeTimer( void )

  Description:
    This function initializes the tick timer.  It configures and starts the
    timer, and enables the timer interrupt.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void InitializeTimer3(void)
{
    WORD timerPeriod;

    IPC3bits.T3IP = TIMER_INTERRUPT_PRIORITY;
    IFS0bits.T3IF = 0;

    TMR3 = 0;
    //timerPeriod = TIMER_PERIOD*(Appl_raw_report_buffer.ReportPollRate/MINIMUM_POLL_INTERVAL);
        // adjust the timer presaclar if poll rate is too high
        // 20000 counts correspond to 10ms , so current pre sacaler setting will
        // allow maximum 30ms poll interval
    PR3 = TIMER_PERIOD;
    T3CON = TIMER_ON | STOP_TIMER_IN_IDLE_MODE | TIMER_SOURCE_INTERNAL |
            GATED_TIME_DISABLED | TIMER_16BIT_MODE | TIMER_PRESCALER;

    IEC0bits.T3IE = 1;

}


void InitializeTimer4(void)
{
    //WORD timerPeriod;

    IPC4bits.T4IP = 3;
    IFS0bits.T4IF = 0;

    TMR4 = 0;
    //timerPeriod = TIMER_PERIOD*(Appl_raw_report_buffer.ReportPollRate/MINIMUM_POLL_INTERVAL);
        // adjust the timer presaclar if poll rate is too high
        // 20000 counts correspond to 10ms , so current pre scaler setting will
        // allow maximum 30ms poll interval
    //PR4 = TIMER_PERIOD;
    #ifdef EVENT_TIMER_100uS
    PR4 = 1500;         //100uS at 30MHz
    #elif defined EVENT_TIMER_10uS
    PR4 = 150;         //10uS at 30MHz
    #endif
    PR4 = 3000;
	//PR4 = timerPeriod * 20;			//I think this is what they meant....     -KMW
    T4CON = TIMER_ON | STOP_TIMER_IN_IDLE_MODE | TIMER_SOURCE_INTERNAL |
            GATED_TIME_DISABLED | TIMER_16BIT_MODE | TIMER_PRESCALER;

    IEC0bits.T4IE = 1;
}




/****************************************************************************
  Function:
    void __attribute__((__interrupt__, auto_psv)) _T3Interrupt(void)

  Description:
    Timer ISR, used to update application state. If no transfers are pending
    new input request is scheduled.
  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/

void __ISR(_TIMER_4_VECTOR, IPL3SOFT) _T4Interrupt(void)
//void __ISR_AT_VECTOR(_TIMER_4_VECTOR, ipl3) _T4Interrupt(void)
{
	    if (IFS0bits.T4IF)
	    {
	        IFS0bits.T4IF   = 0;
	    }
}


void __ISR(_TIMER_3_VECTOR, IPL2SOFT) _T3Interrupt( void )
//void __ISR_AT_VECTOR(_TIMER_3_VECTOR, ipl2) _T3Interrupt(void)
{
    static unsigned int counts;
    if (IFS0bits.T3IF)
    {
        IFS0bits.T3IF = 0;
//        SYSTEM_CLOCK_TOGGLE ^= 1;
        if(DelayTicks > 0) DelayTicks--;
        counts++;
        if(counts >= 500)
        {
            LED_ONB2^=1;
            counts = 0;
        }
//        if(AnalogSampleCtr > 0) AnalogSampleCtr--;
//        if(MasterStateCtr > 0) MasterStateCtr--;        
        SystemTicks++;
    }
}
