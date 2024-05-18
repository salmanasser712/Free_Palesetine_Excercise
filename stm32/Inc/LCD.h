#ifndef __LCD_H__
#define __LCD_H__

#include "std_typo.h"
#include "GPIO_interface.h"

#define LCD_LINE_1          (0)
#define LCD_LINE_2          (1)
#define LCD_LINE_WIDTH      (16)

#define PIN_OUTPUT 0x1
#define PIN_INPUT  0x0

#define LCD_PIN0     0
#define LCD_PIN1     1
#define LCD_PIN2     2
#define LCD_PIN3     3

#define RS_PIN       7
#define EN_PIN       6

#define LCD_PORT     PORTB
#define FLAG_PORT    PORTB



void LCD_Init(void);
void LCD_clear(void);
void LCD_SendData(uint8 character);
void LCD_SendChar(uint8 character, uint8 line, uint8 column);
void LCD_SendString1(uint8 line, uint8 col, uint8 len, uint8 * str);
void LCD_SendString(uint8 len, uint8 * str);
void LCD_GoTo(uint8 line, uint8 column);
void LCD_voidWriteInt(u8 Data, u8 sign);


#endif // __LCD_H__
