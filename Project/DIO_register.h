/*
------------Author:Deeho---------------------
------------SWC:DIO--------------------------
------------Layer:MCAL-----------------------
------------Version:1.0----------------------
------------Date:5/8/2023--------------------
*/

#ifndef _DIO_REGISTER_H_
#define _DIO_REGISTER_H_

#define DIO_REG_PORTA (*((volatile u8*)0x3B))
#define DIO_REG_DDRA (*((volatile u8*)0x3A))
#define DIO_REG_PINA (*((volatile u8*)0x39))

#define DIO_REG_PORTB (*((volatile u8*)0x38))
#define DIO_REG_DDRB (*((volatile u8*)0x37))
#define DIO_REG_PINB (*((volatile u8*)0x36))

#define DIO_REG_PORTC (*((volatile u8*)0x35))
#define DIO_REG_DDRC (*((volatile u8*)0x34))
#define DIO_REG_PINC (*((volatile u8*)0x33))

#define DIO_REG_PORTD (*((volatile u8*)0x32))
#define DIO_REG_DDRD (*((volatile u8*)0x31))
#define DIO_REG_PIND (*((volatile u8*)0x30))





#endif
