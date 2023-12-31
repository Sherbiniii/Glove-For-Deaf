/***********************************************************************/
/***********************************************************************/
/********************  Author: Eman Assem      *************************/
/********************  SWC: LCD                *************************/
/********************  LAYER: HAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE: 11/8/2023          *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_
#include "STD_TYPES.h"

void LCD_voidInit(void);
void LCD_voidSendCommand(u8 copy_u8Command);
void LCD_voidSendData(u8 copy_u8Data);
u8 LCD_u8SendString(const u8 *copy_pu8String);
u8 LCD_u8SetPos(u8 copy_u8PosX,u8 copy_u8PosY);

#endif
