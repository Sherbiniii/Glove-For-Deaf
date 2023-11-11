#define F_CPU 16000000
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"
#include "DIO_interface.h"
#include "state.h"

u16* ADC_pu16ResultValue = 0;
void(*ADC_PV_NotificationFunc)(void)=0;

void ADC_voidInit(void)
{
	//REF AVCC
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
	
	#if ADC_RESOLUTION == EIGHT_BIT
	//LEFT ADJUSTMENT
	SET_BIT(ADMUX,ADLAR);
	#elif ADC_RESOLUTION == TEN_BIT
	//RIGHT ADJUSTMENT
	CLR_BIT(ADMUX,ADLAR);
	#else
	#error "error in ADC_ADJUSTMENT configuration file"
	#endif
	
	//128 PRESCALER
	ADCSRA &=0b11111000;
	ADCSRA |=ADC_PRESCALAR;
	
	//ADC ENABLE
	SET_BIT(ADCSRA,ADEN);
}
u8 ADC_u8StartConversionSynch(u8 copy_u8ChannelID, u16* copy_pu16ResultValue)
{
	u8 Local_u8WaitingCounter;
	u8 Local_u8ErrorState = OK;
	if(copy_pu16ResultValue != 0)
	{
	
		//CHANNEL SELECT
		ADMUX &=0b11100000;
		ADMUX |=copy_u8ChannelID;
		
		//start conv
		SET_BIT(ADCSRA,ADSC);
		
		//busy waiting till finishing conv
		while(GET_BIT(ADCSRA,ADIF)==0 && (Local_u8WaitingCounter++)!= ADC_TIMEOUT);
		
		if(Local_u8WaitingCounter == ADC_TIMEOUT)
		{
			Local_u8ErrorState=TIMEERROR;
		}
		else
		{
			//CLR FLAG
			SET_BIT(ADCSRA,ADIF);
			#if ADC_RESOLUTION == EIGHT_BIT
			*copy_pu16ResultValue=ADCH;
			#elif ADC_RESOLUTION == TEN_BIT
			*copy_pu16ResultValue=ADC_DATA;
			#else
			#error "error in ADC_RESOLUTION configuration file"
			#endif
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
	
}

u8 ADC_u8StartConversionAsynch(u8 copy_u8ChannelID, u16* copy_pu16ResultValue,void(*copy_PV_NotificationFunc)(void))
{
	u8 Local_ErrorState=OK;
	if(copy_pu16ResultValue != 0 && copy_PV_NotificationFunc!=0)
	{
		ADC_pu16ResultValue=copy_pu16ResultValue;
		ADC_PV_NotificationFunc=copy_PV_NotificationFunc;
		
		//CHANNEL SELECT
		ADMUX &=0b11100000;
		ADMUX |=copy_u8ChannelID;

		//start conv
		SET_BIT(ADCSRA,6);
		
		//Intrupt Enable
		SET_BIT(ADCSRA,3);
	}
	else
	{
		Local_ErrorState=NULL_POINTER;
	}
	return Local_ErrorState;
}
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{		
	#if ADC_RESOLUTION == EIGHT_BIT
	*ADC_pu16ResultValue=ADCH;
	#elif ADC_RESOLUTION == TEN_BIT
	*ADC_pu16ResultValue=ADC_DATA;
	#else
	#error "error in ADC_RESOLUTION configuration file"
	#endif
	
	//ADC interupt dis
	CLR_BIT(ADCSRA,3);

	if(ADC_PV_NotificationFunc!=0)
	{
		ADC_PV_NotificationFunc();
	}
	else
	{
		//do nothing
	}
}