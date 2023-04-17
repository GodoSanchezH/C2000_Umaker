

/**
 * main.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "F28x_Project.h"

int main(void)
{

    InitSysCtrl();
    InitGpio();

    EINT;//enable interrupt
    ERTM;//to enable debug events


    for(;;){


    }

}
