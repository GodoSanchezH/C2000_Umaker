

#include "LCD.h"


Ubicacion Cursor;

void LCD_C2000_DataBus(uint_fast8_t a){
    // D4 D5 D6 D7
    //0000 1000
    if(a & 0x1) D4_ON; else D4_OFF;
    //0000 0100
    if(a & 0x2) D5_ON; else D5_OFF;
    //0000 0010
    if(a & 0x4) D6_ON; else D6_OFF;
    //0000 0001
    if(a & 0x8) D7_ON; else D7_OFF;
}
void LCD_C2000_Cmd(uint_fast8_t a){
    E_OFF;
    E_ON;
    LCD_C2000_DataBus(a);
    DELAY_US(1000);
    E_OFF;

}
void LCD_C2000_Init(void){


    LCD_C2000_Cmd(0x03);
    LCD_C2000_Cmd(0x03);
    LCD_C2000_Cmd(0x03);
    LCD_C2000_Cmd(0x02);
    LCD_C2000_Cmd(0x02);
    LCD_C2000_Cmd(0x08);
    LCD_C2000_Cmd(0x00);
    LCD_C2000_Cmd(0x08);
    LCD_C2000_Cmd(0x00);
    LCD_C2000_Cmd(0x01);
    LCD_C2000_Cmd(0x00);
    LCD_C2000_Cmd(0x0C);
}

void LCD_C2000_SetCursor(uint_fast8_t x , uint_fast8_t y){
    RS_OFF;
    uint_fast8_t m,n;
    switch(y){
        case Fila1:
            m = 0x80+x;
            n = (0x80+x)>>4;
            LCD_C2000_Cmd(n);
            LCD_C2000_Cmd(m);
        break;
        case Fila2:
            m = 0xC0+x;
            n = (0xC0+x)>>4;
            LCD_C2000_Cmd(n);
            LCD_C2000_Cmd(m);
        break;
        case Fila3:
             m = 0x94+x;
            n = (0x94+x)>>4;
            LCD_C2000_Cmd(n);
            LCD_C2000_Cmd(m);
        break;
        case Fila4:
            m = 0xD4+x;
            n = (0xD4+x)>>4;
            LCD_C2000_Cmd(n);
            LCD_C2000_Cmd(m);
        break;
    }
}
void LCD_C2000_Print_Char(char a){

    uint_fast8_t m,n;
    m = a;
    n = (a>>4);
    RS_ON;
    LCD_C2000_Cmd(n);
    LCD_C2000_Cmd(m);
}
void LCD_C2000_Print_String(char *a){
    char *ptr;
    ptr = a;
    while(*ptr)
        LCD_C2000_Print_Char(*ptr++);

}
void LCD_C2000_New_Char(uint_fast8_t a,uint_fast8_t b,uint_fast8_t c,uint_fast8_t d,uint_fast8_t e,uint_fast8_t f,uint_fast8_t g,uint_fast8_t h,uint_fast8_t i)
{
 uint_fast8_t m,n;
    switch(a){
        case 1:
         LCD_C2000_Cmd(0x04);
         LCD_C2000_Cmd(0x00);
        RS_ON;
        m=b>>4;
        n=b;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=c>>4;
        n=c;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=d>>4;
        n=d;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=e>>4;
        n=e;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=f>>4;
        n=f;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=g>>4;
        n=g;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=h>>4;
        n=h;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=i>>4;
        n=i;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        RS_OFF;
        LCD_C2000_Cmd(0x00);
        LCD_C2000_Cmd(0x01);
        DELAY_US(100000);
        break;
        case 2:
            LCD_C2000_Cmd(0x04);
            LCD_C2000_Cmd(0x08);
            RS_ON;
        m=b>>4;
        n=b;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=c>>4;
        n=c;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=c>>4;
        n=c;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=d>>4;
        n=d;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=e>>4;
        n=e;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=f>>4;
        n=f;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=g>>4;
        n=g;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=h>>4;
        n=h;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=i>>4;
        n=i;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        RS_OFF;
        LCD_C2000_Cmd(0x00);
        LCD_C2000_Cmd(0x01);
        DELAY_US(100000);
        break;
        case 3:
            LCD_C2000_Cmd(0x04);
            LCD_C2000_Cmd(0xFF);
            RS_ON;
        m=b>>4;
        n=b;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=c>>4;
        n=c;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=d>>4;
        n=d;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=e>>4;
        n=e;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=f>>4;
        n=f;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=g>>4;
        n=g;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=h>>4;
        n=h;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        m=i>>4;
        n=i;
        LCD_C2000_Cmd(m);
        LCD_C2000_Cmd(n);
        RS_OFF;
        LCD_C2000_Cmd(0x00);
        LCD_C2000_Cmd(0x01);
        DELAY_US(100000);
        break;
    }
}
void LCD_C2000_Write_New_Char(uint_fast8_t a){
   RS_ON;
    LCD_C2000_Cmd(0x00);
    LCD_C2000_Cmd(a-1);
    RS_OFF;
}
void LCD_C2000_Clear(void){
    RS_OFF;
    LCD_C2000_Cmd(0x00);
    LCD_C2000_Cmd(0x01);
}
void LCD_C2000_Home(void){
    RS_OFF;
    LCD_C2000_Cmd(0x00);
    LCD_C2000_Cmd(0x02);
}






