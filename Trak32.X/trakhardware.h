/* 
 * File:   trakhardware.h
 * Author: KMW
 *
 * Created on October 16, 2016, 10:24 PM
 */

#ifndef TRAKHARDWARE_H
#define	TRAKHARDWARE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "common.h"    
    
typedef enum
{
    LED_OFF,
    LED_ON
}LED_STATE_T;

typedef enum{
    PERIPHERAL_NOT_PRESENT,
    PERIPHERAL_ERROR,
    PERIPHERAL_OK
}PERIPHERAL_STATUS_T;

#define BAROMETER_INSTALLED
#define ACCELEROMETER_INSTALLED    
    
    
///////////////////////////////////////////////////////////////
//onboard LED1
#define LED_ONB1        LATFbits.LATF12
#define LED_ONB1_TRIS   TRISFbits.TRISF12
#define LED_ONB1_PORT   PORTFbits.RF12
//onboard LED2
#define LED_ONB2        LATFbits.LATF13
#define LED_ONB2_TRIS   TRISFbits.TRISF13
#define LED_ONB2_PORT   PORTFbits.RF13
//raspi shared LED1
#define LED_PI1         LATAbits.LATA7
#define LED_PI1_PORT    PORTAbits.RA7
#define LED_PI1_TRIS    TRISAbits.TRISA7

//raspi shared LED2
#define LED_PI2         LATGbits.LATG15
#define LED_PI2_PORT    PORTGbits.RG15
#define LED_PI2_TRIS    TRISGbits.TRISG15

///////////////////////////////////////////////////////////////    
//opto1 input
#define OPTO_DETECT1        PORTBbits.RB14
#define OPTO_DETECT1_TRIS   TRISBbits.TRISB14
    
//opto2 input
#define OPTO_DETECT2        PORTBbits.RB15
#define OPTO_DETECT2_TRIS   TRISBbits.TRISB15

///////////////////////////////////////////////////////////////
//external LED/optional drive 1-8 hardware JP15
#define EXT1_OUT        LATEbits.LATE0
#define EXT1_IN         PORTEbits.RE0
#define EXT1_TRIS       TRISEbits.TRISE0
#define EXT2_OUT        LATEbits.LATE1
#define EXT2_IN         PORTEbits.RE1
#define EXT2_TRIS       TRISEbits.TRISE1
#define EXT3_OUT        LATGbits.LATG14
#define EXT3_IN         PORTGbits.RG14
#define EXT3_TRIS       TRISGbits.TRISG14
#define EXT4_OUT        LATGbits.LATG13
#define EXT4_IN         PORTGbits.RG13
#define EXT4_TRIS       TRISGbits.TRISG13
#define EXT5_OUT        LATGbits.LATG12
#define EXT5_IN         PORTGbits.RG12
#define EXT5_TRIS       TRISGbits.TRISG12
#define EXT6_OUT        LATEbits.LATE2
#define EXT6_IN         PORTEbits.RE2
#define EXT6_TRIS       TRISEbits.TRISE2
#define EXT7_OUT        LATEbits.LATE3
#define EXT7_IN         PORTEbits.RE3
#define EXT7_TRIS       TRISEbits.TRISE3
#define EXT8_OUT        LATEbits.LATE4
#define EXT8_IN         PORTEbits.RE4
#define EXT8_TRIS       TRISEbits.TRISE4
    
///////////////////////////////////////////////////////////////
//Note:  the PI IO pins are also U4 TX & RX
//connected to headers JP19 (simple IO) JP14 (Pi connections)    
//raspi io1, Pi GPIO27
#define PIIO1_OUT       LATDbits.LATD14
#define PIIO1_IN        PORTDbits.RD14    
#define PIIO1_TRIS      TRISDbits.TRISD14
    
//raspi io2, Pi GPIO17
#define PIIO2_OUT       LATDbits.LATD15
#define PIIO2_IN        PORTDbits.RD15   
#define PIIO2_TRIS      TRISDbits.TRISD15
    

///////////////////////////////////////////////////////////////    
//right odo LED drive
#define ODO_R_LED       LATDbits.LATD9       
#define ODO_R_LED_TRIS  TRISDbits.TRISD9
//right odo interrupt/input
#define ODO_R_IN        PORTAbits.RA14      //int 3
#define ODO_R_IN_TRIS   TRISAbits.TRISA14

//left odo LED drive
#define ODO_L_LED       LATDbits.LATD8     
#define ODO_L_LED_TRIS  TRISDbits.TRISD8
//left odo interrupt/input
#define ODO_L_IN        PORTAbits.RA15      //int 4
#define ODO_L_IN_TRIS   TRISAbits.TRISA15
    
///////////////////////////////////////////////////////////////    
//front sonar trigger
#define SONAR_R_TRIGGER         LATGbits.LATG9  
#define SONAR_R_TRIGGER_TRIS    TRISgbits.TRISG9
//front sonar input
#define SONAR_R_IN              PORTEbits.RE9       //int 2
#define SONAR_R_IN_TRIS         TRISEbits.TRISE9
//rear sonar trigger
#define SONAR_L_TRIGGER         LATAbits.LATA0 
#define SONAR_L_TRIGGER_TRIS    TRISAbits.TRISA0
//rear sonar input
#define SONAR_L_IN              PORTEbits.RE8       //int 1
#define SONAR_L_IN_TRIS         TRISEbits.TRISE8
    
///////////////////////////////////////////////////////////////
//right motor drive1
#define MOTOR_RIGHT_1           LATDbits.LATD2      //OC3    
#define MOTOR_RIGHT_1_TRIS      TRISDbits.TRISD2
//right motor drive2
#define MOTOR_RIGHT_2           LATDbits.LATD3      //OC4
#define MOTOR_RIGHT_2_TRIS      TRISDbits.TRISD3
//left motor drive1
#define MOTOR_LEFT_1           LATDbits.LATD12      //OC1
#define MOTOR_LEFT_1_TRIS      TRISDbits.TRISD12
//left motor drive2
#define MOTOR_LEFT_2           LATDbits.LATD1       //OC2
#define MOTOR_LEFT_2_TRIS      TRISDbits.TRISD1
    
///////////////////////////////////////////////////////////////    
//high current FET1
#define HC_FET_OUT_1            LATBbits.LATB12     //JP9
#define HC_FET_OUT_1_TRIS       TRISBbits.TRISB12
//high current FET2
#define HC_FET_OUT_2            LATBbits.LATB13     //JP10
#define HC_FET_OUT_2_TRIS       TRISBbits.TRISB13
    
///////////////////////////////////////////////////////////////    
//digits OE, LE, CLK, SDI       JP12
#define DIGITS_OE               LATGbits.LATG0
#define DIGITS_OE_TRIS          TRISGbits.TRISG0
#define DIGITS_LE               LATGbits.LATG1
#define DIGITS_LE_TRIS          TRISGbits.TRISG1
#define DIGITS_CLK              LATDbits.LATD7
#define DIGITS_CLK_TRIS         TRISDbits.TRISD7
#define DIGITS_SDI              LATDbits.LATD6
#define DIGITS_SDI_TRIS         TRISDbits.TRISD6
    
///////////////////////////////////////////////////////////////    
//color sense I2C - 2, JP13:
//color sense SCL  RA2  pin 58
#define COLOR_SENSE_SCL         LATAbits.LATA2
#define COLOR_SENSE_SCL_TRIS    TRISAbits.TRISA2
//color sense SDA RA3   pin 59   
#define COLOR_SENSE_SDA         LATAbits.LATA3         
#define COLOR_SENSE_SDA_TRIS    TRISAbits.TRISA3
//color sense LED RA4   pin 60
#define COLOR_SENSE_LED         LATAbits.LATA4
#define COLOR_SENSE_LED_TRIS    TRISAbits.TRISA4

///////////////////////////////////////////////////////////////    
//communications ports    
//debug serial port tx/rx   U2
#define DEBUG_TX                LATFbits.LATF5
#define DEBUG_TX_TRIS           TRISFbits.TRISF5
#define DEBUG_RX                PORTFbits.RF4
#define DEBUG_RX_TRIS           TRISFbits.TRISF4
    
//raspi serial port tx/rx   U1
#define PI_TX                   LATFbits.LATF8
#define PI_TX_TRIS              TRISFbits.TRISF8
#define PI_RX                   PORTFbits.RF2
#define PI_RX_TRIS              TRISFbits.TRISF2
    
//i2c
    //see color sensor
//spi port
#define SPI_CLK_TRIS            TRISGbits.TRISG6
#define SPI_MOSI_TRIS           TRISGbits.TRISG8    
#define SPI_MISO_TRIS           TRISGbits.TRISG7    
//spi barometric sensor select
#define SPI_BARO_CS             LATCbits.LATC4
#define SPI_BARO_CS_TRIS        TRISCbits.TRISC4
//spi accel select
#define SPI_ACCEL_CS            LATCbits.LATC3
#define SPI_ACCEL_CS_TRIS       TRISCbits.TRISC3
//spi magnetometer select
#define SPI_MAG_CS              LATCbits.LATC2
#define SPI_MAG_CS_TRIS         TRISCbits.TRISC2
//spi spare1 select
#define SPI_SPARE1_CS           LATCbits.LATC1
#define SPI_SPARE1_CS_TRIS      TRISCbits.TRISC1
//spi spare2 select
#define SPI_SPARE2_CS           LATEbits.LATE7
#define SPI_SPARE2_CS_TRIS      TRISEbits.TRISE7
//can tx/rx, can standby
#define CAN_TX                  LATFbits.LATF1
#define CAN_TX_TRIS             TRISFbits.TRISF1
#define CAN_RX                  PORTFbits.RF0
#define CAN_RX_TRIS             TRISFbits.TRISF0
#define CAN_STANDBY             LATAbits.LATA6    
#define CAN_STANDBY_TRIS        TRISAbits.TRISA6    
    
///////////////////////////////////////////////////////////////    
//analog inputs
//onboard temp sensor
#define aONB_TEMP_TRIS          TRISBbits.TRSIB2
#define aONB_TEMP_CH            2
//right motor temp  JP8
#define aRMOTOR_TEMP_TRIS       TRISBbits.TRSIB4
#define aRMOTOR_TEMP_CH         4    
//left motor temp   JP7
#define aLMOTOR_TEMP_TRIS       TRISBbits.TRSIB3
#define aLMOTOR_TEMP_CH         3    
//light sensor      JP16
#define aLIGHT_SENSE_TRIS       TRISBbits.TRSIB5
#define aLIGHT_SENSE_CH         5    
//battery 1
#define aBAT1_TRIS              TRISBbits.TRSIB10
#define aBAT1_CH                10    
//battery 2
#define aBAT2_TRIS              TRISBbits.TRSIB11
#define aBAT2_CH                11    
//spare 1
#define aSPARE1_TRIS            TRISBbits.TRSIB6
#define aSPARE1_CH              6    
//spare 2
#define aSPARE2_TRIS            TRISBbits.TRSIB7
#define aSPARE2_CH              7    
//spare 3
#define aSPARE3_TRIS            TRISBbits.TRSIB8
#define aSPARE3_CH              8    
//spare 4
#define aSPARE4_TRIS            TRISBbits.TRSIB9
#define aSPARE4_CH              9    


//Hardware related globals    
extern uint16 DelayTicks;    
extern uint32 SystemTicks;
extern PERIPHERAL_STATUS_T barometerStatus;    
    
//Hardware function prototypes
extern void InitializeHardware(void);
extern void DelayByCounts(uint16 delayValue);
extern void InitializeUART2(void);
extern void InitializeUART1(void);
extern void InitializeADC(void);
//extern void InitializeSoundPWM(void);
extern void SelectAnalogChannel(uint8 SelectChannel);
extern uint16 ADCRead(void);
extern uint8 simpleCommandReadSPI(uint8 command);
extern void readSPIcommand(uint8 cmdLen, uint8 *cmdBuffer, uint8 dataLen, uint8 * dataBuffer);
extern void writeSPIcommand(uint8 cmdLen, uint8 *cmdBuffer, uint8 dataLen, uint8 * dataBuffer);

#ifdef	__cplusplus
}
#endif

#endif	/* TRAKHARDWARE_H */

