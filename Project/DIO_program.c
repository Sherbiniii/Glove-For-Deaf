#include "BIT_MATH.h"
#include "DIO_register.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"
#include "state.h"
#include "STD_TYPES.h"


u8 DIO_u8SetPinDirection(u8 copy_u8port,u8 copy_u8PinNumber,u8 copy_u8PinDirection)
{
	u8 Local_u8ErrorState=OK;
	
	if(copy_u8PinNumber<= DIO_PIN7)
	{
		if(copy_u8PinDirection == DIO_PIN_OUTPUT)
		{
			switch(copy_u8port)
			{
				case DIO_PORTA: SET_BIT(DIO_REG_DDRA,copy_u8PinNumber); break;
				case DIO_PORTB: SET_BIT(DIO_REG_DDRB,copy_u8PinNumber);break;
				case DIO_PORTC: SET_BIT(DIO_REG_DDRC,copy_u8PinNumber);break;
				case DIO_PORTD: SET_BIT(DIO_REG_DDRD,copy_u8PinNumber);break;
			}
		}
		else if (copy_u8PinDirection == DIO_PIN_INPUT)
		{
			switch(copy_u8port)
			{
				case DIO_PORTA: CLR_BIT(DIO_REG_DDRA,copy_u8PinNumber); break;
				case DIO_PORTB: CLR_BIT(DIO_REG_DDRB,copy_u8PinNumber);break;
				case DIO_PORTC: CLR_BIT(DIO_REG_DDRC,copy_u8PinNumber);break;
				case DIO_PORTD: CLR_BIT(DIO_REG_DDRD,copy_u8PinNumber);break;
				
			}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	
	return Local_u8ErrorState;
}
u8 DIO_u8SetPinValue(u8 copy_u8port,u8 copy_u8PinNumber,u8 copy_u8PinValue)
{
	u8 Local_u8ErrorState=OK;
	if(copy_u8PinNumber<=DIO_PIN7)
	{
		if(copy_u8PinValue == DIO_PIN_HIGH)
		{
			switch(copy_u8port)
			{
				case DIO_PORTA: SET_BIT(DIO_REG_PORTA,copy_u8PinNumber); break;
				case DIO_PORTB: SET_BIT(DIO_REG_PORTB,copy_u8PinNumber);break;
				case DIO_PORTC: SET_BIT(DIO_REG_PORTC,copy_u8PinNumber);break;
				case DIO_PORTD: SET_BIT(DIO_REG_PORTD,copy_u8PinNumber);break;
				
			}
		}
		else if(copy_u8PinValue==DIO_PIN_LOW)
		{
			switch(copy_u8port)
			{
				case DIO_PORTA: CLR_BIT(DIO_REG_PORTA,copy_u8PinNumber); break;
				case DIO_PORTB: CLR_BIT(DIO_REG_PORTB,copy_u8PinNumber);break;
				case DIO_PORTC: CLR_BIT(DIO_REG_PORTC,copy_u8PinNumber);break;
				case DIO_PORTD: CLR_BIT(DIO_REG_PORTD,copy_u8PinNumber);break;
			}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return  Local_u8ErrorState;
}
u8 DIO_u8SetPortDirection(u8 copy_u8port,u8 copy_u8PortDirection)
{
	u8 Local_u8ErrorState=OK;
	switch(copy_u8port)
	{
		case DIO_PORTA: DIO_REG_DDRA= copy_u8PortDirection;break;
		case DIO_PORTB: DIO_REG_DDRB= copy_u8PortDirection;break;
		case DIO_PORTC: DIO_REG_DDRC= copy_u8PortDirection;break;
		case DIO_PORTD: DIO_REG_DDRD= copy_u8PortDirection;break;
		default: Local_u8ErrorState = NOK; break;
	}
	
	return Local_u8ErrorState;
}
u8 DIO_u8SetPortValue(u8 copy_u8port,u8 copy_u8PortValue)
{
	u8 Local_u8ErrorState=OK;
	switch(copy_u8port)
	{
		case DIO_PORTA: DIO_REG_PORTA= copy_u8PortValue;break;
		case DIO_PORTB: DIO_REG_PORTB= copy_u8PortValue;break;
		case DIO_PORTC: DIO_REG_PORTC= copy_u8PortValue;break;
		case DIO_PORTD: DIO_REG_PORTD= copy_u8PortValue;break;
		default: Local_u8ErrorState = NOK; break;
	}
	
	return Local_u8ErrorState;
}

u8 DIO_u8GetPinValue(u8 copy_u8port,u8 copy_u8PinNumber,u8* copy_pu8PinValue)
{
	u8 Local_u8ErrorState=OK;
	if(copy_u8PinNumber<=DIO_PIN7)
	{
		switch(copy_u8port)
		{
			case DIO_PORTA: *copy_pu8PinValue= GET_BIT(DIO_REG_PINA,copy_u8PinNumber); break;
			case DIO_PORTB: *copy_pu8PinValue= GET_BIT(DIO_REG_PINB,copy_u8PinNumber); break;
			case DIO_PORTC: *copy_pu8PinValue= GET_BIT(DIO_REG_PINC,copy_u8PinNumber); break;
			case DIO_PORTD: *copy_pu8PinValue= GET_BIT(DIO_REG_PIND,copy_u8PinNumber); break;
			default: Local_u8ErrorState = NOK; break;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	
	return  Local_u8ErrorState;
}