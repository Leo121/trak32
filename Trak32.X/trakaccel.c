#include <xc.h>
#include "trak32.h"
#include "trakaccel.h"

void initAccelSPI(void)
{
    SPI2BRG = 0x01;     //24MHz Fpb = 6MHz SPI clock, accel max clk = 10MHz
        
    SPI2CONbits.SMP = 1;
    SPI2CONbits.CKE = 1;
    SPI2CONbits.CKP = 1;
    SPI2CONbits.MSTEN = 1;
    SPI2CONbits.ON = 1;     //enable SPI module
}

