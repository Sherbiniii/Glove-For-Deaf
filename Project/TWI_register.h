/***********************************************************************/
/***********************************************************************/
/********************  Author: Eman Assem      *************************/
/********************  SWC: TWI             *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE: 30/9/2023          *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_

// TWI Bit Rate Register
#define TWBR         (*(volatile u8*)0x20)

// TWI Control Register
#define TWCR         (*(volatile u8*)0x56)

// TWI Status Register
#define TWSR         (*(volatile u8*)0x21)

// TWI Data Register
#define TWDR         (*(volatile u8*)0x23)

// TWI (Slave) Address Register
#define TWAR         (*(volatile u8*)0x22)




#endif