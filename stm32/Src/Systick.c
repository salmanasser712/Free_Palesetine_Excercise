
#include "std_typo.h"
#include "BitMath.h"
#include "Systick_priv.h"
#include "SYSTICK.h"
#include "Systick_config.h"

systickcbf_t APPcbf ;
u8 flag = 1;
u8 counter = 0;

uint8_t SYSTICK_Init (void)
{
	/* CLK source and interrupt enable */
	SET_BIT(STK_CTRL, CLKSOURCE);
	SET_BIT(STK_CTRL, TICKINT);
	return OK;

}
uint8_t SYSTICK_Start (void)
{
	/* enable counter */
	SET_BIT(STK_CTRL, ENABLE);
	return OK;
}
uint8_t SYSTICK_Stop (void)
{
	/* disable counter */
	CLR_BIT(STK_CTRL, ENABLE);
	return OK;
}
uint8_t SYSTICK_SetCallback (systickcbf_t cbf)
{
	/* callback function */
	APPcbf = cbf;
	return OK;
}
uint8_t SYSTICK_SetTime (u32 timeus,u32 clk)
{
	/* add value to STK LOAD */ 
	STK_LOAD = timeus * clk;
	return OK;
}
void SysTick_Handler(void)
{
	counter++;
	APPcbf(flag);
	flag ^= 1;
}
