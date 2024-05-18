#include "BitMath.h"
#include "std_typo.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"

void DIO_voidSetPinDirection(u8 port, u8 pin, u8 Direction){
	switch(port){
	case 0:
		if(pin >= 0 && pin < 8){
			CLR_BIT(GPIOA_CRL, (pin * 4));
			CLR_BIT(GPIOA_CRL, ((pin * 4) - 1));
			CLR_BIT(GPIOA_CRL, ((pin * 4) - 2));
			CLR_BIT(GPIOA_CRL, ((pin * 4) - 3));
			GPIOA_CRL |= (Direction << (4 * pin));
		}
		else{
			CLR_BIT(GPIOA_CRH, (pin * 4));
			CLR_BIT(GPIOA_CRH, ((pin * 4) - 1));
			CLR_BIT(GPIOA_CRH, ((pin * 4) - 2));
			CLR_BIT(GPIOA_CRH, ((pin * 4) - 3));
			GPIOA_CRH|= (Direction << (4 * (pin - 8)));
		}
		break;

	case 1:
		if(pin >= 0 && pin < 8){
			CLR_BIT(GPIOB_CRL, (pin * 4));
			CLR_BIT(GPIOB_CRL, ((pin * 4) - 1));
			CLR_BIT(GPIOB_CRL, ((pin * 4) - 2));
			CLR_BIT(GPIOB_CRL, ((pin * 4) - 3));
			GPIOB_CRL |= (Direction << (4 * pin));
		}
		else{
			CLR_BIT(GPIOB_CRH, (pin * 4));
			CLR_BIT(GPIOB_CRH, ((pin * 4) - 1));
			CLR_BIT(GPIOB_CRH, ((pin * 4) - 2));
			CLR_BIT(GPIOB_CRH, ((pin * 4) - 3));
			GPIOB_CRH |= (Direction << (4 * (pin - 8)));
		}
		break;

	case 2:
		if(pin >= 0 && pin < 8){
			CLR_BIT(GPIOC_CRL, (pin * 4));
			CLR_BIT(GPIOC_CRL, ((pin * 4) - 1));
			CLR_BIT(GPIOC_CRL, ((pin * 4) - 2));
			CLR_BIT(GPIOC_CRL, ((pin * 4) - 3));
			GPIOC_CRL |= (Direction << (4 * pin));
		}
		else{
			CLR_BIT(GPIOC_CRH, (pin * 4));
			CLR_BIT(GPIOC_CRH, ((pin * 4) - 1));
			CLR_BIT(GPIOC_CRH, ((pin * 4) - 2));
			CLR_BIT(GPIOC_CRH, ((pin * 4) - 3));
			GPIOC_CRH |= (Direction << (4 * (pin - 8)));
		}
		break;
	}
}

void DIO_voidSetPinValue(u8 port, u8 pin, u8 Value){
	switch(port){
	case 0:
		switch(Value){
		case GPIO_HIGH:
			SET_BIT(GPIOA_ODR, pin);
			break;
		case GPIO_LOW:
			CLR_BIT(GPIOA_ODR, pin);
			break;
		}
		break;
	case 1:
		switch(Value){
		case GPIO_HIGH:
			SET_BIT(GPIOB_ODR, pin);
			break;
		case GPIO_LOW:
			CLR_BIT(GPIOB_ODR, pin);
			break;
		}
		break;
	case 2:
		switch(Value){
		case GPIO_HIGH:
			SET_BIT(GPIOC_ODR, pin);
			break;
		case GPIO_LOW:
			CLR_BIT(GPIOC_ODR, pin);
			break;
		}
		break;
	}
}

u8 DIO_u8GetPinValue(u8 port, u8 pin){
	u8 value = 0;
	switch(port){
	case 0:
		value = GET_BIT(GPIOA_IDR, pin);
		break;
	case 1:
		value = GET_BIT(GPIOB_IDR, pin);
		break;
	case 2:
		value = GET_BIT(GPIOA_IDR, pin);
		break;
	}
	return value;
}

void DIO_voidSetPortDirection(u8 port, u8 Direction){
	uint8 pins[16] = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7, PIN8, PIN9, PIN10, PIN11, PIN12, PIN13, PIN14, PIN15};
	for(uint8 i = 0; i < 16; i++){
		DIO_voidSetPinDirection(port, pins[i], Direction);
	}
}

void DIO_voidSetPortValue(u8 port, u8 Value){
	uint8 pins[16] = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7, PIN8, PIN9, PIN10, PIN11, PIN12, PIN13, PIN14, PIN15};
	for(uint8 i = 0; i < 16; i++){
		DIO_voidSetPinValue(port, pins[i], Value);
	}
}

void DIO_voidTogglePinValue(u8 port, u8 pin){
	u8 value = DIO_u8GetPinValue(port, pin);
	switch(value){
	case GPIO_HIGH:
		CLR_BIT(GPIOC_ODR, pin);
		break;
	case GPIO_LOW:
		SET_BIT(GPIOC_ODR, pin);
		break;
	}
}

void DIO_voidTogglePortValue(u8 port){
	uint8 pins[16] = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7, PIN8, PIN9, PIN10, PIN11, PIN12, PIN13, PIN14, PIN15};
		for(uint8 i = 0; i < 16; i++){
			DIO_voidTogglePinValue(port, pins[i]);
		}
}
