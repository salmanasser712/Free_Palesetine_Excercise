#ifndef DNVIC_H_
#define DNVIC_H_


/**
 * @def 	PASSWORD_MASK
 * @brief 	Password to make Software reset 
 */
#define PASSWORD_MASK  0X05FA0000

/**
 * @def 	FLASH_BASE_ADDRESS
 * @brief 	Base Address of Flash
 */
#define FLASH_BASE_ADDRESS 0x08000000

/**
 * @def 	OFFSET_POSITION
 * @brief 	used in shifting offest value to be corresponding for offest bits in Regsiter 
 */
#define OFFSET_POSITION 0x08

/**
 * @def 	RESET_MASK
 * @brief 	Base Address of Flash
 */
#define RESET_MASK 0x04




/**
 * @def     Peripheral 
 * @brief   Numbers asssigned to peripherals is the offest of them in vector table array 
 * 
 */
#define WWDG				0
#define PVD					1
#define TAMPER				2
#define RTC					3
#define FLASH				4
#define RCCINT				5
#define EXTI0				6
#define EXTI1				7
#define EXTI2				8
#define EXTI3				9
#define EXTI4				10
#define DMA1_CHANNEL1		11
#define DMA1_CHANNEL2		12
#define DMA1_CHANNEL3		13
#define DMA1_CHANNEL4		14
#define DMA1_CHANNEL5		15
#define DMA1_CHANNEL6		16
#define DMA1_CHANNEL7		17
#define ADC1_2				18
#define USB_HP_CAN_TX		19
#define USB_LP_CAN_RX0		20
#define CAN_RX1				21
#define CAN_SCE				22
#define EXTI9_5				23
#define TIM1_BRK			24
#define TIM1_UP				25
#define TIM1_TRG_COM		26
#define TIM1_CC				27
#define TIM2				28
#define TIM3				29
#define TIM4				30
#define I2C1_EV				31
#define I2C1_ER				32
#define I2C2_EV				33
#define I2C2_ER				34
#define SPI1				35
#define SPI2				36
#define USART1				37
#define USART2				38
#define USART3				39
#define EXTI15_10			40
#define RTCALARM			41
#define USBWAKEUP			42
#define TIM8_BRK			43
#define TIM8_UP				44
#define TIM8_TRG_COM		45
#define TIM8_CC				46
#define ADC3				47
#define FSMC				48
#define SDIO				49
#define TIM5				50
#define SPI3				51
#define UART4				52
#define UART5				53
#define TIM6				54
#define TIM7				55
#define DMA2_CHANNEL1		56
#define DMA2_CHANNEL2		57
#define DMA2_CHANNEL3		58
#define DMA2_CHANNEL4_5		59
#define AIRCR_WRITE  0x5FA0000


/**
 * @brief   Function to Enable peripheral Interrupt 
 * @param   IRQn Variable of u8 , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @return  OK | NOT_OK
 */
u8 DNVIC_EnableIRQ(u8 IRQn);

/**
 * @brief   Function to Disable peripheral Interrupt 
 * @param   IRQn Variable of u8 , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @return  OK | NOT_OK
 */
u8 DNVIC_DisableIRQ(u8 IRQn);

/**
 * @brief   Function to Set Peripheral Pending Interrupt Flag By Software 
 * @param   IRQn Variable of u8 , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @return  OK | NOT_OK
 */
u8 DNVIC_SetPendingIRQ (u8 IRQn);

/**
 * @brief   Function to Reset Peripheral Pending Interrupt Flag By Software 
 * @param   IRQn Variable of u8 , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @return  OK | NOT_OK
 */
u8 DNVIC_ClearPendingIRQ (u8 IRQn);

/**
 * @brief   Function to get Pending Flag Value 
 * @param   IRQn Variable of u8 , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @param   Val  pointer  of u8 , Pending Flag which to be read assigned to pointer
 * @return  OK | NOT_OK
 */
u8 DNVIC_GetPendingIRQ (u8 IRQn, u8 *Val);

/**
 * @brief   Function to get Active Flag Value 
 * @param   IRQn Variable of u8 , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @param   Val  pointer  of u8 , Active Flag which to be read assigned to pointer
 * @return  OK | NOT_OK
 */
u8 DNVIC_GetActive (u8 IRQn, u8 *Val);

/**
 * @def    NUM_PREEMPTION_NUM_SUBGROUP
 * @brief  define Groups and Subgroups ex (ALL_PREEMPTION , ONE_PREEMPTION_THREE_SUBGROUP) 
 */
#define ALL_PREEMPTION						0X00000300
#define THREE_PREEMPTION_ONE_SUBGROUP		0X00000400
#define TWO_PREEMPTION_TWO_SUBGROUP			0X00000500
#define ONE_PREEMPTION_THREE_SUBGROUP		0X00000600
#define ALL_SUBGROUP						0X00000700

/**
 * @brief   Function provides priority grouping control for the exception model
 * @param   priority_grouping Variable of u32 , Priority Type (ALL_PREEMPTION , THREE_PREEMPTION_ONE_SUBGROUP)
 * @return  OK | NOT_OK
 */
u8 DNVIC_SetPriorityGrouping(u32 priority_grouping);

/**
 * @brief   Function to Set Interrupt Priority 
 * @param   IRQn        Variable of u8 , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @param   priority    Variable of u8 , Priority (0..16)
 * @return  OK | NOT_OK
 */
u8 DNVIC_SetPriority (u8 IRQn, u8 priority);

/**
 * @brief   Function to Read peripheral Priority 
 * @param   IRQn        Variable of u8 , Interrupt Request Number is number assigned to peripheral as it is offest of them in vector table array ex (WWDG , TIM2)
 * @param   priority    Pointer to u8 , Priority which to be read
 * @return  OK | NOT_OK
 */
u8 DNVIC_GetPriority (u8 IRQn, u8 *priority);

/**
 * @brief   Function to Disable All peripherals interrupt
 * @param   NA
 * @return  NA
 */
void DNVIC_voidDisableAllPeripherals(void);

/**
 * @brief   Function to Enable All peripherals Interrupt
 * @param   NA
 * @return  NA
 */
void DNVIC_voidEnableAllPeripherals(void);



 /* must develop after reading ch7 and ending the task needed */
 /*** read m3 guide and programming manual then write */ 

/**
 * @brief   Function to Disable all faults Interrupts
 * @param   NA
 * @return  NA
 */
 void DNVIC_voidDisableAllFaults(void);

/**
 * @brief   Function to Enable all faults Interrupts
 * @param   NA
 * @return  NA
 */

void DNVIC_voidEnableAllFaults(void);

/**
 * @brief   Function to disable interrupts only with priority lower than certain level 
 * @param   priority Variable of u8 , Priority (0..16)
 * @return  NA
 */
void DNVIC_voidSetBASEPRI(u8 priority);
/**
 * @brief   Function to change vector Table offest  
 * @param   offset Variable of u32 , Change vector Table offest
 * @return  NA
 */
void DNVIC_voidChangeVectorOffset (u32 offset);
/**
 * @brief   Function to make Software reset 
 * @param   NA 
 * @return  NA
 */
void DNVIC_voidSysReset(void);


#endif /* DNVIC_H_ */
