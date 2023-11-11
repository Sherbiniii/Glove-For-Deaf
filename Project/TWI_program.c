#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "state.h"
#include "TWI_config.h"
#include "TWI_private.h"
#include "TWI_register.h"
#include "TWI_interface.h"



#include <util/delay.h>



void TWI_initMaster           (void)
{
	/*prescaler=1*/
	CLR_BIT(TWSR,TWI_TWPS0);
	CLR_BIT(TWSR,TWI_TWPS1);
	
	/*400kbps*/
	TWBR=12;
	
	/*enable Ack*/
	//SET_BIT(TWCR,6);
	
	/*enable twi*/
	SET_BIT(TWCR,TWI_TWEN);
	
}
void TWI_initSlave            (u8 slaveAdd)
{
	/*select slave*/
	TWAR=slaveAdd<<1;
	
	/*disable general call*/
	
	/*enable Ack*/
	SET_BIT(TWCR,TWI_TWEA);
	
	/*enable twi*/
	SET_BIT(TWCR,TWI_TWEN);
	
}

void TWI_sendStartCondition   (void)
{
	/*send start condition*/
	SET_BIT(TWCR,TWI_TWSTA);
	/*clear flag to start current process*/
	SET_BIT(TWCR,TWI_TWINT);
	/*wait flag*/
	while (0== GET_BIT(TWCR,TWI_TWINT));
	/*check ack*/
	while ((TWSR & 0xF8) != 0x08);

}
void TWI_sendRepStartCondition(void)
{
	/*send start condition*/
	SET_BIT(TWCR,TWI_TWSTA);
	/*clear flag to start current process*/
	SET_BIT(TWCR,TWI_TWINT);
	/*wait flag*/
	while (0== GET_BIT(TWCR,TWI_TWINT));
	/*check ack*/
	while ((TWSR & 0xF8) != 0x10);
}
void TWI_sendStopCondition    (void)
{
	/*send stop condition*/
	SET_BIT(TWCR,TWI_TWSTO);
	/*clear flag to start current process*/
	SET_BIT(TWCR,TWI_TWINT);
}
void TWI_sendSlaveAddwithWrite(u8 slaveAdd)
{
	/*select slave*/
	TWDR=slaveAdd<<1;
	
	/*write condition*/
	CLR_BIT(TWDR,TWI_TWD0);
	
	// Clear SC bit
	CLR_BIT(TWCR,TWI_TWSTA );
	
	// Clear flag to start next job
	// SET_BIT(TWCR,7);
	
	/*clear flag to start current process*/
	SET_BIT(TWCR,TWI_TWINT);
	/*wait flag*/
	while (0== GET_BIT(TWCR,TWI_TWINT));
	/*check ack*/
	while ((TWSR & 0xF8) != 0x18);
}
void TWI_sendSlaveAddwithRead (u8 slaveAdd)
{
	/*select slave*/
	TWDR=slaveAdd<<1;
	/*read condition*/
	SET_BIT(TWDR,TWI_TWD0);
	// Clear SC bit
	CLR_BIT(TWCR,TWI_TWSTA);
	
		// Clear flag to start next job
		//SET_BIT(TWCR,7);
	/*clear flag to start current process*/
	SET_BIT(TWCR,TWI_TWINT);
	/*wait flag*/
	while (0== GET_BIT(TWCR,TWI_TWINT));
	/*check ack*/
	while ((TWSR & 0xF8) != 0x40 );
}
void TWI_sendMasterDataByte   (u8 data)
{
	/*send data*/
	TWDR=data;
	/*clear flag to start current process*/
	SET_BIT(TWCR,TWI_TWINT);
	
	/*wait flag*/
	while (0== GET_BIT(TWCR,TWI_TWINT));
	
	/*check ack*/
	while ((TWSR & 0xF8) != 0x28);

}
void TWI_readMasterDataByte   (u8* returnedData)
{
	if(returnedData != 0 )
	{
		/*clear flag to start current process*/
		SET_BIT(TWCR,TWI_TWINT);
		/*wait flag*/
		while (0== GET_BIT(TWCR,TWI_TWINT));
		/*check ack*/
		//while ((TWSR & 0xF8) != 0x50);
		*returnedData=TWDR;
	}
}


