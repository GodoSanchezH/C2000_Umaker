

/**
 * main.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "F28x_Project.h"

#define LedAzul 31
#define LedRojo 34

int main(void)
{

    InitSysCtrl();
    InitGpio();

    GPIO_SetupPinMux(LedAzul,GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(LedAzul, GPIO_OUTPUT, GPIO_PUSHPULL);

    EALLOW;

    //gpio output
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;
    GpioDataRegs.GPBSET.bit.GPIO34 = 1;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34  = 1;
    //GPIO InPUT
    //GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 0;//habiñitado
    //GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;// habilitamos la resistencia pull up
    //GpioCtrlRegs.GPBDIR.bit.GPIO35 = 0;//input
    EDIS;


    GPIO_SetupPinMux(16,GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(16, GPIO_INPUT, GPIO_PULLUP);


    DINT;
    InitPieCtrl();
    IER = 0X00000000;
    IFR = 0X00000000;
    InitPieVectTable();

    EINT;//enable interrupt
    ERTM;//to enable debug events

    GpioDataRegs.GPADAT.bit.GPIO31 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO34 =1;
    for(;;){

        if (GPIO_ReadPin(16)== 0) {
            DELAY_US(100000);
            while(GPIO_ReadPin(16)== 0);

            GpioDataRegs.GPADAT.bit.GPIO31 =  ~GpioDataRegs.GPADAT.bit.GPIO31;
            GpioDataRegs.GPBDAT.bit.GPIO34 =  ~GpioDataRegs.GPBDAT.bit.GPIO34;
        }


    }

}
