#ifndef _TMR_PRIVATE_H_
#define _TMR_PRIVATE_H_

#define TMR_OCF0 1
#define TMR_WGM00 6
#define TMR_WGM01 3
#define TMR_OCIE0 1
#define TMR_TOIE0 0

#define TMR_PRESCALER_1		1
#define TMR_PRESCALER_8		2
#define TMR_PRESCALER_64	3
#define TMR_PRESCALER_256	4
#define TMR_PRESCALER_1024	5

#define TMR_TOV		0
#define TMR_PWMPC	1
#define TMR_CTC		2
#define TMR_PWMF	3

#define TMR1_NORM	0

#define TMR_CTC_NORM (0<<4)
#define TMR_CTC_TOG (1<<4)
#define TMR_CTC_CLR (2<<4)
#define TMR_CTC_SET (3<<4)

#define  TMR_PWMF_NORM	(0<<4)
#define  TMR_PWMF_CLROC (2<<4)
#define  TMR_PWMF_SETOC (3<<4)

#define TMR1_WGM13  4
#define TMR1_WGM12  3
#define TMR1_CS12   2
#define TMR1_CS11   1
#define TMR1_CS10   0
#define TMR1_ICES1  6

#define TMR1_TICIE1	5

#define TMR1_COM1A0 6
#define TMR1_COM1A1 7
#define TMR1_COM1B0 4
#define TMR1_COM1B1 5
#define TMR1_WGM11  1
#define TMR1_WGM10  0



#endif