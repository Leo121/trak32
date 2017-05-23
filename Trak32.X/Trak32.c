
// Includes Section
#include <xc.h>
#include <sys/attribs.h>        //note: this include is needed for interrupts
#include <p32xxxx.h>
#include <stdio.h>
#include "common.h"
#include "trakhardware.h"
#include "trakserial.h"
#include "trakcommands.h"
#include "trak-ints.h"


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


void checkComChannels(void);
void checkSampleTimers(void);
void masterStateMachine(void);


/*************************************************************************
 Global Data
 *************************************************************************/



/*************************************************************************
 Main entry point
 *************************************************************************/
int main(void)
{
    InitializeHardware();
//    INTEnableSystemMultiVectoredInt();
    InitializeInterrupts();
        
    LED_ONB1 = 1;
    LED_ONB2 = 1;
    DelayByCounts(1000);
    LED_ONB1 = 1;
    LED_ONB2 = 0;    
    
    sprintf(TX2buffer, "Boot!\r\n");
    kickU2TX();
  
    MasterStateCtr = MASTER_COUNT_TICKS;
    AnalogSampleCtr = ANALOG_SAMPLE_TICKS;
      
    while(1)
    {        
        checkComChannels();
        if(AnalogSampleCtr == 0) checkSampleTimers();
        if(MasterStateCtr == 0) masterStateMachine();        
    }
}

void checkComChannels(void)
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


void checkSampleTimers(void)
{
    AnalogSampleCtr = ANALOG_SAMPLE_TICKS;
    //sample all ADCs and save
}

void masterStateMachine(void)
{
    MasterStateCtr = MASTER_COUNT_TICKS;
    
}







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
    uint32 timerPeriod;

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

