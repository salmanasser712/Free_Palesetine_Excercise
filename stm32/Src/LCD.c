//#include "Main.h"
//#include "Port.h"
//#include "Util.h"
#include "std_typo.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "LCD.h"
#include "delay.h"

#define LCD_CONFIG_WORD             (0x30)

#define LCD_CLR                     (0x01)

#define LCD_CURSOR_HOME             (0x02)

#define LCD_SET_ENTRY_MODE          (0x40)
#define LCD_INCREMENT_CURSOR        (0x02)
#define LCD_DECREMENT_CURSOR        (0x00)
#define LCD_DISPLAY_SHIFT_ON        (0x01)
#define LCD_DISPLAY_SHIFT_OFF       (0x00)

#define LCD_DISPLAY_CONTROL         (0x08)
#define LCD_DISPLAY_ON              (0x04)
#define LCD_DISPLAY_OFF             (0x00)
#define LCD_CURSOR_ON               (0x02)
#define LCD_CURSOR_OFF              (0x00)
#define LCD_CURSOR_BLINK_ON         (0x01)
#define LCD_CURSOR_BLINK_OFF        (0x00)

#define LCD_CURSOR_DISPLAY_CONTROL  (0x10)
#define LCD_SHIFT_CURSOR            (0x00)
#define LCD_SHIFT_DISPLAY           (0x08)
#define LCD_SHIFT_LEFT              (0x00)
#define LCD_SHIFT_RIGHT             (0x04)

#define LCD_FUNCTION_SET            (0x20)
#define LCD_DATA_LENGTH_4           (0x00)
#define LCD_DATA_LENGTH_8           (0x10)
#define LCD_ONE_LINE                (0x00)
#define LCD_TWO_LINES               (0x08)
#define LCD_SMALL_FONT              (0x00)
#define LCD_LARGE_FONT              (0x04)

#define line1_add                   (0x00)
#define line2_add                   (0x40)
#define line3_add                   (0x14)
#define line4_add                   (0x54)

#define LCD_SET_CGRAM_ADDRESS       (0x40)

#define LCD_SET_DDRAM_ADDRESS       (0x80)

#define LCD_DDRAM_LINE_SIZE         (0x28)
#define LCD_DDRAM_LINE_2_ADDRESS    (0x40)

static void LCD_SendCommand(uint8 command);
void LCD_SendData(uint8 character);
static void write_data(uint8 data);
void SET_PIN();

void LCD_Init(void)
{
	/* Add your code here */
	/* Initialize Pins */

	DIO_voidSetPinDirection(LCD_PORT, LCD_PIN0, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_PORT, LCD_PIN1, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_PORT, LCD_PIN2, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(LCD_PORT, LCD_PIN3, GPIO_OUTPUT_10MHZ_PP);

	DIO_voidSetPinDirection(FLAG_PORT, RS_PIN, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinDirection(FLAG_PORT, EN_PIN, GPIO_OUTPUT_10MHZ_PP);
	_delay_ms(15);
	/* Initialization sequence */
	LCD_SendCommand(0x2);
	_delay_ms(15);
	LCD_SendCommand(0x02);
	_delay_ms(15);
	/* Initial LCD commands */
	/* Select data length = 8 bits, 2 lines LCD and small font */
	uint8 comd = LCD_FUNCTION_SET | LCD_DATA_LENGTH_4 | LCD_TWO_LINES | LCD_SMALL_FONT;
	LCD_SendCommand(comd);
	_delay_ms(15);
	/* Turn display , cursor and blinking OFF */
	comd = LCD_DISPLAY_ON | LCD_CURSOR_ON  | LCD_CURSOR_BLINK_OFF | LCD_DISPLAY_CONTROL;
	LCD_SendCommand(comd);
	_delay_ms(15);
	/* Increment cursor and turn off display shift */
	comd = LCD_INCREMENT_CURSOR | LCD_DISPLAY_SHIFT_OFF | LCD_SET_ENTRY_MODE ;
	LCD_SendCommand(comd);
	_delay_ms(15);
	/* Clear display */
	comd = LCD_CLR;
	LCD_SendCommand(comd);
	_delay_ms(15);

	/* End of your code !*/
}

void LCD_clear(){
	uint8 comd = LCD_CLR;
	LCD_SendCommand(comd);
	_delay_ms(10);
}
void LCD_SendChar(uint8 character, uint8 line, uint8 column)
{
	/* Add your code here */
	/* Change position and send character */
	LCD_GoTo(line, column);

	_delay_ms(10);

	LCD_SendData(character);

	/* End of your code !*/

}

void LCD_SendString1(uint8 line, uint8 col, uint8 len, uint8 * str){
	LCD_GoTo(line, col);
	uint8 i = 0;

	/* Add your code here */
	/* Clear screen and send character by character to the LCD */
	for( ; i < len; i++){
		LCD_SendData(str[i]);
	}
	/* End of your code !*/
}

void LCD_SendString(uint8 len, uint8 * str)
{
	uint8 i = 0;

	/* Add your code here */
	/* Clear screen and send character by character to the LCD */
	for( ; i < len; i++){
		LCD_SendData(str[i]);
	}
	/* End of your code !*/
}

static void LCD_SendCommand(uint8 command)
{
	/* Add your code here */
	SET_PIN();
	_delay_ms(10);
	DIO_voidSetPinValue(FLAG_PORT, RS_PIN, 0);
	write_data(command);
	/* End of your code !*/

}
static void write_data(uint8 data){
	uint8 low = data & 0x0F;
	uint8 high = (data >> 4) & 0x0F;
	//setpinvalue(FLAG_PORT, EN_PIN, 1);
	//_delay_ms(20);
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN0, (high & 1));
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN1, ((high >> 1) & 1));
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN2, ((high >> 2) & 1));
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN3, ((high >> 3) & 1));
	DIO_voidSetPinValue(FLAG_PORT, EN_PIN, 1);
	_delay_ms(10);
	DIO_voidSetPinValue(FLAG_PORT, EN_PIN, 0);
	_delay_ms(10);

	//setpinvalue(FLAG_PORT, EN_PIN, 1);
	//_delay_ms(20);
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN0, (low & 1));
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN1, ((low >> 1) & 1));
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN2, ((low >> 2) & 1));
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN3, ((low >> 3) & 1));
	DIO_voidSetPinValue(FLAG_PORT, EN_PIN, 1);
	_delay_ms(10);
	DIO_voidSetPinValue(FLAG_PORT, EN_PIN, 0);
	_delay_ms(10);
}

void SET_PIN(){
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN0, 0);
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN1, 0);
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN2, 0);
	DIO_voidSetPinValue(LCD_PORT, LCD_PIN3, 0);
}

void LCD_SendData(uint8 character)
{
	/* Add your code here */
	SET_PIN();
	_delay_ms(10);
	DIO_voidSetPinValue(FLAG_PORT, RS_PIN, 1);
	write_data(character);
	/* End of your code !*/
}

void LCD_GoTo(uint8 line, uint8 column)
{

	uint8 address = 0;
	/* Calculate address in DDRAM */
	switch(line){
	case 0:
		address = line1_add + column;
		break;
	case 1:
		address = line2_add + column;
		break;
	case 2:
		address = line3_add + column;
		break;
	case 3:
		address = line4_add + column;
		break;
	}

	uint8 comd = address | LCD_SET_DDRAM_ADDRESS;

	/* Send address to LCD */

	LCD_SendCommand(comd);

	/* End of your code !*/


}
void reverse(uint8 *res, uint8 len){
	for(uint8 i = 0; i < len / 2; i++){
		uint8 temp = res[i];
		res[i] = res[len - 1 - i];
		res[len - 1 - i] = temp;
	}
}

ErrorStatus get_char(u32 val, uint8 *res, uint8 *res_len, uint8 sign){
	ErrorStatus er = ES_OK;
	uint8 i = 0;
	if(val == 0) {
		res[0] = 0 + '0';
		i++;
	}
	while(val){
		res[i++] = (uint8)(val % 10) + '0';
		val /= 10;
	}
	if(sign){
		res[i++] = '-';
		res[i++] = ' ';
	}
	*res_len = i;
	reverse(res, *res_len);
	return er;
}


void LCD_voidWriteInt(u8 Data, u8 sign){
	uint8 res[20], res_len = 0;
	get_char((u32) Data, res, &res_len, sign);
	LCD_SendString(res_len, res);
}

void Key_Init(){

}

void Dis_GameOver(){

}

void Dis_Border(){

}


