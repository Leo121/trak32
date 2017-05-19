#include <p32xxxx.h>
//#include <plib.h>
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "trakserial.h"
#include "trakcommands.h"
#include "trakhardware.h"
#include "trak32.h"
#include "trakLEDs.h"


uint8 RXcmdbuffer[255];
uint8 RX2readptr = 0;
COM_ERRORS ComError = COM_NO_ERROR;

/***************************************************************************/
void ExtractCommand(void)
{
    unsigned char i;    
    i = 0;
    while(RX2readptr != RX2inputptr)
    {
        RXcmdbuffer[i] = RX2buffer[RX2readptr];
        RX2readptr++;
        if(RX2readptr == RX2_BUFFER_LENGTH) RX2readptr = 0;                
        i++;
        if(i > RX2_BUFFER_LENGTH)
        {
            RXcmdbuffer[0] = BAD_STATE;
            ComError = COM_ERROR_OVERFLOW;
            break;
        }
    }
    RXcmdbuffer[i] = 0x00;         //need to null terminate cmd buffer
}



void InterpretCommands(unsigned char *CommandString)
{
    TRAK_COMMANDS IncomingCommand = CommandString[0];
    unsigned char action = CommandString[1];
    unsigned char CommandHandlerStatus = 0;
    uint32 TempTime;
    uint32 TempDays = 0;
    uint32 TempHours = 0;
    uint32 TempMinutes = 0;
    uint32 TempSecs = 0;
    uint8 TempFracSecs = 0;
        
    switch(IncomingCommand)
    {
//	    case CMD_RPM:
//	    	//CommandHandlerStatus = HandleRPMCommand(CommandString);
//	    	break;
//	    		    	
//    	CMD_MPH:
//	    	//CommandHandlerStatus = HandleMPHCommand(CommandString);
//    		break;
//    		    		
//    	CMD_MODE:
//	    	//CommandHandlerStatus = HandleModeCommand(CommandString);
//    		break;
//
//		CMD_CYLINDERS:
//	    	//CommandHandlerStatus = HandleCylindersCommand(CommandString);
//			break;
//			
//    	CMD_STATUS:
//	    	//CommandHandlerStatus = HandleStatusCommand(CommandString);
//    		break;


        case CMD_LED:
            CommandHandlerStatus  = 1;
            HandleLEDCommand(CommandString, TX2buffer);
            break;

        
        case CMD_UPTIME:
            CommandHandlerStatus  = 1;
            if(action == 'T')
            {
                TempTime = SystemTicks;
                TempSecs = TempTime/1000;
                TempFracSecs = TempTime - (TempSecs*1000);
                TempMinutes = TempSecs/60;
                TempSecs = TempSecs - (TempMinutes * 60);
                TempHours = TempMinutes/60;
                TempMinutes = TempMinutes - (TempHours * 60);
                TempDays = TempHours/24;
                
                //sprintf(TX2buffer, "Up time: %lu.%03i seconds\r\n", TempSecs, TempFracSecs);            
                sprintf(TX2buffer, "Up time: %i days, %i hours, %i minutes %i.%03i seconds\r\n", TempDays, TempHours, TempMinutes, TempSecs, TempFracSecs);            
            }
            else
            {
                sprintf(TX2buffer, "Up counts: %lu\r\n", SystemTicks);
            }
            break;

        case CMD_VERSION:
            CommandHandlerStatus  = 1;
            sprintf(TX2buffer, "HW version %d.%d   FW Version %d.%d\r\n", HW_VERSION_MAJOR, HW_VERSION_MINOR, FW_VERSION_MAJOR, FW_VERSION_MINOR);
            break;

            
        default:
            CommandHandlerStatus = BAD_STATE;
            ComError = COM_ERROR_BAD_HW;
            break;        
    }    
    
    if(CommandHandlerStatus == BAD_STATE)
    {
        sprintf((char*)TX2buffer, "Error: %i     CmdBfr[0] = %c\r\n", ComError, IncomingCommand);
    }
    
    kickU2TX();    
}




//
//COM_ERRORS HandleLEDCommand(uint8 *CommandString, uint8 *TXbuffer)
//{
//    COM_ERRORS returnvalue = COM_NO_ERROR;
//    switch(CommandString[1])
//    {
//        case 'R':
//            switch(CommandString[2])
//            {
//                case '1':
//                    if(LED_ONB1 == 1)
//                    {
//                        sprintf(TXbuffer, "LED 1 on\r\n");
//                    }
//                    else
//                    {
//                        sprintf(TXbuffer, "LED 1 off\r\n");                        
//                    }
//                    break;
//                case '2':
//                    break;
//                case '3':
//                    break;
//                case '4':
//                    break;
//                default:
//                    returnvalue = COM_ERROR_BAD_SELECT;
//                    break;
//            }
//            break;
//        
//        case 'W':
//            break;
//            
//        default:
//            returnvalue = COM_ERROR_BAD_ACTION;
//            break;
//    }
//    return returnvalue;
//}


COM_ERRORS HandleLEDCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    unsigned char Select = CommandString[1];
    TRAK_COMMAND_ACTIONS Action = CommandString[2];
    unsigned char CommandStringLength;
    int CommandValue = 0;
    unsigned char CommandValueString[7];
    LED_STATE CmdLEDState;
    unsigned char i, j, statechar;
    LED_HW CmdLEDSelect;
    unsigned char returnvalue = 0;

    switch(Select)
    {
        case '1':
            CmdLEDSelect = LED_1;
            break;
        case '2':
            CmdLEDSelect = LED_2;
            break;
        case '3':
            CmdLEDSelect = LED_3;
            break;
        case '4':
            CmdLEDSelect = LED_4;
            break;
        default:
            ComError = COM_ERROR_BAD_SELECT;
            returnvalue = BAD_STATE;
    }
    
    if(returnvalue != BAD_STATE)
    {
        switch(Action)
        {
            case CMD_ACTION_OFF:
                CmdLEDState = LED_OFF;
                break;

            case CMD_ACTION_ON:
                CmdLEDState = LED_ON;
                break;

            case CMD_ACTION_TOGGLE:
                CmdLEDState = LED_TOGGLE;
                CommandStringLength = strlen(CommandString);
                if(CommandStringLength > 10 || CommandStringLength < 6)
                {
                    ComError = COM_ERROR_BAD_VALUE;
                    returnvalue = BAD_STATE;
                }
                else
                {
                    j = 0;
                    for(i = 3; i < CommandStringLength - 2; i++)
                    {
                        if(isdigit(CommandString[i]) == 0)
                        {
                            returnvalue = BAD_STATE;
                            break;
                        }
                        else
                        {
                            CommandValueString[j] = CommandString[i]; //if(CommandString)
                            j++;
                        }
                    }
                    CommandValueString[j] = 0x00;   //null terminate string
                    CommandValue = atoi(CommandValueString);
                }
                break;
                
            case CMD_ACTION_READ:
                CmdLEDState = ReadLED(CmdLEDSelect);
                break;
            default:
                ComError = COM_ERROR_BAD_STATE;
                returnvalue = BAD_STATE;
        }
    
    }
    
    if(returnvalue != BAD_STATE)
    {
        switch(Action)
        {
            case CMD_ACTION_OFF:
            case CMD_ACTION_ON:
            case CMD_ACTION_TOGGLE:
                SetLED(CmdLEDSelect, CmdLEDState, (uint16) CommandValue);
                sprintf(TXbuffer, "OK\r\n");
                break;

            case CMD_ACTION_READ:
                CmdLEDState = ReadLED(CmdLEDSelect);
                if(CmdLEDState == LED_ON)
                {
                    statechar = CMD_ACTION_ON;
                }
                else
                {
                    statechar = CMD_ACTION_OFF;                    
                }
                sprintf(TXbuffer, "L%c%c\r\n", Select, statechar);
                break;
            default:
                ComError = COM_ERROR_BAD_STATE;
                returnvalue = BAD_STATE;
        }
    }
    
    return returnvalue;
}


COM_ERRORS HandleADCCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleMotorCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleInputCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleOutputCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleDigitCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleAccelCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleBaroCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleMagnetometerCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleTemperatureCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

