/* 
 * File:   trakcommands.h
 * Author: KMW
 *
 * Created on January 13, 2017, 4:14 PM
 */

#ifndef TRAKCOMMANDS_H
#define	TRAKCOMMANDS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum{
    CMD_STATUS = 'S',    
    CMD_UPTIME = 'U',
    CMD_VERSION = 'V',
    CMD_ADC = 'A',
    CMD_LED = 'L',
    CMD_INPUT = 'I',
    CMD_OUTPUT = 'O',
    CMD_PWM = 'P',
    CMD_ADC_VOLTAGE = 'V',
    CMD_ACCEL = 'C',
    CMD_BARO = 'B',
    CMD_MAGNETOMETER = 'G',
    CMD_MOTOR = 'M',
    CMD_DIGITS = 'D',
    CMD_TEMPERATURE = 'T',
    CMD_ODOMETER = 'R'
}TRAK_COMMANDS;

typedef enum{
    CMD_ACTION_READ = 'R',
    CMD_ACTION_WRITE = 'W',
    CMD_ACTION_SWEEP = 'S',
    CMD_ACTION_LCD = 'L',
    CMD_ACTION_UART = 'U',
    CMD_ACTION_BOTH = 'B',
    CMD_ACTION_OFF = 'F',
    CMD_ACTION_ON = 'N',
    CMD_ACTION_TOGGLE = 'T'            
}TRAK_COMMAND_ACTIONS;


typedef enum{
    COM_NO_ERROR,
    COM_ERROR_OVERFLOW,
    COM_ERROR_BAD_HW,
    COM_ERROR_BAD_SELECT,
    COM_ERROR_BAD_STATE,
    COM_ERROR_BAD_VALUE,
    COM_ERROR_BAD_ACTION            
}COM_ERRORS;


typedef enum{
	DEV_MODE_1 = '1',				//ADC/pot inputs, no output
	DEV_MODE_2 = '2',				//ADC/pot inputs, output at 500ms
	DEV_MODE_3 = '3',				//
	DEV_MODE_4 = '4'
}DEV_OPERATION_MODES;

#define BAD_STATE 0xFF      //numerous hardware types may return a bad state, this will be 0xFF

typedef enum{
	FLAG_OFF,
	FLAG_ON
}FLAG_VALUES;


extern uint8 RXcmdbuffer[];
extern uint8 RX2readptr;
extern COM_ERRORS ComError;

extern void ExtractCommand(void);
extern void InterpretCommands(uint8 *CommandString);
extern void ParseU2Command(void);

extern COM_ERRORS HandleLEDCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleADCCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleMotorCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleInputCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleOutputCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleDigitCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleAccelCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleBaroCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleMagnetometerCommand(uint8 *CommandString, uint8 *TXbuffer);
extern COM_ERRORS HandleTemperatureCommand(uint8 *CommandString, uint8 *TXbuffer);


#ifdef	__cplusplus
}
#endif

#endif	/* TRAKCOMMANDS_H */

