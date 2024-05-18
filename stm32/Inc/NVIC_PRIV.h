#ifndef DNVIC_PRIV_H_
#define DNVIC_PRIV_H_


/**
 * @def 	NVIC_BASE_ADDRESS
 * @brief 	NVIC peripheral base address 
 */
#define NVIC_BASE_ADDRESS  (( NVIC_t*) 0XE000E100)
/**
 * @def 	SCB_AIRCR
 * @brief 	NVIC Application Interrupt and Reset Control Register 
 */
#define SCB_AIRCR *((volatile u32*) 0XE000ED0C)

#define SYSRESETREQ       2

/**
 * @def 	SCB_VTOR
 * @brief 	Vector Table Offset register
 */
#define SCB_VTOR  *((volatile u32*) 0xE000ED08)


#define BASEPRI   *((volatile u32*) 0xE000ED24)



/**
 * @typedef		NVIC_t 
 * @brief		Struct of All Registers in NVIC Driver	
 */
typedef struct
{
	u32 ISER[8];
	u32 Reserved[24];
	u32 ICER[8];
	u32 Reserved1[24];
	u32 ISPR[8];
	u32 Reserved2[24];
	u32 ICPR[8];
	u32 Reserved3[24];
	u32 IABR[8];
	u32 Reserved4[56];
	u8 IPR[240];
}NVIC_t;

/**
 * @brief NV pointer to struct NVIC_t 
 */
NVIC_t   *NV=NVIC_BASE_ADDRESS;

#endif
