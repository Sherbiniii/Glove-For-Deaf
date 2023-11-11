#include "GIE_register.h"
#include "GIE_config.h"
#include "GIE_private.h"
#include "GIE_interface.h"
#include "BIT_MATH.h"


void GIE_voidEnable(void)
{
	SET_BIT(SREG,SREG_I);
}