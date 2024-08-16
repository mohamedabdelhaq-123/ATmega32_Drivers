/*
 * SERVO_Int.h
 *
 * Created: 3/25/2024 4:44:24 PM
 *  Author: DELL
 */ 


#ifndef SERVO_INT_H_
#define SERVO_INT_H_

typedef enum{
	Servo_Enter=0,
	Servo_Exit,
}Servo_type;


void Servo_Position2(u8 degree,Servo_type servo);
void Servo_Position(u8 degree);

#endif /* SERVO_INT_H_ */