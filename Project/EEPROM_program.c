	
/*
 * EEPROM_program.c
 *
 * Created: 9/17/2022 9:26:43 PM
 *  Author: AMIT
 */ 

#define F_CPU    16000000UL
#include <util/delay.h>

 /* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"


/* MCAL */
#include "TWI_interface.h"
#include "TWI_register.h"
#include "DIO_interface.h"
/* HAL */
#include "EEPROM_interface.h"


void EEPROM_voidSendData(u16 byteAddress,u8 data)
{
	u8 sAddress = (u8)(0x50 | (u8)(byteAddress>>8));
	
	// Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddwithWrite(sAddress);
	
	// Send byte address
	TWI_sendMasterDataByte((u8)byteAddress);
	
	// Send byte data
	TWI_sendMasterDataByte(data);
	
	// Send stop condition
	TWI_sendStopCondition();
	
	_delay_ms(5);
}

void EEPROM_voidReadData (u16 byteAddress,u8* returnedData)
{
	u8 sAddress = (u8)(0x50 | (byteAddress>>8));
	
	//Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddwithWrite(sAddress);
	
	// Send byte address
	TWI_sendMasterDataByte((u8)byteAddress);
	
	// Send repeated 
	TWI_sendRepStartCondition();
	
	// Send slave address with read operation
	TWI_sendSlaveAddwithRead(sAddress);
	
	// Read byte data
	TWI_readMasterDataByte(returnedData);
	
	// Send stop condition
	TWI_sendStopCondition();
	
	_delay_ms(5);
}

void EEPROM_voidRReadData (u16 byteAddress,u8* returnedData)
{
	u8 sAddress = (u8)(0x50 | (byteAddress>>8));

	TWI_sendRepStartCondition();

	// Send slave address with write operation
	TWI_sendSlaveAddwithWrite(sAddress);
	
	// Send byte address
	TWI_sendMasterDataByte((u8)byteAddress);
		
	// Send repeated
	TWI_sendRepStartCondition();
	
	// Send slave address with read operation
	TWI_sendSlaveAddwithRead(sAddress);
	
	// Read byte data
	TWI_readMasterDataByte(returnedData);

	// Send stop condition
	TWI_sendStopCondition();
	_delay_ms(5);
}