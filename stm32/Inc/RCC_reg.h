#ifndef RCC_PRIV_H
#define	RCC_PRIV_H

typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
	
}RCC;


//CR
#define  HSION     0
#define  HSIRDY    1
#define  HSEON     16
#define  HSERDY    17
#define  PLLON     24
#define  PLLRDY    25
#define  CSSON     19

#define sys_HSI     0
#define sys_HSE     1
#define sys_PLL     2

#define PLLSRC      16

#define PREDIV1_0     0
#define PREDIV1_2     1

#define MRCC	((volatile RCC * )0x40021000)

#endif
