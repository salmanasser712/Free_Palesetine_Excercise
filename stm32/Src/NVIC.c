/**
 * header file STD_TYPES.h
 */
#include "BitMath.h"
#include "std_typo.h"

/**
 * @headerfile DNVIC.h
 */
#include "NVIC.h"
#include "NVIC_PRIV.h"

u8 DNVIC_EnableIRQ(u8 IRQn)
{
	if (IRQn>=0 && IRQn<=31 ){
		SET_BIT(NV->ISER[0],IRQn);
	}
	else if (IRQn>=32 && IRQn<=63 ){
		SET_BIT(NV->ISER[1],(IRQn-32));
	}
	else if (IRQn>=64 && IRQn<=67 ){
		SET_BIT(NV->ISER[2],(IRQn-64));
	}
	else{
		return ES_NOK;
	}
	return ES_OK;
}


u8 DNVIC_DisableIRQ(u8 IRQn)
{
	if (IRQn>=0 && IRQn<=31 ){
		SET_BIT(NV->ICER[0],IRQn);
	}
	else if (IRQn>=32 && IRQn<=63 ){
		SET_BIT(NV->ICER[1],(IRQn-32));
	}
	else if (IRQn>=64 && IRQn<=67 ){
		SET_BIT(NV->ICER[2],(IRQn-64));
	}
	else{
		return ES_NOK;
	}
	return ES_OK;
}

u8 DNVIC_SetPendingIRQ (u8 IRQn)
{
	if (IRQn>=0 && IRQn<=31 ){
		SET_BIT(NV->ISPR[0],IRQn);
	}
	else if (IRQn>=32 && IRQn<=63 ){
		SET_BIT(NV->ISPR[1],(IRQn-32));
	}
	else if (IRQn>=64 && IRQn<=67 ){
		SET_BIT(NV->ISPR[2],(IRQn-64));
	}
	else{
		return ES_NOK;
	}
	return ES_OK;
}

u8 DNVIC_ClearPendingIRQ (u8 IRQn)
{
	if (IRQn>=0 && IRQn<=31 ){
		SET_BIT(NV->ICPR[0],IRQn);
	}
	else if (IRQn>=32 && IRQn<=63 ){
		SET_BIT(NV->ICPR[1],(IRQn-32));
	}
	else if (IRQn>=64 && IRQn<=67 ){
		SET_BIT(NV->ICPR[2],(IRQn-64));
	}
	else{
		return ES_NOK;
	}
	return ES_OK;
}

u8 DNVIC_GetPendingIRQ (u8 IRQn, u8 *Val)
{
	u8 ret=0;
	if (IRQn>=0 && IRQn<=31 ){
		ret= GET_BIT(NV->ISPR[0],IRQn);
	}
	else if (IRQn>=32 && IRQn<=63 ){
		ret= GET_BIT(NV->ISPR[1],(IRQn-32));
	}
	else if (IRQn>=64 && IRQn<=67 ){
		ret= GET_BIT(NV->ISPR[2],(IRQn-64));
	}
	else{
		return ES_NOK;
	}
	return ret;
}

u8 DNVIC_GetActive (u8 IRQn, u8 *Val)
{
	if (IRQn>=0 && IRQn<=31 ){
		*Val = GET_BIT(NV->IABR[0],IRQn);
	}
	else if (IRQn>=32 && IRQn<=63 ){
		*Val = GET_BIT(NV->IABR[1],(IRQn-32));
	}
	else if (IRQn>=64 && IRQn<=67 ){
		*Val = GET_BIT(NV->IABR[2],(IRQn-64));
	}
	else{
		return ES_NOK;
	}
	return ES_OK;
}

u8 DNVIC_SetPriorityGrouping(u32 priority_grouping)
{
	SCB_AIRCR = PASSWORD_MASK;
	switch(priority_grouping)
	{
	case ALL_PREEMPTION :SCB_AIRCR |= priority_grouping; break;
	case THREE_PREEMPTION_ONE_SUBGROUP :SCB_AIRCR |= priority_grouping; break;
	case TWO_PREEMPTION_TWO_SUBGROUP :SCB_AIRCR |= priority_grouping; break;
	case ONE_PREEMPTION_THREE_SUBGROUP :SCB_AIRCR |= priority_grouping; break;
	case ALL_SUBGROUP :SCB_AIRCR |= priority_grouping; break;
	default: return ES_NOK;
	}
	return ES_OK;
}

u8 DNVIC_SetPriority (u8 IRQn, u8 priority)
{
	NV->IPR[IRQn] |= (priority << 4);
	return ES_OK;
}

u8 DNVIC_GetPriority (u8 IRQn, u8 *priority)
{
	*priority = (NV->IPR[IRQn] >> 4);
	return ES_OK;
}
/* must develop after reading ch7 and ending the task needed */
void DNVIC_voidDisableAllPeripherals(void)
{
	NV->ICER[0] = 0xFFFFFFFF;
	NV->ICER[1] = 0xFFFFFFFF;
	NV->ICER[2] = 0xFFFFFFFF;
}

void DNVIC_voidEnableAllPeripherals(void)
{
	NV->ISER[0] = 0xFFFFFFFF;
	NV->ISER[1] = 0xFFFFFFFF;
	NV->ISER[2] = 0xFFFFFFFF;
}

void DNVIC_voidDisableAllFaults(void)
{
	 BASEPRI = 0xFF;
}


void DNVIC_voidEnableAllFaults(void)
{
	 BASEPRI = 0;

}

void DNVIC_voidSetBASEPRI(u8 priority)
{
	BASEPRI = priority;
}
void DNVIC_voidChangeVectorOffset (u32 offset)
{
	SCB_VTOR = offset;
}

void DNVIC_voidSysReset(void)
{
	 SET_BIT(SCB_AIRCR, SYSRESETREQ);
}
