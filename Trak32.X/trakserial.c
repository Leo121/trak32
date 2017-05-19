
//#include "common.h"
#include <xc.h>
#include <sys/attribs.h>        //note: this include is needed for interrupts
#include "common.h"
#include "trakhardware.h"
#include "trakserial.h"


unsigned char TX1buffer[TX1_BUFFER_LENGTH];
unsigned char TX1ptr;
unsigned char TX1length;
unsigned char TX1enabled;

unsigned char RX1buffer[RX1_BUFFER_LENGTH];
unsigned char RX1ptr;
unsigned char RX1mode;
unsigned char RX1packetlength;
RX_DATA_STATE_T RX1DataFlag = RECEIVING_DATA;

unsigned char TX2buffer[TX2_BUFFER_LENGTH];
unsigned char TX2ptr;
unsigned char TX2length;
unsigned char TX2enabled;

unsigned char RX2buffer[RX2_BUFFER_LENGTH];
unsigned char RX2inputptr = 0;
unsigned char RX2mode;
unsigned char RX2packetlength;
RX_DATA_STATE_T RX2DataFlag = RECEIVING_DATA;


/*************************************************************************
 Initiate UART1 interrupt driven transmit
 *************************************************************************/
void kickU1TX(void)
{
    TX1length = strlen(TX1buffer);
    TX1ptr = 0;
    TX1enabled = 1;
    U1TXREG = TX1buffer[TX1ptr];
    IEC0bits.U1TXIE = 1;
}


/*************************************************************************
 Initiate UART2 interrupt driven transmit
 *************************************************************************/
void kickU2TX(void)
{
    TX2length = strlen(TX2buffer);
    TX2ptr = 0;
    TX2enabled = 1;
    U2TXREG = TX2buffer[TX2ptr];
    IEC1bits.U2TXIE = 1;
}


/*************************************************************************
 Initialize UART1
 *************************************************************************/
void InitializeUART1(void)
{
    U1BRG = 51;         //115200 baud @ 24MHz
    U1STA =  0x00009700;
    //U1MODE = 0x00008000;    //for BRGH = 0
    //U1MODE = 0x00008008;    //for BRGH = 1, no cts/rts
    U1MODE = 0x00008008;    //for BRGH = 1, CTS and RTS disabled
//    SetPriorityIntU1(UART_INT_PR5);
//    SetSubPriorityIntU1(UART_INT_SUB_PR0);
//    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));    // Enable the UART module
    
    
    IPC6bits.U1IP = 5;
    IPC6bits.U1IS = 0;
    
    
    
 // Interrupt enabling for RX and TX section
    IEC0bits.U1RXIE = 1;        //INTEnable(INT_U1RX, INT_ENABLED);  // RX Interrupt is enabled
    IEC0bits.U1TXIE = 0;        //INTEnable(INT_U1TX, INT_DISABLED);    
}



/*************************************************************************
 Initialize UART2
 *************************************************************************/
void InitializeUART2(void)
{
    U2BRG = 51;        //115200 baud @ 24MHz
    U2STA =  0x00009600;
    //U2MODE = 0x00008000;    //for BRGH = 0
    U2MODE = 0x00008008;    //for BRGH = 1, CTS and RTS disabled
    //U2MODE = 0x00008208;    //for BRGH = 1, CTS and RTS enabled
//    SetPriorityIntU2(UART_INT_PR4);
//    SetSubPriorityIntU2(UART_INT_SUB_PR0);
//    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));    // Enable the UART module
    
//    IPC8bits.U2RXIP = 4;
//    IPC8bits.U2RXIS = 0;
//    IPC8bits.U2TXIP = 5;
//    IPC8bits.U2TXIS = 0;
    
    IPC8bits.U2IP = 4;
    IPC8bits.U2IS = 0;
//    IPC8bits.U2TXIP = 5;
//    IPC8bits.U2TXIS = 0;
    
    
    
 // Interrupt enabling for RX and TX section
    IEC1bits.U2RXIE = 1;        //INTEnable(INT_U2RX, INT_ENABLED);  // RX Interrupt is enabled
    IEC1bits.U2TXIE = 0;        //INTEnable(INT_U2TX, INT_DISABLED);    
}


/*************************************************************************
 Interrupts
 *************************************************************************/
void __ISR(_UART1_VECTOR, IPL5SOFT) IntUart1Handler(void)
{
    uint8 incoming;
    // Is this an RX interrupt?
    if(IFS0bits.U1RXIF)
    {
        //save the incoming byte
        //incoming = ReadUART1();
        incoming = U1RXREG;
        if(incoming == 0x0D || incoming == 0x0A)
        {
            RX1DataFlag = RECEIVED_COMMAND;
            RX1buffer[RX1ptr] = 0x00;           //null terminate the incoming string
        }
        else
        {
            RX1buffer[RX1ptr] = incoming;
            RX1ptr++;
            if(RX1ptr == RX1_BUFFER_LENGTH) RX1ptr = 0;
        }

        IFS0bits.U1RXIF = 0;
    }

	//if (mU1TXGetIntFlag() && TX1enabled == 1)
    if (IFS0bits.U1TXIF && TX1enabled == 1)
	{
            IFS0bits.U1TXIF = 0;
            TX1ptr++;
            if(TX1ptr == TX1length)
            {
                //INTEnable(INT_U1TX, INT_DISABLED);  //disable interrupt
                IEC0bits.U1TXIE = 0;
                TX1enabled = 0;
            }
            else
            {
                //putcUART1(TX1buffer[TX1ptr]);
                U1TXREG = TX1buffer[TX1ptr];
            }
	}
}


void __ISR(_UART2_VECTOR, IPL4SOFT) IntUart2Handler(void)
{
    uint8 incoming;
    // Is this an RX interrupt?
    //if(mU2RXGetIntFlag())
    if(IFS1bits.U2RXIF)
    {
        //save the incoming byte
        LED_ONB1 = LED_ON;
        //incoming = ReadUART2();
        incoming = U2RXREG;
        RX2buffer[RX2inputptr] = incoming;
        RX2inputptr++;
        if(RX2inputptr == RX2_BUFFER_LENGTH) RX2inputptr = 0;
        if(incoming == 0x0D || incoming == 0x0A)
        {
            RX2DataFlag = RECEIVED_COMMAND;
        }

        IFS1bits.U2RXIF = 0;            //mU2RXClearIntFlag();    // Clear the RX interrupt Flag
        LED_ONB1 = LED_OFF;
	//	putcUART2(incoming);	// Echo what we just received.
    }

    //if (mU2TXGetIntFlag() && TX2enabled == 1)
	//if (mU2TXGetIntFlag())
    if(IFS1bits.U2TXIF)
    {
        if(TX2enabled == 1)
        {
            IFS1bits.U2TXIF = 0;            //mU2TXClearIntFlag();
            TX2ptr++;
            if(TX2ptr >= TX2_BUFFER_LENGTH)
            {
                TX2ptr = 0;
                //should log TX overflow error
            }
            if(TX2ptr == TX2length)
            {
                IEC1bits.U2TXIE = 0;        //INTEnable(INT_U2TX, INT_DISABLED);  //disable interrupt
                TX2enabled = 0;
            }
            else
            {
                //putcUART2(TX2buffer[TX2ptr]);
                U2TXREG = TX2buffer[TX2ptr];
            }
        }
    }

}
        
