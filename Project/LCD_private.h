#ifndef _LCD_PRIVATE_H_
#define _LCD_PRIVATE_H_

#define FOUR_BIT_MODE 0
#define EIGHT_BIT_MODE 1

static void EnablePulse(void);
static void Static_LCD_HalfPortSend(u8 copy_u8Val);

#endif