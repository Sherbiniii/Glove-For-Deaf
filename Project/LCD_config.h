/***********************************************************************/
/***********************************************************************/
/********************  Author: Eman Assem      *************************/
/********************  SWC: LCD                *************************/
/********************  LAYER: HAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE: 11/8/2023          *************************/
/***********************************************************************/
/***********************************************************************/
  
#ifndef _LCD_CONFIG_H_
#define _LCD_CONFIG_H_
/*
  YOU HAVE 2 MODES
  1-FOUR_BIT_MODE
  2-EIGHT_BIT_MODE
 */
#define LCD_MODE FOUR_BIT_MODE

#if LCD_MODE == FOUR_BIT_MODE

#define LCD_D4_PIN   DIO_PIN4
#define LCD_D5_PIN   DIO_PIN5
#define LCD_D6_PIN   DIO_PIN6
#define LCD_D7_PIN   DIO_PIN7

#endif


#define LCD_DATA_PORT    DIO_PORTB  
#define LCD_CTRL_PORT    DIO_PORTB
   
#define LCD_RS_PIN       DIO_PIN1
#define LCD_RW_PIN       DIO_PIN2
#define LCD_E_PIN        DIO_PIN3

//0 ONE LINE 
//1 2 LINE
//#define LCD_#_LINE       0 
//#define MASK      8|LCD_#_LINE|BLINK|CURSER 



#endif
