/****************************************************************/
/*********************** STD LIB DIRECTIVES *********************/
/****************************************************************/

#include "BitMath.h"
#include "std_typo.h"
#include "RCC_int.h"
#include "RCC_config.h"
#include "RCC_reg.h"


/****************************************************************/
/*********************** Function Implementation  ***************/
/****************************************************************/


/****************************************************************/
/* Description    :  This function used to initialize RCC	    */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/

void MRCC_voidInit(void)
{
		#if 	CLOCK_TYPE == HSI
		/* internal 8 MHZ RC oscillator 			*/
		/*	HSI clock enable						*/
		MRCC->CR = MRCC->CR |  (1 << HSION);
				
		/*HSI selected as system clock		*/
		MRCC->CFGR = MRCC->CFGR | sys_HSI;
				

		/*	HSI Ready Flag					*/
		while(!GET_BIT(MRCC->CR, HSIRDY));
				
		
		#elif	CLOCK_TYPE == HSE
				/*	HSE clock enable				*/
				MRCC->CR = MRCC->CR | (1 << HSEON);

				/*HSE selected as system clock		*/
				MRCC->CFGR = MRCC->CFGR | sys_HSE;
				
				
				/*	HSE Ready Flag					*/
				while(!GET_BIT(MRCC->CR, HSERDY));
				
		#elif	CLOCK_TYPE == PLL
				/*	The PLL output frequency must not exceed 72 MHz */
				/*PLL selected as system clock		*/
				MRCC->CFGR = MRCC->CFGR | sys_PLL;
				
		/*PLL multiplication factor*/		
		#if CLOCK_FACTOR == MULTIPLY_BY_2
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_2 << 18);
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_3
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_3 << 18);
		
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_4
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_4 << 18);
		
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_5
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_5 << 18);
		
		
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_6
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_6 << 18);
		
		
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_7
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_7 << 18);
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_8
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_8 << 18);
		
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_9
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_9 << 18);
		
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_10
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_10 << 18);
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_11
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_11 << 18);
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_12
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_12 << 18);
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_13
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_13 << 18);
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_14
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_14 << 18);
		
		#elif CLOCK_FACTOR == MULTIPLY_BY_15
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_15 << 18);
	
		#elif CLOCK_FACTOR == MULTIPLY_BY_16
				MRCC->CFGR = MRCC->CFGR | (MULTIPLY_BY_16 << 18);
		
		
		#else
			#warning	"Wrong Multiplication factor!"
		
		#endif
		
					#if 	PLL_SOURCE	==	PLL_HSI_DIVIDED_BY_2
							/*PLL entry clock source is HSI divdided by 2		*/
							MRCC->CFGR = MRCC->CFGR | (0 << PLLSRC);
							
					#elif	PLL_SOURCE	==	PLL_HSE
							/*PLL entry clock source is HSE						*/
							MRCC->CFGR = MRCC->CFGR | (1 << PLLSRC);
							/*HSE divider for PLL entry : clock not divided 	*/
							MRCC->CFGR2 = MRCC->CFGR2 | PREDIV1_0;

					#elif	PLL_SOURCE	==	PLL_HSE_DIVIDED_BY_2
							/*PLL entry clock source is HSE						*/
							MRCC->CFGR = MRCC->CFGR | (1 << PLLSRC);
							/*HSE divider for PLL entry : clock divided		 	*/
							MRCC->CFGR2 = MRCC->CFGR2 | PREDIV1_2;
						
					#endif
		
				/*	PLL clock enable				*/
					MRCC->CR = MRCC->CR |  (1 << PLLON);
				
				/*	PLL Ready Flag					*/
					while(!GET_BIT(MRCC->CR, PLLRDY));
				
		#else
			
			#error		"Wrong Clock System type congiguration!"
		
		#endif
		/*FOR Clock Security System				*/
		#if		CLOCK_SECURITY_SYSTEM	==	OFF
				CLR_BIT(MRCC->CR, CSSON);
		
		#elif	CLOCK_SECURITY_SYSTEM	==	ON
				SET_BIT(MRCC->CR, CSSON);
				
		#else
				#warning	"Wrong clock security system configuration choice!"
		#endif
		
}

ErrorStatus MRCC_enumSetPeripheralClock(u8 Copy_u8PeripheralBus , u8 Copy_u8PeripheralName , u8 Copy_u8PeripheralState )
{
	ErrorStatus	LOC_enumstate = ES_OK ;
	switch( Copy_u8PeripheralState )
	{
		case	RCC_ENABLE 	:
							switch( Copy_u8PeripheralBus )
							{	
								case AHB  :	SET_BIT(MRCC->AHBENR, Copy_u8PeripheralName);break;
								case APB1 :	SET_BIT(MRCC->APB1ENR,Copy_u8PeripheralName);break;
								case APB2 : SET_BIT(MRCC->APB2ENR,Copy_u8PeripheralName);break;
								default	  :	break;
							}
							break;
		case	RCC_DISABLE :	
							switch( Copy_u8PeripheralBus )
							{	
								case AHB  :	CLR_BIT(MRCC->AHBENR, Copy_u8PeripheralName);
								break;
								case APB1 :	CLR_BIT(MRCC->APB1ENR,Copy_u8PeripheralName);
								break;
								case APB2 : CLR_BIT(MRCC->APB2ENR,Copy_u8PeripheralName);
								break;
								default	  :	
								break;
							}
							break;
		case	RCC_RESET	:	
							switch( Copy_u8PeripheralBus )
							{	
								case APB1 :	SET_BIT(MRCC->APB1RSTR,Copy_u8PeripheralName);break;
								case APB2 : SET_BIT(MRCC->APB2RSTR,Copy_u8PeripheralName);break;
								default	  :	break;
							}
							break;
	}
	return LOC_enumstate;
}
