#include <xc.h>
#include "common.h"
#include "trakhardware.h"
#include "trakDigits.h"


//STP16DPP LED digit driver


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

unsigned int DigitBuffer;
unsigned int DigitBufferTest;
unsigned char LeftDigitValue;
unsigned char RightDigitValue;
unsigned char LeftDigitDefault;
unsigned char RightDigitDefault;
unsigned char LeftDigit;
unsigned char RightDigit;
unsigned char LeftDP;
unsigned char RightDP;
unsigned char LeftBuffer[10];
unsigned char RightBuffer[10];



void InitDigit(void)
{
	LeftBuffer[0] = cLDIGIT_0;
	LeftBuffer[1] = cLDIGIT_1;
	LeftBuffer[2] = cLDIGIT_2;
	LeftBuffer[3] = cLDIGIT_3;
	LeftBuffer[4] = cLDIGIT_4;
	LeftBuffer[5] = cLDIGIT_5;
	LeftBuffer[6] = cLDIGIT_6;
	LeftBuffer[7] = cLDIGIT_7;
	LeftBuffer[8] = cLDIGIT_8;
	LeftBuffer[9] = cLDIGIT_9;

	RightBuffer[0] = cRDIGIT_0;
	RightBuffer[1] = cRDIGIT_1;
	RightBuffer[2] = cRDIGIT_2;
	RightBuffer[3] = cRDIGIT_3;
	RightBuffer[4] = cRDIGIT_4;
	RightBuffer[5] = cRDIGIT_5;
	RightBuffer[6] = cRDIGIT_6;
	RightBuffer[7] = cRDIGIT_7;
	RightBuffer[8] = cRDIGIT_8;
	RightBuffer[9] = cRDIGIT_9;
		
	
}


//#define DIGITS_OE               LATGbits.LATG0
//#define DIGITS_LE               LATGbits.LATG1
//#define DIGITS_CLK              LATDbits.LATD7
//#define DIGITS_SDI              LATDbits.LATD6



//enter with digit values in Left/RightDigitValue 
void DisplayDigits(void)
{
	unsigned char tempchar;
	int i;


	LeftDigit = LeftBuffer[LeftDigitValue];
	RightDigit = RightBuffer[RightDigitValue];
	
	if(LeftDP == TRUE)
	{
		LeftDigit = LeftDigit + cLDIGIT_DP;
	}
	else
	{
		tempchar = 0xFF;
		tempchar = tempchar ^ cLDIGIT_DP;
		LeftDigit = LeftDigit & tempchar;		
	}

/*	if(RightDP == TRUE)
	{
		RightDigit = RightDigit + cRDIGIT_DP;
	}
	else
	{
		tempchar = 0xFF;
		tempchar = tempchar ^ cRDIGIT_DP;
		RightDigit = RightDigit & tempchar;		
	}*/

	
	DigitBuffer = 0;
	//DigitBuffer = LeftDigit << 8;
	//DigitBuffer = DigitBuffer + RightDigit;
	DigitBuffer = RightDigit << 8;
	DigitBuffer = DigitBuffer + LeftDigit;

	DIGITS_CLK = 0;
	DIGITS_SDI = 0;

	//DigitBuffer = DigitBufferTest;
	//DigitBufferTest = DigitBufferTest>>1;
	//if(DigitBufferTest == 0) DigitBufferTest = 0x8000;
	
	for(i=0;i<16;i++)	
	{
		DIGITS_CLK = 0;

		if(DigitBuffer & 0x01)
		{
			DIGITS_SDI = 1;	
		}
		else
		{
			DIGITS_SDI = 0;
		}
			
		DIGITS_CLK = 1;
		//delay here?
		//delay here?		

		DigitBuffer = DigitBuffer>>1;
		
	}
	DIGITS_CLK = 0;
	
	DIGITS_SDI = 0;

//	LED_CLK = 1;
	//delay here?
	DIGITS_LE = 1;	

	//delay here?		
	DIGITS_LE = 0;
	//delay here?		

	DIGITS_CLK = 0;
	//delay here?		

	DIGITS_OE = 0;	


}




//enter with digit values in Left/RightDigitValue 
void ClearDigits(void)
{
//	unsigned char tempchar;
	int i;

	
	DigitBuffer = 0;

	DIGITS_CLK = 0;
	DIGITS_SDI = 0;

	
	for(i=0;i<16;i++)	
	{
		DIGITS_CLK = 0;

		if(DigitBuffer & 0x01)
		{
			DIGITS_SDI = 1;	
		}
		else
		{
			DIGITS_SDI = 0;
		}
			
		DIGITS_CLK = 1;
		//delay here?
		//delay here?		

		DigitBuffer = DigitBuffer>>1;
		
	}
	DIGITS_CLK = 0;
	
	DIGITS_SDI = 0;

//	LED_CLK = 1;
	//delay here?
	DIGITS_LE = 1;	

	//delay here?		
	DIGITS_LE = 0;
	//delay here?		

	DIGITS_CLK = 0;
	//delay here?		

	DIGITS_OE = 0;	


}

void CountUp(void)
{
	RightDigitValue++;
	if(RightDigitValue>9)
	{
		RightDigitValue = 0;
		LeftDigitValue++;
		if(LeftDigitValue > 9) LeftDigitValue = 0;
	}

}

void CountDown(void)
{
	if(RightDigitValue == 0)
	{
		if(LeftDigitValue == 0)
		{
			RightDigitValue = RightDigitDefault;
			LeftDigitValue = LeftDigitDefault;
		}
		else
		{
			LeftDigitValue--;
			RightDigitValue = 9;
		}
	}
	else
	{
		RightDigitValue--;
	}
}
