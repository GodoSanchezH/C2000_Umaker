/*
 * LCD.h
 *
 *  Created on: 23 abr. 2023
 *      Author: gssan
 */

#ifndef LCD_H_
#define LCD_H_

#include "F28x_Project.h"
#include "stdint.h"

#define E_ON   GPIO_WritePin(2, 1)
#define E_OFF  GPIO_WritePin(2, 0)
#define RS_ON GPIO_WritePin(3, 1)
#define RS_OFF GPIO_WritePin(3, 0)
#define D4_ON GPIO_WritePin(4, 1)
#define D4_OFF GPIO_WritePin(4, 0)
#define D5_ON GPIO_WritePin(5, 1)
#define D5_OFF GPIO_WritePin(5,0)
#define D6_ON GPIO_WritePin(6, 1)
#define D6_OFF GPIO_WritePin(6,0)
#define D7_ON GPIO_WritePin(7, 1)
#define D7_OFF GPIO_WritePin(7, 0)

typedef enum{
    Fila1=0,
    Fila2,
    Fila3,
    Fila4
}Ubicacion;


void LCD_C2000_Cmd(uint_fast8_t a);
void LCD_C2000_DataBus(uint_fast8_t a);
void LCD_C2000_Init(void);
void LCD_C2000_SetCursor(uint_fast8_t x , uint_fast8_t y);
void LCD_C2000_Print_Char(char a);
void LCD_C2000_Print_String(char *a);
void LCD_C2000_New_Char(uint_fast8_t a,uint_fast8_t b,uint_fast8_t c,uint_fast8_t d,uint_fast8_t e,uint_fast8_t f,uint_fast8_t g,uint_fast8_t h,uint_fast8_t i);
void LCD_C2000_Write_New_Char(uint_fast8_t a);
void LCD_C2000_Clear(void);
void LCD_C2000_Home(void);



#endif /* LCD_H_ */
