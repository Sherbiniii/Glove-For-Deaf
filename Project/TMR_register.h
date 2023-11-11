#ifndef _TMR_REGISTER_H_
#define _TMR_REGISTER_H_

#define TMR_OCR0	(*((volatile u8*)0x5C))
#define TMR_TCCR0	(*((volatile u8*)0x53))
#define TMR_TCNT0	(*((volatile u8*)0x52))
#define TMR_TIMSK	(*((volatile u8*)0x59))
#define TMR_TIFR	(*((volatile u8*)0x58))

#define TMR1_TCCR1A	(*((volatile u8*)0x4F))
#define TMR1_TCCR1B	(*((volatile u8*)0x4E))
#define TMR1_TIMSK  (*((volatile u8*)0x4A))

#define TMR1_OCR1A	(*((volatile u16*)0x4A))
#define TMR1_ICR1	(*((volatile u16*)0x46))
#define TMR1_TCNT1	(*((volatile u16*)0x4C))

#endif