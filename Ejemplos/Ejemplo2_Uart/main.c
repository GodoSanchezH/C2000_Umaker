

/**
 * main.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "F2837xD_device.h"
#include "F28x_Project.h"
uint16_t outVal = 0;
void Init_UART(void);
void SCI_C2000_Print_Char(char C);
void SCI_C2000_Print_String(char *C);
void delay_ms(uint16_t ms);
void _delay_ms(uint16_t n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3180;j++)
 {}
}
/*
int main(void)
{
    InitSysCtrl();
    InitGpio();

    GPIO_SetupPinMux(31,GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(31, GPIO_OUTPUT, GPIO_PUSHPULL);

    //EINT;//enable interrupt
    ERTM;//to enable debug events
    for(;;){

        SCI_C2000_Print_String("Hola Mundo\n\r");
        outVal = ~outVal;
        GPIO_WritePin(31, outVal);
        _delay_ms(200);
    }

}
void delay_ms(uint16_t ms){
    ms = 1000*ms;
    DELAY_US(ms);
}
void Init_UART(void){

    EALLOW;
    ClkCfgRegs.LOSPCP.all = 0X0002; // Redefinimos , el Clock A 100MHZ
    CpuSysRegs.PCLKCR7.bit.SCI_B = 1;//HABILITAMOS EL Clock de SCI
    EDIS;





    EALLOW;

    GpioCtrlRegs.GPAMUX2.bit.GPIO18 =2;
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 =2;
    GpioCtrlRegs.GPADIR.bit.GPIO18 =1;
    GpioCtrlRegs.GPADIR.bit.GPIO19 =0;
    EDIS;

    EALLOW;

    ScibRegs.SCICCR.all = 0x0007;//8 , sin paridad 1 bit de stop
    ScibRegs.SCICTL1.bit.TXENA = 1;//Habilitamos EL tx
    ScibRegs.SCICTL1.bit.RXENA = 1;//Habilitamos el RX
    ScibRegs.SCICTL2.bit.TXINTENA = 0;//habilitamos la interrupcion por tx
    ScibRegs.SCICTL2.bit.RXBKINTENA = 0;//habilitamos la interrupcion por tx

    ScibRegs.SCIHBAUD.bit.BAUD =  0x0;
    ScibRegs.SCILBAUD.bit.BAUD =  0x6C;//115200 buadios

    ScibRegs.SCICTL1.all = 0x23;


    EDIS;



}



void SCI_C2000_Print_Char(char C){

    while(ScibRegs.SCICTL2.bit.TXRDY==0);
    ScibRegs.SCITXBUF.all = C;

}
void SCI_C2000_Print_String(char *C){

    char *ptr;
    ptr=C;

    while(*ptr)
        SCI_C2000_Print_Char(*ptr++);

}
*/
Uint16 LoopCount;

//
// Function Prototypes
//
void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);

//
// Main
//
void main(void)
{
    Uint16 ReceivedChar;
    char *msg;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
   InitGpio();

//
// For this example, only init the pins for the SCI-A port.
//  GPIO_SetupPinMux() - Sets the GPxMUX1/2 and GPyMUX1/2 register bits
//  GPIO_SetupPinOptions() - Sets the direction and configuration of the GPIOS
// These functions are found in the F2837xD_Gpio.c file.
//

   GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2);
   GPIO_SetupPinOptions(18,GPIO_OUTPUT, GPIO_PUSHPULL);
   GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2);
   GPIO_SetupPinOptions(19, GPIO_INPUT, GPIO_ASYNC);


//
// Step 3. Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts
//
   DINT;

//
// Initialize PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
   InitPieCtrl();

//
// Disable CPU __interrupts and clear all CPU __interrupt flags:
//
   IER = 0x0000;
   IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
   InitPieVectTable();

//
// Step 4. User specific code:
//
   LoopCount = 0;

   scia_fifo_init();       // Initialize the SCI FIFO
   scia_echoback_init();   // Initialize SCI for echoback

   msg = "\r\n\n\nHello World!\0";
   scia_msg(msg);

   msg = "\r\nYou will enter a character, and the DSP will echo it back! \n\0";
   scia_msg(msg);

   for(;;)
   {
       msg = "\r\nEnter a character: \0";
       scia_msg(msg);

       //
       // Wait for inc character
       //
       while(SciaRegs.SCIFFRX.bit.RXFFST == 0) { } // wait for empty state

       //
       // Get character
       //
       ReceivedChar = SciaRegs.SCIRXBUF.all;

       //
       // Echo character back
       //
       msg = "  You sent: \0";
       scia_msg(msg);
       scia_xmit(ReceivedChar);

       LoopCount++;
   }
}

//
//  scia_echoback_init - Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F,
//                       default, 1 STOP bit, no parity
//
void scia_echoback_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //

    SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

    //
    // SCIA at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.
    //
    SciaRegs.SCIHBAUD.all = 0x0002;
    SciaRegs.SCILBAUD.all = 0x008B;

    SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
}

//
// scia_xmit - Transmit a character from the SCI
//
void scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciaRegs.SCITXBUF.all =a;
}

//
// scia_msg - Transmit message via SCIA
//
void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}

//
// scia_fifo_init - Initialize the SCI FIFO
//
void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all = 0x0;
}

//
// End of file
//

