/*
 * KEY.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Owner
 */

#ifndef KEY_H_
#define KEY_H_

#include "std_typo.h"
#include "DIO/DIO_INT.h"

typedef enum
{
	 COL_PIN0 = 7,
	 COL_PIN1 = 6,
	 COL_PIN2 = 5,
	 COL_PIN3 = 3
}COLS;

typedef enum
{
	 ROW_PIN0 = 5,
	 ROW_PIN1 = 4,
	 ROW_PIN2 = 3,
	 ROW_PIN3 = 2
}ROWS;


#define COL_PORT  PORTD
#define ROW_PORT  PORTC

void KEYS_Init(void);
uint8 check(uint8 *value);
uint8 Get_value();
void init_arr(uint8 *arr, uint8 len);
ERROR_status get_char(u32 val, uint8 *res, uint8 *res_len, uint8 sign);
ERROR_status CALC(uint8 *input, uint8 in_len, uint8 *res, uint8 *res_len);


#endif /* KEY_H_ */
