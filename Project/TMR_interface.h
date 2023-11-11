#ifndef _TMR_INTERFACE_H_
#define _TMR_INTERFACE_H_



void TIMER0_voidInit(void);
void TIMER0_voidSetValue (u8 copy_u8TimerValue);
void TIMER1_voidInit(void);
void TIMER1_voidSetCompareValueChannelA(u16 copy_u16CompareVal);
u8 TIMER0_SetCallBack(void(*ptrtofunc)(void));
void TIMER1_voidSetValue (u16 copy_u16TimerValue);
u16 TIMER1_u16GetValue (void);
u16 TIMER1_u16GetICR1AVal(void);
void TIMER1_SetCallBackCap(void(*ptrtofunc)(void));
void TIMER1_TogICUMode(void);
void TMR0_delay(u8 copy_u8Delay);


#endif