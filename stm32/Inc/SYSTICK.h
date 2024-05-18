#ifndef _SYSTICK_INT_H_
#define _SYSTICK_INT_H_

#define SYSTICK_ENABLE   0x00000001
#define SYSTICK_DISABLE  0xFFFFFFFE

#define OK       0
#define NOT_OK   1

#define SYSTICK_CLK_AHB  	   0x00000004
#define SYSTICK_CLK_AHB_DIV_8  0x00000000


#define SYSTICK_TICK_INT_ENABLE  0x00000002
#define SYSTICK_TICK_INT_DISABLE 0x00000000

typedef void (*systickcbf_t) (u8);
uint8_t SYSTICK_Init (void);
uint8_t SYSTICK_Start (void);
uint8_t SYSTICK_Stop (void);
uint8_t SYSTICK_SetCallback (systickcbf_t cbf);
uint8_t SYSTICK_SetTime (u32 timeus,u32 clk);
uint8_t SYSTICK_SetPrescale (u32 prescale);

#endif 
