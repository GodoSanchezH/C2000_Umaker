

/**
 * main.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "F28x_Project.h"

#define led 34
uint16_t outVal = 0;
int main(void)
{

    InitSysCtrl();
    InitGpio();

    GPIO_SetupPinMux(led, CPU1, 0);
    GPIO_SetupPinOptions(led, GPIO_OUTPUT, GPIO_PUSHPULL);

    InitPieCtrl();
    InitPieVectTable();
    EINT;//enable interrupt
    ERTM;//to enable debug events

    for(;;){
        outVal = ~outVal;
        GPIO_WritePin(led, outVal);
        DELAY_US(500000);

    }

}
