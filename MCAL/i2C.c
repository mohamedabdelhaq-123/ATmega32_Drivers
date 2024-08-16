/*
 * i2C.c
 *
 * Created: 4/27/2024 7:56:12 PM
 *  Author: Ahmed Saad
 */ 
#include "MemMap.h"
#include "StdTypes.h"
#include "i2C.h"
#include "LCD_Int.h"
/*
void i2c_init_master(void)
{
	TWBR=0x02;
	
	CLEAR_BIT(TWSR,TWPS0);
	
	CLEAR_BIT(TWSR,TWPS1);   //bit rate= 400K   prescaller = 1 
	
	SET_BIT(TWCR,TWEN);      // Enable I2c
}

void i2c_init_slave(Slave_G general)
{
	if (general==enable_G)
	{
		TWAR=(Slave_address<<1|1);
	}
	else if (general==not_enable_G)
	{
		TWAR=(Slave_address<<1);
	}
	
	SET_BIT(TWCR,TWEN);                   // Enable I2c
}

void i2c_start(void)
{
	
	  // Clear the TWINT flag before sending the start bit TWINT=1 (not cleared automatically)
	  // send the start bit by TWSTA=1
	  // Enable TWI Module TWEN=1 
	 
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	while(!READ_BIT(TWCR,TWINT));
	
	if ((TWSR & 0xF8) != MASTER_START_COMMAND)
	{
		//error
	}
	
}

void i2c_stop(void)
{
	 
	  // Clear the TWINT flag before sending the stop bit TWINT=1
	  // send the stop bit by TWSTO=1
	  // Enable TWI Module TWEN=1 
	 
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_rep_start(void)
{
	SET_BIT(TWCR,TWINT);                 // Clear Interrupt Flag
	
	SET_BIT(TWCR,TWSTA);                 // send Start
	
	while(!READ_BIT(TWCR,TWINT));
	
	if ((TWSR & 0xF8) != MASTER_REPEATED_START_COMMAND)
	{
		//error
	}
	
}

void TWI_writeByte(u8 data)
{
    // Put data On TWI data Register 
    TWDR = data;
    
    // Wait for TWINT flag set in TWCR Register(data is send successfully) 
	while(!READ_BIT(TWCR,TWINT));
	
	LCD_Cursor(2,4);
	LCD_WriteNum(TWSR & 0xF8);
	
    //while(BIT_IS_CLEAR(TWCR,TWINT));
}

void i2c_send_slave_address_w(u8 S_address)
{
	S_address=(S_address<<1) & 0XFE;
	
	TWDR=S_address;
	
	// Clear the TWINT flag before sending the data TWINT=1
	// Enable TWI Module TWEN=1 
	  
    TWCR = (1 << TWINT) | (1 << TWEN);
	
	while(!READ_BIT(TWCR,TWINT));
	
	LCD_Cursor(1,8);
	LCD_WriteNum((TWSR & 0xF8));
	
	if ((TWSR & 0xF8) != MASTER_ADDRESS_SENT_WRITE_ACK_RECEIVED_COMMAND )
	{
		//error
	}
	
}

void i2c_send_slave_address_R(u8 S_address)
{
	S_address=(S_address<<1) | 1;
	
	TWDR=S_address;
	
	// Clear the TWINT flag before sending the data TWINT=1
	// Enable TWI Module TWEN=1
	 
    TWCR = (1 << TWINT) | (1 << TWEN);
	
	while(!READ_BIT(TWCR,TWINT));
	
	if ((TWSR & 0xF8) != MASTER_ADDRESS_SENT_READ_ACK_RECEIVED_COMMAND )
	{
		//error
	}
}

void i2c_send_data(u8 byte)
{
	TWDR=byte;
	
	// Clear the TWINT flag before sending the data TWINT=1
	// Enable TWI Module TWEN=1
	
	TWCR = (1 << TWINT) | (1 << TWEN);
	u8 c=0;
	while(!READ_BIT(TWCR,TWINT))
	{
// 		LCD_Cursor(2,7);
// 		LCD_WriteNum(c);
// 		c++;
	}
	
// 	LCD_Cursor(2,7);
// 	LCD_WriteNum(TWSR & 0xF8);
	
	if ((TWSR & 0xF8) != MASTER_DATA_TRANS_WRITE_ACK_RECEIVED_COMMAND )
	{
		//error
	}
}

u8 i2c_read_data_A(void)
{
	 
	   Clear the TWINT flag before reading the data TWINT=1
	   Enable sending ACK after reading or receiving data TWEA=1
	   Enable TWI Module TWEN=1 
	 	
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	
    // Wait for TWINT flag set in TWCR Register (data received successfully) 
	
	while(!READ_BIT(TWCR,TWINT));
	
	if ((TWSR & 0xF8) == MASTER_DATA_RECEIVED_READ_ACK_RETURNED_COMMAND )   //with return ack
	{
		return TWDR; 
	}
}

u8 i2c_read_data_NA(void)
{
	/* 
	   Clear the TWINT flag before reading the data TWINT=1
	   Enable TWI Module TWEN=1 
	 
    TWCR = (1 << TWINT) | (1 << TWEN);
	
    // Wait for TWINT flag set in TWCR Register (data received successfully) 
	
	while(!READ_BIT(TWCR,TWINT));
	
	if ((TWSR & 0xF8) == MASTER_DATA_RECEIVED_READ_NO_ACK_RETURNED_COMMAND )   //with return ack
	{
		return TWDR; 
	}
}


*/
