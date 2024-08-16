/*
 * MOTOR_Cfg.h
 *
 * Created: 12/11/2023 9:45:22 AM
 *  Author: DELL
 */ 


#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

#define  total_motors 6
#define  MOtOR_PINS   2


#define  M1_IN1  PINC0
#define  M1_IN2  PINC1

#define  M2_IN1  PIND0
#define  M2_IN2  PIND1

#define  M3_IN1  PINC2
#define  M3_IN2  PINC3

#define  M4_IN1  PINC4
#define  M4_IN2  PINC5


DIO_PinVoltage_t arr[total_motors][MOtOR_PINS]={
	{M1,M1_IN1,M1_IN2},
	{M2,M2_IN1,M2_IN2}
	
	
	
	
	
};


#endif /* MOTOR_CFG_H_ */