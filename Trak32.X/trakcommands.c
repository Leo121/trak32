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
#include "trakbarometer.h"
#include "trakeep.h"


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

        case CMD_ADC:
            CommandHandlerStatus  = 1;
            HandleADCCommand(CommandString, TX2buffer);
            break;

        case CMD_ADC_VOLTAGE:
            CommandHandlerStatus  = 1;
            HandleADCvCommand(CommandString, TX2buffer);
            break;
            
        case CMD_TEMPERATURE:
            CommandHandlerStatus  = 1;
            HandleTemperatureCommand(CommandString, TX2buffer);
            break;
            
        case CMD_BARO:
            CommandHandlerStatus  = 1;
            HandleBaroCommand(CommandString, TX2buffer);
            break;
            
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
                TempHours = TempHours - (TempDays * 24);
                
                sprintf(TX2buffer, "Up time: %i:%02i:%02i:%02i.%03i\r\n", TempDays, TempHours, TempMinutes, TempSecs, TempFracSecs);                                
                //sprintf(TX2buffer, "Up time: %i days, %i hours, %i minutes %i.%03i seconds\r\n", TempDays, TempHours, TempMinutes, TempSecs, TempFracSecs);            
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

        case CMD_SELF_TEST:
            selfTest();
            sprintf(TX2buffer, "Self Test Complete\r\n");
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


//#define aONB_TEMP_CH            2
//#define aRMOTOR_TEMP_CH         4    
//#define aLMOTOR_TEMP_CH         3    
//#define aLIGHT_SENSE_CH         5    
//#define aBAT1_CH                10    
//#define aBAT2_CH                11    
//#define aSPARE1_CH              6    
//#define aSPARE2_CH              7    
//#define aSPARE3_CH              8    
//#define aSPARE4_CH              9    

COM_ERRORS HandleADCCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    unsigned char Select = CommandString[1];
    TRAK_COMMAND_ACTIONS Action = CommandString[2];
    //unsigned char CommandStringLength;
    //int CommandValue = 0;
    //unsigned char CommandValueString[7];
    uint8 adcChannel;
    uint16 adcValue;
    
    
    //unsigned char i, j, statechar;
    unsigned char returnvalue = 0;

    adcChannel = adcSelectToChannel(Select);
  
    if(adcChannel == BAD_STATE) returnvalue = BAD_STATE;
    
    if(returnvalue != BAD_STATE)
    {
        switch(Action)
        {
            case CMD_ACTION_OFF:
            case CMD_ACTION_ON:
            case CMD_ACTION_TOGGLE:
                break;

            case CMD_ACTION_READ:
                adcValue = readADCbyChannel(adcChannel);
                sprintf(TXbuffer, "A%c:%i\r\n", Select, adcValue);
                break;
            default:
                ComError = COM_ERROR_BAD_STATE;
                returnvalue = BAD_STATE;
        }
    }    
    return returnvalue;    
}

COM_ERRORS HandleADCvCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    unsigned char Select = CommandString[1];
    TRAK_COMMAND_ACTIONS Action = CommandString[2];
    uint8 adcChannel;
    float adcResult, hold;
    int16 whole, fraction;
    
    //unsigned char i, j, statechar;
    unsigned char returnvalue = 0;

    adcChannel = adcSelectToChannel(Select);
  
    if(adcChannel == BAD_STATE) returnvalue = BAD_STATE;        
    
    if(returnvalue != BAD_STATE)
    {
        switch(Action)
        {
            case CMD_ACTION_OFF:
            case CMD_ACTION_ON:
            case CMD_ACTION_TOGGLE:
                break;

            case CMD_ACTION_READ:
                readADCvoltageChannel(adcChannel, &adcResult);
                adcResult = adcResult + 0.0005;     //round up
                whole = (int)adcResult;
                hold = adcResult - (float)whole;
                fraction = (uint16)(hold * 1000);
                sprintf(TXbuffer, "A%cv:%i.%03i\r\n", Select, whole, fraction);
                break;
            default:
                ComError = COM_ERROR_BAD_STATE;
                returnvalue = BAD_STATE;
        }
    }    
    return returnvalue;    
}

uint8 adcSelectToChannel(uint8 selectChar)
{
    uint8 adcChannel;
    switch(selectChar)
    {
        case '1':
            adcChannel = 2;
            break;
        case '2':
            adcChannel = 3;
            break;
        case '3':
            adcChannel = 4;
            break;
        case '4':
            adcChannel = 5;
            break;
        case '5':
            adcChannel = 10;
            break;
        case '6':
            adcChannel = 11;
            break;
        case '7':
            adcChannel = 6;
            break;
        case '8':
            adcChannel = 7;
            break;
        case '9':
            adcChannel = 8;
            break;
        case 'A':
            adcChannel = 9;
            break;            
        default:
            adcChannel = BAD_STATE;
    }
    return adcChannel;
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
    COM_ERRORS returnvalue = 0;
    if(barometerStatus == PERIPHERAL_NOT_PRESENT)
    {
       sprintf(TXbuffer, "Baro Not Present\r\n"); 
    }
    else
    {
        if(barometerStatus == PERIPHERAL_ERROR)
        {
           sprintf(TXbuffer, "Baro Error\r\n");             
        }
        else
        {
            sprintf(TXbuffer, "BP:%3.2f\r\n", currentBarometricPressure);
        }
    }
    return returnvalue;
}

COM_ERRORS HandleMagnetometerCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    
}

COM_ERRORS HandleTemperatureCommand(uint8 *CommandString, uint8 *TXbuffer)
{
    unsigned char Select = CommandString[1];
    TRAK_COMMAND_ACTIONS Action = CommandString[2];
    uint8 adcChannel;
    float adcResult, hold;
    int16 whole, fraction;
    
    //unsigned char i, j, statechar;
    unsigned char returnvalue = 0;

    adcChannel = adcSelectToChannel(Select);
  
    if(adcChannel == BAD_STATE) returnvalue = BAD_STATE;        
    
    if(returnvalue != BAD_STATE)
    {
        switch(Action)
        {
            case CMD_ACTION_OFF:
            case CMD_ACTION_ON:
            case CMD_ACTION_TOGGLE:
                break;

            case CMD_ACTION_READ:
                readADCvoltageChannel(adcChannel, &adcResult);
                voltageToTemp(adcResult, &adcResult);
                adcResult = adcResult + 0.0005;     //round up
                whole = (int)adcResult;
                hold = adcResult - (float)whole;
                fraction = (int)(hold * 1000);
                sprintf(TXbuffer, "A%ct:%i.%03i\r\n", Select, whole, fraction);
                break;
            default:
                ComError = COM_ERROR_BAD_STATE;
                returnvalue = BAD_STATE;
        }
    }    
    return returnvalue;        
}


void selfTest(void)
{
    while(TX2enabled);
    sprintf(TX2buffer, "****\r\nSelf test at up counts: %lu\r\n", SystemTicks);
    kickU2TX();
    while(TX2enabled);
    if(barometerStatus == PERIPHERAL_OK)
    {
        sprintf(TX2buffer, "Barometer OK\r\n");                
    }
    else
    {
        sprintf(TX2buffer, "Barometer Error\r\n");        
    }
    kickU2TX();

    while(TX2enabled);
    
    if(accelTest() == RETURN_SUCCESS)
    {
        sprintf(TX2buffer, "Accel OK\r\n");
    }
    else
    {
        sprintf(TX2buffer, "Accel Error\r\n");        
    }
    kickU2TX();

    while(TX2enabled);
    
    if(magTest() == RETURN_SUCCESS)
    {
        sprintf(TX2buffer, "Mag OK\r\n");
    }
    else
    {
        sprintf(TX2buffer, "Mag Error\r\n");        
    }
    kickU2TX();

    while(TX2enabled);        
    if(eepTest(EEP_1) == RETURN_SUCCESS)
    {
        sprintf(TX2buffer, "EEP 1 OK\r\n");        
    }
    else
    {
        sprintf(TX2buffer, "EEP 1 error\r\n");        
    }
    
    kickU2TX();

    while(TX2enabled);        
    if(eepTest(EEP_2) == RETURN_SUCCESS)
    {
        sprintf(TX2buffer, "EEP 2 OK\r\n");        
    }
    else
    {
        sprintf(TX2buffer, "EEP 2 error\r\n");        
    }
    kickU2TX();

    while(TX2enabled);        
        
}
