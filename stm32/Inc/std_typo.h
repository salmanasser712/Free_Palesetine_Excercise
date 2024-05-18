/*
 * std_typo.h
 *
 *  Created on: Oct 20, 2023
 *      Author: Owner
 */

#ifndef STD_TYPOS_H_
#define STD_TYPOS_H_

#include <stdint.h>

#define uint8 unsigned char
#define u8 unsigned char
#define u16 uint16_t
#define u32 uint32_t
#define f32 float
#define f64 double

#define NULL ((void*)0)

typedef enum {
	ES_OK = 1,
	ES_NOK = 0
}ErrorStatus;



#endif /* STD_TYPOS_H_ */
