/*
 * i2C.h
 *
 * Created: 4/27/2024 7:37:20 PM
 *  Author: Ahmed Saad
 */ 


#ifndef I2C_H_
#define I2C_H_

/* Status Register Values */

/* Master Send Commands */
#define MASTER_START_COMMAND												0x08
#define MASTER_REPEATED_START_COMMAND										0x10
#define MASTER_ADDRESS_SENT_WRITE_ACK_RECEIVED_COMMAND						0x18   //master send address and W
#define MASTER_ADDRESS_SENT_WRITE_NO_ACK_RECEIVED_COMMAND					0x20
#define MASTER_DATA_TRANS_WRITE_ACK_RECEIVED_COMMAND						0x28  // master send data with ack
#define MASTER_DATA_TRANS_WRITE_NO_ACK_RECEIVED_COMMAND						0x30  // master send data with no ack
#define ARIBTRIATION_LOST_COMMAND											0x38
/* Master Receive Commands */
#define MASTER_ADDRESS_SENT_READ_ACK_RECEIVED_COMMAND						0x40  //master send address and W
#define MASTER_ADDRESS_SENT_READ_NO_ACK_RECEIVED_COMMAND					0x48
#define MASTER_DATA_RECEIVED_READ_ACK_RETURNED_COMMAND						0x50
#define MASTER_DATA_RECEIVED_READ_NO_ACK_RETURNED_COMMAND					0x58
/* Slave Receive Commands */
/* Write Request From Master */
#define SLAVE_ADDRESS_READ_RECEIVED_ACK_RETURNED_COMMAND					0x60
#define SLAVE_ADDRESS_READ_RECEIVED_NO_ACK_RETURNED_COMMAND				    0x68
#define SLAVE_GENERAL_CALL_RECEIVED_ACK_RETURNED_COMMAND					0x70
#define SLAVE_ARBITRATION_SLAW_LOST_ACK_RETURNED							0x78
/* Byte is Received */
#define SLAVE_PERVIOUSLY_READ_ADDRESSED_ACK_RETURNED						0x80
#define SLAVE_PERVIOUSLY_READ_ADDRESSED_NO_ACK_RETURNED						0x88
#define SLAVE_PERVIOUSLY_ADDRESSED_GENERAL_CALL_ACK_RETURNED				0x90
#define SLAVE_STOP_OR_REPEATED_CODITION_RECEIVED							0xA0
/* Slave Send Commands */
/* Read request From Master */
#define SLAVE_WRITE_ACK_RETURNED_COMMAND									0xA8  
#define SLAVE_ARBITRATION_SLAR_RECEIVED_LOST_ACK_RETURNED					0xB0
/* Data Transmitted */
#define SLAVE_DATA_TRANSMITTED_ACK_RECEIVED									0xB8
#define SLAVE_DATA_TRANSMITTED_NO_ACK_RECEIVED								0xC0
#define SLAVE_LAST_DATA_TRANSMITTED_ACK_RECEIVED							0xC8
#define SLAVE_STOP_OR_REPEATED_CODITION_RECEIVED							0xA0
/* General Commands */
#define NO_RELEVANT_STATE_AVAILABLE											0xF8
#define BUS_ERROR_ILLEGAL_CONDITION											0x00


typedef enum{
	enable_G,
	not_enable_G
}Slave_G;


#define Slave_address                1


void i2c_init_master(void);
void i2c_init_slave(Slave_G general);
void i2c_start(void);
void i2c_stop(void);
void i2c_rep_start(void);
void i2c_send_slave_address_w(u8 S_address);
void i2c_send_slave_address_R(u8 S_address);
void i2c_send_data(u8 byte);
u8 i2c_read_data_A(void);
u8 i2c_read_data_NA(void);
void slave_check_address_W(void);
void TWI_writeByte(u8 data);



#endif /* I2C_H_ */