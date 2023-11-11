#include "STD_TYPES.h"
#include "state.h"
#include "BIT_MATH.h"
#include "TMR_register.h"
#include "TMR_config.h"
#include "TMR_interface.h"
#include "TMR_private.h"
#include "DIO_interface.h"

static void(*ptrtofunc_ovf)(void)=0;
static void(*ptrtofunc_ctc)(void)=0;
static void(*ptrtofunc_cap)(void)=0;

void TIMER0_voidInit(void)
{
	#if TMR_MODE == TMR_TOV
	TMR_TCNT0 = TMR_PRELOADVALUE;
	CLR_BIT(TMR_TCCR0,TMR_WGM00);
	CLR_BIT(TMR_TCCR0,TMR_WGM01);
	/*TOV interrupt enable*/
	SET_BIT(TMR_TIMSK,TMR_TOIE0);
	
	#elif TMR_MODE == TMR_CTC
	/*CTC mode*/
	CLR_BIT(TMR_TCCR0,TMR_WGM00);
	SET_BIT(TMR_TCCR0,TMR_WGM01);
	/*OC0 mode*/
	TMR_TCCR0 &= 0b11001111;
	TMR_TCCR0 |= TMR_CTC_OUTPUT;
	/*compare match value*/
	TMR_OCR0 =TMR_CMPVALUE;
	/*compare match interrupt enable*/
	//SET_BIT(TMR_TIMSK,TMR_OCIE0);
	
	#elif TMR_MODE == TMR_PWMF
	SET_BIT(TMR_TCCR0,TMR_WGM00);
	SET_BIT(TMR_TCCR0,TMR_WGM01);
	/*MODE*/
	TMR_TCCR0 &= 0b11001111;
	TMR_TCCR0 |= TMR_PWMF_MODE;
	/*compare match value*/
	TMR_OCR0 =TMR_CMPVALUE;
	
	#elif TMR_MODE == TMR_PWMPC
	SET_BIT(TMR_TCCR0,TMR_WGM00);
	CLR_BIT(TMR_TCCR0,TMR_WGM01);
	/*compare match value*/
	TMR_OCR0 =TMR_CMPVALUE;
	#endif
	
	/*PRESCALER*/
	TMR_TCCR0 &= 0b11111000;
	TMR_TCCR0 |= TMR_PRESCALER;
}

u8 TIMER0_SetCallBack(void(*ptrtofunc)(void))
{
	u8 Local_u8ErrorState = OK;
	if(ptrtofunc != 0)
	{
		#if TMR_MODE == TMR_CTC
		ptrtofunc_ctc = ptrtofunc;
		#elif TMR_MODE == TMR_TOV
		ptrtofunc_ovf = ptrtofunc;
		#else Local_u8ErrorState = NOK
		#endif
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

//void __vector_10 (void) __attribute__((signal)); //CTC
//void __vector_10 (void)
//{
//	ptrtofunc_ctc();
//}
void __vector_11 (void) __attribute__((signal)); //OVF
void __vector_11 (void)
{
	ptrtofunc_ovf();
}

void TIMER1_voidInit(void)
{
	/*Set Normal signal*/
	CLR_BIT(TMR1_TCCR1A,TMR1_COM1A0);
	CLR_BIT(TMR1_TCCR1A,TMR1_COM1A1);
	/*Normal mode*/
	CLR_BIT(TMR1_TCCR1A,TMR1_WGM10);
	CLR_BIT(TMR1_TCCR1A,TMR1_WGM11);
	CLR_BIT(TMR1_TCCR1B,TMR1_WGM12);
	CLR_BIT(TMR1_TCCR1B,TMR1_WGM13);
	
	/*set top val 40000*/
	//TMR1_ICR1=40000;
	
	/*set comp val 2000 init*/
	//TMR1_OCR1A=2000;
	
	//ICU enable int
	SET_BIT(TMR_TIMSK,TMR1_TICIE1);
	
	//ICU mode
	SET_BIT(TMR1_TCCR1B,TMR1_ICES1);
	
	/*prescalar 8*/
	CLR_BIT(TMR1_TCCR1B,TMR1_CS10);
	SET_BIT(TMR1_TCCR1B,TMR1_CS11);
	CLR_BIT(TMR1_TCCR1B,TMR1_CS12);
	
	//TMR1_TCNT1=0;
	
}
void TIMER1_voidSetCompareValueChannelA(u16 copy_u16CompareVal)
{
	TMR1_OCR1A=copy_u16CompareVal;
}

void TIMER1_voidSetValue (u16 copy_u16TimerValue)
{
	TMR1_TCNT1=copy_u16TimerValue;
}
u16 TIMER1_u16GetValue (void)
{
	return TMR1_TCNT1;
}
u16 TIMER1_u16GetICR1AVal(void)
{
	return TMR1_ICR1;
}
void TIMER1_SetCallBackCap(void(*ptrtofunc)(void))
{
	ptrtofunc_cap=ptrtofunc;
}
void __vector_6(void)__attribute__((signal));
void __vector_6(void)
{
	ptrtofunc_cap();
}
void TIMER1_TogICUMode(void)
{
	TOG_BIT(TMR1_TCCR1B,TMR1_ICES1);
}
void TIMER0_voidSetValue (u8 copy_u8TimerValue)
{
	TMR_TCNT0 = copy_u8TimerValue;
}
void TMR0_delay(u8 copy_u8Delay)
{
	u8 Local_u8Counter1=0;
	for(Local_u8Counter1;Local_u8Counter1 <copy_u8Delay;Local_u8Counter1++)
	{
		u8 Local_u8Counter0=0;
		for(Local_u8Counter0;Local_u8Counter0<8;Local_u8Counter0++)
		{
			TIMER0_voidSetValue(0);
			while(GET_BIT(TMR_TIFR,TMR_OCF0) == 0);
			SET_BIT(TMR_TIFR,TMR_OCF0);
		}
	}
}