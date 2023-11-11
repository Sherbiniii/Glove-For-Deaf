#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EEPROM_interface.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "GIE_interface.h"
#include "TWI_interface.h"
#include "TMR_interface.h"
#include "state.h"
#include "Pro.h"
#include "ADC_interface.h"

//#include <util/delay.h>

u16 Global_ADC_u16ResultD=0; //variable to store the ADC result

u8 Global_u8Counter=0; // counter to specify which finger the flex fn is dealing with

// initializing the 5 fingers with 0
F F1 ={0,0};
F F2 ={0,0};
F F3 ={0,0};
F F4 ={0,0};
F F5 ={0,0};

u8 Global_u8RestInclined=0; // variable to store the rest inclination state

void ADC_Operations(void)
{
	Global_u8Counter=0; // setting counter to specify the first finger
	ADC_u8StartConversionAsynch(ADC_CHANNEL_0,&Global_ADC_u16ResultD,Flex_App); // getting the current finger 1 partition, converting using ADC from channel0 and setting flexapp as callback fn
	DIO_u8GetPinValue(DIO_PORTD,DIO_PIN0,&F1.inclined);// getting the current finger 1 inclination
	TMR0_delay(10);//10 ms delay
	//_delay_ms(10);
	Global_u8Counter++; // setting counter to specify the second finger
	ADC_u8StartConversionAsynch(ADC_CHANNEL_1,&Global_ADC_u16ResultD,Flex_App); // getting the current finger 2 partition, converting using ADC from channel1 and setting flexapp as callback fn
	DIO_u8GetPinValue(DIO_PORTD,DIO_PIN1,&F2.inclined);// getting the current finger 2 inclination
	TMR0_delay(10);//10 ms delay
	//_delay_ms(10);

	Global_u8Counter++; // setting counter to specify the third finger
	ADC_u8StartConversionAsynch(ADC_CHANNEL_2,&Global_ADC_u16ResultD,Flex_App); // getting the current finger 3 partition, converting using ADC from channel2 and setting flexapp as callback fn
	DIO_u8GetPinValue(DIO_PORTD,DIO_PIN2,&F3.inclined);// getting the current finger 3 inclination
	TMR0_delay(10);//10 ms delay
	//_delay_ms(10);
	
	Global_u8Counter++; // setting counter to specify the fourth finger
	ADC_u8StartConversionAsynch(ADC_CHANNEL_3,&Global_ADC_u16ResultD,Flex_App);// getting the current finger 4 partition, converting using ADC from channel3 and setting flexapp as callback fn
	DIO_u8GetPinValue(DIO_PORTD,DIO_PIN3,&F4.inclined);// getting the current finger 4 inclination
	TMR0_delay(10);//10 ms delay
	//_delay_ms(10);
	
	Global_u8Counter++; // setting counter to specify the fifth finger
	ADC_u8StartConversionAsynch(ADC_CHANNEL_4,&Global_ADC_u16ResultD,Flex_App);// getting the current finger 5 partition, converting using ADC from channel4 and setting flexapp as callback fn
	DIO_u8GetPinValue(DIO_PORTD,DIO_PIN4,&F5.inclined);// getting the current finger 5 inclination
	TMR0_delay(10);//10 ms delay
	//_delay_ms(10);
	
	DIO_u8GetPinValue(DIO_PORTD,DIO_PIN5,&Global_u8RestInclined); //getting the rest inclination

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	LCD_Printing(); // fn comparing current states with stored states to print on lcd
}
void EEPROM_SaveStates(void)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	u16 Local_u16States[15] = {0b0000000010100010,0b0000000010100000,0b0010000010000000,0b0001101010010110,0b1000001010100010,0b1000001010101000,0b0111100000000000,0b0000000000000000,0b0000000010000000,0b0000000000000101,0b0000001010000010,0b0001101010000010,0b0000001010101010,0b0000001010100101,0b0001101010000010}; //Array of 15 states to send it to EEPROM
	u8 Local_u8LoopCounter=0; 
	u16 Local_u8BaseAddress=0b10000000000;//setting EEPROM base address and start writing from 0 address
	for(Local_u8LoopCounter;Local_u8LoopCounter<15;Local_u8LoopCounter++) // storing states in EEPROM byte by byte
	{
		EEPROM_voidSendData(Local_u8BaseAddress+(Local_u8LoopCounter*2),(u8)Local_u16States[Local_u8LoopCounter]);
		EEPROM_voidSendData(Local_u8BaseAddress+(Local_u8LoopCounter*2)+1,(u8)((Local_u16States[Local_u8LoopCounter])>>8));
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void Flex_App()
{
	f32 Local_ADC_f32ResultA =(f32)Global_ADC_u16ResultD*5/256; // converting digital value to float analog value

	switch((u8)Local_ADC_f32ResultA) //switch case to specify the current partition state of each finger (0 = straight,1 = partially closed,2 = fully closed)
	{
		case 0:
		switch(Global_u8Counter) //switch on counter to specify the finger 
		{
			case 0: F1.Partition=0; break;
			case 1: F2.Partition=0; break;
			case 2:	F3.Partition=0; break;
			case 3: F4.Partition=0; break;
			case 4: F5.Partition=0; break;
		}break;
		case 2:
		case 3:
		case 1:
		switch(Global_u8Counter)
		{
			case 0: F1.Partition=1; break;
			case 1: F2.Partition=1; break;
			case 2:	F3.Partition=1; break;
			case 3: F4.Partition=1; break;
			case 4: F5.Partition=1; break;
		}break;
		
		case 4:
		switch(Global_u8Counter)
		{
			case 0: F1.Partition=2; break;
			case 1: F2.Partition=2; break;
			case 2:	F3.Partition=2; break;
			case 3: F4.Partition=2; break;
			case 4: F5.Partition=2; break;
		}break;
		default:break;
	}
}
void LCD_Printing(void)
{
	u8 Local_u8Mark=15; // variable to check if the current state represents a stored word or not
	u8 Local_u8LoopCounter=0;
	u8 Local_u8DataPart=0;// variable to store the data read from EEPROM
	u16 Local_u16ReadData=0; // variable to store the full state read from EEPROM
	u16 Local_u8BaseAddress=0b10000000000;//Address to read from
	u16 Local_u16CurrentState =0;//variable to store the current state
	Local_u16CurrentState |= (((u16)Global_u8RestInclined<<15) | ((u16)F5.inclined<<14) | ((u16)F4.inclined<<13) | ((u16)F3.inclined<<12) | ((u16)F2.inclined<<11) | ((u16)F1.inclined<<10) | ((u16)F5.Partition<<8) | ((u16)F4.Partition<<6) | ((u16)F3.Partition<<4) | ((u16)F2.Partition<<2) | ((u16)F1.Partition)); // getting the cuurent state from the fingers and rest variables
	
	for(Local_u8LoopCounter;Local_u8LoopCounter<15;Local_u8LoopCounter++) // loop to read stored states from EEPROM
	{
		Local_u16ReadData=0;
		EEPROM_voidReadData(Local_u8BaseAddress+((u16)(Local_u8LoopCounter)*2),&Local_u8DataPart);
		Local_u16ReadData |= Local_u8DataPart;
		
		EEPROM_voidReadData(Local_u8BaseAddress+((u16)(Local_u8LoopCounter)*2)+1,&Local_u8DataPart);
		Local_u16ReadData |= (Local_u8DataPart<<8);
		
		if(Local_u16CurrentState== Local_u16ReadData) // getting the current state representation word order in case it represents a stored word
		{
			Local_u8Mark=Local_u8LoopCounter;
			break;
		}
	}
		LCD_voidSendCommand(1); // clearing LCD
		LCD_u8SetPos(0,0); // setting position of LCD cursor to 0,0
		if(Local_u8Mark != 15) // checking that the current state is a stored word
		{	
			switch(Local_u8Mark) // according to the order of the state stored in EEPROM, the corresponding word is printed on LCD
			{
				case 0: LCD_u8SendString("This is terrible"); break;
				case 1:	LCD_u8SendString("I love you"); break;
				case 2: LCD_u8SendString("I really love you"); break;
				case 3:	LCD_u8SendString("I'm watching you"); break;
				case 4: LCD_u8SendString("You"); break;
				case 5:	LCD_u8SendString("Good Job"); break;
				case 6: LCD_u8SendString("Wish you a happy life"); break;
				case 7:	LCD_u8SendString("STOP"); break;
				case 8: LCD_u8SendString("I hate you"); break;
				case 9:	LCD_u8SendString("OK"); break;
				case 10:LCD_u8SendString("Peace"); break;
				case 11:LCD_u8SendString("Good luck"); break;
				case 12:LCD_u8SendString("It hurts"); break;
				case 13:LCD_u8SendString("It hurts a lot"); break;
				case 14:LCD_u8SendString("Sunday"); break;
			}
		}
		else // if current state not equal a stored state in EEPROM, print 'no sign yet' on LCD
		{
				LCD_u8SendString("No Sign yet");
		}
}

