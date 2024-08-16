 /*
 * MOTOR_Prog.c
 *
 * Created: 12/11/2023 9:31:45 AM
 *  Author: DELL
 */
 #include "StdTypes.h"
 #include "DIO_Int.h"
 #include "MOTOR_Int.h"
 #include "MOTOR_Cfg.h"



 void MOTOR_Init(void)
 {
	 // future use
 }



 void MOTOR_Stop(MOTOR_t motor)
 {
	 switch(motor)
	 {
		 case M1:
		 DIO_WritePin(M1_IN1,LOW);
		 DIO_WritePin(M1_IN2,LOW);
		 break;
		 case M2:
		 DIO_WritePin(M2_IN1,LOW);
		 DIO_WritePin(M2_IN2,LOW);
		 break;
	 }
	 
	 
 }

 void MOTOR_CW(MOTOR_t motor)
 {
	 switch(motor)
	 {
		 case M1:
		 DIO_WritePin(M1_IN1,HIGH);
		 DIO_WritePin(M1_IN2,LOW);
		 break;
		 case M2:
		 DIO_WritePin(M2_IN1,HIGH);
		 DIO_WritePin(M2_IN2,LOW);
		 break;
	 }
 }

 void MOTOR_CW2(MOTOR_t motor)
 {
	  switch(motor)
	  {
		  case M1:
	 DIO_WritePin(arr[M1][0],HIGH);
	 DIO_WritePin(arr[M1][1],LOW);
	  }
 }

 void MOTOR_CCW(MOTOR_t motor)
 {
	 switch(motor)
	 {
		 case M1:
		 DIO_WritePin(M1_IN1,LOW);
		 DIO_WritePin(M1_IN2,HIGH);
		 break;
		 case M2:
		 DIO_WritePin(M2_IN1,LOW);
		 DIO_WritePin(M2_IN2,HIGH);
		 break;
	 }
 }