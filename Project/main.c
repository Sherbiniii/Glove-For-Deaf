#define F_CPU 16000000 // defining the crystal frequency
//includes
#include "state.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "TMR_interface.h"
#include "EEPROM_interface.h"
#include "LCD_interface.h"
#include "TWI_interface.h"
#include "Pro.h"

int main(void)
{
	DIO_u8SetPortDirection(DIO_PORTB,DIO_PORT_OUTPUT); //setting the LCD PORT as output
	LCD_voidInit(); // initializing LCD 2 lines, 5*7 , disp on
	
	DIO_u8SetPortDirection(DIO_PORTA,DIO_PORT_INPUT); //setting the ADC PORT as input
	DIO_u8SetPortDirection(DIO_PORTD,DIO_PORT_INPUT); // setting the switches port as input
	DIO_u8SetPortValue(DIO_PORTD,DIO_PORT_HIGH); // setting it as pull up resistor mode
	
	GIE_voidEnable(); // enabling GIE to allow interrupts 
	ADC_voidInit();  // initializing ADC
	TWI_initMaster(); // initializing TWI in master mode
	TIMER0_voidInit(); // initializing TIMER in CTC mode

	EEPROM_SaveStates(); // sending the 15 words to EEPROM to store it
	while (1)
	{
		ADC_Operations(); // getting reading from sensors through ADC and comparing it with the stored data to output words on LCD
	}
}


