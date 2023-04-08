

/**
 * main.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "device.h"
#include "driverlib.h"

int main(void)
{
    Device_init();//Inicializamos el dispositivo

    Device_initGPIO();//Inicializamos la GPIO

    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);


    //Inicializamos las Interrupciones
    Interrupt_initModule();
    //Interrupciones Vectoriales
    Interrupt_initVectorTable();

    EINT;//enable interrupt
    ERTM;//to enable debug events
    for(;;){

        GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);
        GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);
        DEVICE_DELAY_US(500000);
        GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
        GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0);
        DEVICE_DELAY_US(500000);
    }

}
