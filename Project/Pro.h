#ifndef _PRO__H_
#define _PRO__H_

// struct including the partition to which the finger is closed and whether it is inclined or not
typedef struct Finger
{
	u8 Partition;
	u8 inclined;
}F;

void Flex_App(void);
void LCD_Printing(void);
void ADC_Operations(void);
void EEPROM_SaveStates(void);
#endif
