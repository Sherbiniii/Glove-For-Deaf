/***********************************************************************/
/***********************************************************************/
/********************  Author: Eman Assem      *************************/
/********************  SWC: LCD                *************************/
/********************  LAYER: HAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE: 11/8/2023          *************************/
/***********************************************************************/
/***********************************************************************/

#define F_CPU 16000000
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "state.h"
#include "LCD_config.h"
#include "DIO_interface.h"
#include "LCD_private.h"
#include "LCD_interface.h"


#if LCD_MODE == FOUR_BIT_MODE
static void Static_LCD_HalfPortSend(u8 copy_u8Val)
{
	u8 Local_u8HoldBit; 
	Local_u8HoldBit= GET_BIT(copy_u8Val,0);
	DIO_u8SetPinValue(LCD_DATA_PORT,LCD_D4_PIN,Local_u8HoldBit);
	Local_u8HoldBit= GET_BIT(copy_u8Val,1);
	DIO_u8SetPinValue(LCD_DATA_PORT,LCD_D5_PIN,Local_u8HoldBit);
	Local_u8HoldBit= GET_BIT(copy_u8Val,2);
	DIO_u8SetPinValue(LCD_DATA_PORT,LCD_D6_PIN,Local_u8HoldBit);
	Local_u8HoldBit= GET_BIT(copy_u8Val,3);
	DIO_u8SetPinValue(LCD_DATA_PORT,LCD_D7_PIN,Local_u8HoldBit);
}
#endif
void LCD_voidSendCommand(u8 copy_u8Command)
{
	/*CTRL PINS*/
	/*RS command=0 data=1*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	/*RW read=1  write=0*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	#if LCD_MODE == EIGHT_BIT_MODE
	/*send data before enable pulse*/
	DIO_u8SetPortValue(LCD_DATA_PORT,copy_u8Command);
	EnablePulse();
	
	#elif LCD_MODE == FOUR_BIT_MODE
	Static_LCD_HalfPortSend(copy_u8Command>>4);
	EnablePulse();
	Static_LCD_HalfPortSend(copy_u8Command);
	EnablePulse();
	
	#endif
	
}
void LCD_voidSendData(u8 copy_u8Data)
{
	/*CTRL PINS*/
	/*RS command=0 data=1*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
	/*RW read=1  write=0*/
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	#if LCD_MODE == EIGHT_BIT_MODE
	/*send data before enable pulse*/
	DIO_u8SetPortValue(LCD_DATA_PORT,copy_u8Data);
	EnablePulse();
	
	#elif LCD_MODE == FOUR_BIT_MODE
	Static_LCD_HalfPortSend(copy_u8Data>>4);
	EnablePulse();
	Static_LCD_HalfPortSend(copy_u8Data);
	EnablePulse();
	
	#endif
}

static void EnablePulse(void)
{
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	/*delay to send*/
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_PIN_LOW);
}
void LCD_voidInit(void)
{
	//1-delay more than 30ms
	_delay_ms(40);
	
	#if LCD_MODE == EIGHT_BIT_MODE
	//2-sendCommand N=1-> 2 lines ,F=0 ->5*7   0b0011NFXX = 0b00111000
	LCD_voidSendCommand(0b00111000);
	
	//LCD_u8SendCommand(0b00001100);
	
	#elif LCD_MODE == FOUR_BIT_MODE
	
	Static_LCD_HalfPortSend(0b0010);
	EnablePulse();

	Static_LCD_HalfPortSend(0b0010);
	EnablePulse();
	
	Static_LCD_HalfPortSend(0b1000);
	EnablePulse();
	

	#endif
	//3-Display ON/OFF D=1   C =0  B=0  0b00001100
	
	LCD_voidSendCommand(0b00001100);

	
	//LCD_u8SendCommand(0x38);
	//LCD_u8SendCommand(0x0F);
	//LCD_u8SendCommand(0x80);

	//4-clr display 1
	LCD_voidSendCommand(1);

}


u8 LCD_u8SendString(const u8 *copy_pu8String)
{
	u8 Local_u8Counter=0;
	u8 Local_u8ErrorState=OK;
	if(copy_pu8String !=0)
	{
		while(copy_pu8String[Local_u8Counter] != '\0')
		{
			LCD_voidSendData(copy_pu8String[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
	else
		Local_u8Counter=NOK;
	
	return Local_u8ErrorState;
}

u8 LCD_u8SetPos(u8 copy_u8PosX,u8 copy_u8PosY)
{
	u8 Local_u8ErrorState=OK;
	u8 Local_u8DDRAM=0;
	switch(copy_u8PosY)
	{
		case 0: Local_u8DDRAM=copy_u8PosX; break;
		case 1: Local_u8DDRAM=copy_u8PosX+0x40; break;
		default: Local_u8ErrorState=NOK; break;
	}
	SET_BIT(Local_u8DDRAM,7);
	LCD_voidSendCommand(Local_u8DDRAM);
	return Local_u8ErrorState;
}

