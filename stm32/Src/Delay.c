#include "std_typo.h"
#include "Delay.h"

void _delay_ms(u32 Value)
{
	u32 i;
	u32 count=(u32)(float)(Value-TM)/T1;
	
	for(i=0;i<count;i++)
	{
		
		asm("NOP");
		
	}
	
}
