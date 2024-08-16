/*
* SERVO_Prog.c
*
* Created: 3/25/2024 4:43:53 PM
*  Author: DELL
*/
#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "SERVO_Int.h"
#include "SERVO_Cfg.h"
#include "Timers_Int.h"



void Servo_Position(u8 degree)
{
	OCR1B= Mini_ON_Pulse +((degree*Resolution)/180);
}

void Servo_Position2(u8 degree,Servo_type servo)
{
	switch(servo){
		case Servo_Enter:
		switch(degree){
			case 0:
			DIO_WritePin(Servo_Enter_Pin,HIGH);
			_delay_us(1410);
			DIO_WritePin(Servo_Enter_Pin,LOW);
			break;
			case 90:
			DIO_WritePin(Servo_Enter_Pin,HIGH);
			_delay_us(1500);
			DIO_WritePin(Servo_Enter_Pin,LOW);
			break;
			case 180:
						DIO_WritePin(Servo_Enter_Pin,HIGH);
						_delay_us(2000);
						DIO_WritePin(Servo_Enter_Pin,LOW);
			// code
			break;
		}
		break;
		case Servo_Exit:
		switch(degree){
			case 0:
			DIO_WritePin(Servo_Exit_Pin,HIGH);
			_delay_us(1410);
			DIO_WritePin(Servo_Exit_Pin,LOW);
			break;
			case 90:
			DIO_WritePin(Servo_Exit_Pin,HIGH);
			_delay_us(2000);
			DIO_WritePin(Servo_Exit_Pin,LOW);
			break;
			case 180:
			// code
			break;
		}
		break;
	}
}