#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_
#include "STD_TYPES.h"

#define ADC_CHANNEL_0 0
#define ADC_CHANNEL_1 1
#define ADC_CHANNEL_2 2
#define ADC_CHANNEL_3 3
#define ADC_CHANNEL_4 4
#define ADC_CHANNEL_5 5
#define ADC_CHANNEL_6 6
#define ADC_CHANNEL_7 7


void ADC_voidInit(void);
u8 ADC_u8StartConversionSynch(u8 copy_u8ChannelID, u16* copy_pu16ResultValue);
u8 ADC_u8StartConversionAsynch(u8 copy_u8ChannelID, u16* copy_pu16ResultValue,void(*copy_PV_NotificationFunc)(void));


#endif