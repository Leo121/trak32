
// Includes Section
#include <xc.h>
#include <sys/attribs.h>        //note: this include is needed for interrupts
#include <p32xxxx.h>
#include "common.h"
#include "trakhardware.h"
#include "trakserial.h"
#include "trakcommands.h"
#include "trak-ints.h"


    
uint16 MasterStateCtr;
uint16 AnalogSampleCtr;




//**Interrupt code**//

void InitializeInterrupts(void)
{    
    //PRISS = 0x76543210;           ????
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
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
//void __ISR(_TIMER_4_VECTOR, IPL3SRS) _T4Interrupt(void)
//void __ISR_AT_VECTOR(_TIMER_4_VECTOR, ipl3) _T4Interrupt(void)
{
	    if (IFS0bits.T4IF)
	    {
	        IFS0bits.T4IF   = 0;
	    }
}


void __ISR(_TIMER_3_VECTOR, IPL2SOFT) _T3Interrupt( void )
//void __ISR_AT_VECTOR(_TIMER_3_VECTOR, IPL2SRS) _T3Interrupt(void)
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
        if(AnalogSampleCtr > 0) AnalogSampleCtr--;
        if(MasterStateCtr > 0) MasterStateCtr--;        
        SystemTicks++;
    }
}









//void __ISR_AT_VECTOR(_TIMER_3_VECTOR, IPL2SRS) _T3Interrupt(void)
//{
//    static unsigned int counts;
//        
//    if (IFS0bits.T3IF)
//    {
//        IFS0bits.T3IF = 0;
//        
//        //RN4020_WAKE_SW = RN4020_WAKE_SW ^1;
//
//        //AUDIO_SHUTDOWN ^= 1;
//        
//        LEDcounter++;
//
//        HandleSoundInterrupt();
//        
//        counts++;
//        if(counts == MASTER_STATE_COUNTS)
//        {
//            MasterFlag = TRUE;
//            counts = 0;
//        }
//
//        if(StateTimer > 0) StateTimer--;
//        if(DelayTimer > 0) DelayTimer--;
//        if(SwingTimer > 0) SwingTimer --;
//        if(BLETimerTicks > 0) BLETimerTicks--;
//        if(LEDTimer > 0) LEDTimer--;
//        
//        #ifdef USE_ANALOG_ACCELS
//        SampleAccelsCounts++;
//        if(SampleAccelsCounts == ACCEL_SAMPLE_COUNTS)
//        {
//            SampleAccelsCounts = 0;
//            fSampleAnalogAccels = TRUE;
//        }
//        #endif
//        CalculateVelocityCounts++;
//        if(CalculateVelocityCounts == VELOCITY_CALC_COUNTS)
//        {
//            CalculateVelocityCounts = 0;
//            fCalculateVelocity = TRUE;
//        }
//
//    }
//}




//void __ISR(_UART2_RX_VECTOR, IPL4SRS) IntUart2RXHandler(void)
//{
//    uint8 incoming;
//    // Is this an RX interrupt?
//    //LED1 = 1;
//    LEDTimer = HALF_SECOND_COUNTS;
//    if(IFS4bits.U2RXIF)
//    {
//        //save the incoming byte
//        //incoming = ReadUART2();
//        incoming = U2RXREG;
//        RXbuffer[RXptr] = incoming;
//        RXptr++;
////        if(incoming == 0x0D)
//        if(incoming == 0x0A)
//        {
//            RXDataFlag = COMMAND_RECEIVED;
//            IncomingStringLength = RXptr;
//        }
//
//        //mU2RXClearIntFlag();    // Clear the RX interrupt Flag
//        IFS4bits.U2RXIF = 0;    // Clear the RX interrupt Flag
//
//    }
//}

//void __ISR(_UART2_TX_VECTOR, IPL5SRS) IntUart2TXHandler(void)	
//{
////	if (mU2TXGetIntFlag() && TXenabled == 1)
//    if(IFS4bits.U2TXIF && TXenabled)
//	{
//            //mU2TXClearIntFlag();
//            IFS4bits.U2TXIF = 0;    //clear TX int flag
//            TXptr++;
//            if(TXptr == TXlength)   //if we have transmitted full pakcet
//            {
//                //INTEnable(INT_U2TX, INT_DISABLED);
//                IEC4bits.U2TXIE = 0;  //disable interrupt
//                TXenabled = 0;
//            }
//            else
//            {
//                //putcUART2(TXbuffer[TXptr]);
//                U2TXREG = TXbuffer[TXptr];
//            }
//	}
//    //LED1 = 0;    
//}

#ifdef ENABLE_DEBUG_UART
void __ISR(_UART1_VECTOR, ipl5) IntUart1Handler(void)
{
    uint8 incoming;
    // Is this an RX interrupt?
    LED1 = 1;
    //if(mU1RXGetIntFlag())
    if(IFS3bits.U1RXIF)
    {
        //save the incoming byte
        //incoming = ReadUART1();
        incoming = U1RXREG;
        RXbuffer[RXptr] = incoming;
        RXptr++;
        if(incoming == 0x0D)
        {
            RXDataFlag = COMMAND_RECEIVED;
        }

        //mU1RXClearIntFlag();
        IFS3bits.U1RXIF = 0;    // Clear the RX interrupt Flag
    }

	// We don't care about TX interrupt
	//if (mU1TXGetIntFlag() && DebugTXenabled == 1)
    if(IFS3bits.U1TXIF && DebugTXenabled)
	{
            //mU1TXClearIntFlag();
            IFS3bits.U1TXIF = 0;
            DebugTXptr++;
            if(DebugTXptr == DebugTXlength)
            {
                //INTEnable(INT_U1TX, INT_DISABLED);  //disable interrupt
                IEC3bits.U1TXIE = 0;
                DebugTXenabled = 0;
            }
            else
            {
                //putcUART1(DebugTXbuffer[DebugTXptr]);
                U1TXREG = DebugTXbuffer[DebugTXptr];
            }
	}
}
#endif


void __ISR(_TIMER_2_VECTOR, IPL7SRS) T2_IntHandler (void)
{
// Insert user code here
    IFS0CLR = 0x0100; 
}

typedef enum {
EXCEP_IRQ = 0, // 0 - interrupt
EXCEP_AdEL = 4, // 4 - address error exception (load or ifetch)
EXCEP_AdES, // 5 - address error exception (store)
EXCEP_IBE, // 6 - bus error (ifetch)
EXCEP_DBE, // 7 - bus error (load/store)
EXCEP_Sys, // 8 - syscall
EXCEP_Bp, // 9 - breakpoint
EXCEP_RI, // 10 - reserved instruction
EXCEP_CpU, // 11 - coprocessor unusable
EXCEP_Overflow, // 12 - arithmetic overflow
EXCEP_Trap, // 13 - trap (possible divide by zero)
EXCEP_IS1 = 16, // 16 - implementation specfic
EXCEP_CEU, // 17 - CorExtend Unuseable
EXCEP_C2E // 18 - coprocessor 2
} _excep_code;

/******************************************************************************/
/* void _general_exception_handler(unsigned int Cause, unsigned int Status) */
/* */
/* PreCondition: None */
/* */
/* Input: None */
/* */
/* Output: None */
/* */
/* Side Effects: None */
/* */
/* Overview: Overrides (weak) general exception handler provided by */
/* C32. Uses C32 macros to read epc and cause registers. */
/* Application code can then do something useful with them. */
/* */
/******************************************************************************/

void __attribute__((naked, nomips16)) _general_exception_handler(uint32 cause, uint32 status)
{
    //UINT32 count=0;
    uint32 _epc=0;
    uint32 _status = 0;
    _excep_code _cause = 0;

    _status = status;
    _cause = ((cause & 0x0000007C) >> 2);
    _epc = _CP0_GET_EPC();
    while(1)
    {
        Nop();
    }
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
