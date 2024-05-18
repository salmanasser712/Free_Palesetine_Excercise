#include "std_typo.h"
#include "BitMath.h"
#include "ISR_Interrupts.h"
#include "GPIO_interface.h"
#include "LCD.h"
#include "delay.h"
#include "NVIC.h"

void WWDG_IRQHandler(void){
	uint8 str[] = {'W', 'D', 'G', ' ', 'S', 'T', 'A', 'R', 'T'};
	LCD_SendString1(0, 1, 9,  str);
	DNVIC_SetPendingIRQ(ADC3);
	_delay_ms(5000);
	uint8 str1[] = {'W', 'D', 'G', ' ', 'E', 'N', 'D'};
	LCD_SendString1(2, 1, 7,  str1);
	DNVIC_ClearPendingIRQ(WWDG);
}

void ADC3_IRQHandler(void){
	DIO_voidSetPinDirection(PORTA, PIN7, GPIO_OUTPUT_10MHZ_PP);
	DIO_voidSetPinValue(PORTA, PIN7, GPIO_HIGH);
	DNVIC_ClearPendingIRQ(ADC3);
}
