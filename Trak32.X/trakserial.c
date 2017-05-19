
//#include "common.h"
#include <xc.h>
#include <plib.h>
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
    putcUART1(TX1buffer[TX1ptr]);
    INTEnable(INT_U1TX, INT_ENABLED);
    //enable U2 TX interrupt
    //send char
}


/*************************************************************************
 Initiate UART2 interrupt driven transmit
 *************************************************************************/
void kickU2TX(void)
{
    TX2length = strlen(TX2buffer);
    TX2ptr = 0;
    TX2enabled = 1;
    putcUART2(TX2buffer[TX2ptr]);
    INTEnable(INT_U2TX, INT_ENABLED);
    //enable U2 TX interrupt
    //send char
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
    SetPriorityIntU1(UART_INT_PR5);
    SetSubPriorityIntU1(UART_INT_SUB_PR0);
    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));    // Enable the UART module
 // Interrupt enabling for RX and TX section
    INTEnable(INT_U1RX, INT_ENABLED);  // RX Interrupt is enabled
    INTEnable(INT_U1TX, INT_DISABLED);
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
    SetPriorityIntU2(UART_INT_PR4);
    SetSubPriorityIntU2(UART_INT_SUB_PR0);
    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));    // Enable the UART module
 // Interrupt enabling for RX and TX section
    INTEnable(INT_U2RX, INT_ENABLED);  // RX Interrupt is enabled
    INTEnable(INT_U2TX, INT_DISABLED);
}


/*************************************************************************
 Interrupts
 *************************************************************************/
void __ISR(_UART1_VECTOR, IPL5SOFT) IntUart1Handler(void)
{
    BYTE incoming;
    // Is this an RX interrupt?
    if(mU1RXGetIntFlag())
    {
        //save the incoming byte
        incoming = ReadUART1();
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

        mU1RXClearIntFlag();    // Clear the RX interrupt Flag
    }

	// We don't care about TX interrupt
	if (mU1TXGetIntFlag() && TX1enabled == 1)
	{
            mU1TXClearIntFlag();
            TX1ptr++;
            if(TX1ptr == TX1length)
            {
                INTEnable(INT_U1TX, INT_DISABLED);  //disable interrupt
                TX1enabled = 0;
            }
            else
            {
                putcUART1(TX1buffer[TX1ptr]);
            }
	}
}


void __ISR(_UART2_VECTOR, IPL4SOFT) IntUart2Handler(void)
{
    BYTE incoming;
    // Is this an RX interrupt?
    if(mU2RXGetIntFlag())
    {
        //save the incoming byte
        LED_ONB1 = LED_ON;
        incoming = ReadUART2();
        RX2buffer[RX2inputptr] = incoming;
        RX2inputptr++;
        if(RX2inputptr == RX2_BUFFER_LENGTH) RX2inputptr = 0;
        if(incoming == 0x0D || incoming == 0x0A)
        {
            RX2DataFlag = RECEIVED_COMMAND;
        }

        mU2RXClearIntFlag();    // Clear the RX interrupt Flag
        LED_ONB1 = LED_OFF;
	//	putcUART2(incoming);	// Echo what we just received.
    }

    //if (mU2TXGetIntFlag() && TX2enabled == 1)
	if (mU2TXGetIntFlag())
    {
        if(TX2enabled == 1)
        {
            mU2TXClearIntFlag();
            TX2ptr++;
            if(TX2ptr >= TX2_BUFFER_LENGTH)
            {
                TX2ptr = 0;
                //should log TX overflow error
            }
            if(TX2ptr == TX2length)
            {
                INTEnable(INT_U2TX, INT_DISABLED);  //disable interrupt
                TX2enabled = 0;
            }
            else
            {
                putcUART2(TX2buffer[TX2ptr]);
            }
        }
    }

}
        
