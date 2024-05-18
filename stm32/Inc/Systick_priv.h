#ifndef _SYSTICK_PRIV_H_
#define _SYSTICK_PRIV_H_

#define STK_CTRL	*((volatile uint32_t*)0xE000E010)
#define CLKSOURCE                                  2
#define TICKINT                                    1
#define ENABLE                                     0

#define STK_LOAD	*((volatile uint32_t*)0xE000E014)
#define STK_VAL		*((volatile uint32_t*)0xE000E018)

#endif

