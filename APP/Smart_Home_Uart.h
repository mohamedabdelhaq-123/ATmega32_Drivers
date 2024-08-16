/*
* Smart_Home_Uart.h
*
* Created: 4/17/2024 1:57:46 AM
*  Author: DELL
*/


#ifndef SMART_HOME_UART_H_
#define SMART_HOME_UART_H_

typedef struct{
	u8*str;  // pointer to string
	void (*fptr)(u32);  // pointer to func
}tasks_t;

#define NofTasks	10

typedef enum{
	Okk,
	No_Matching
}Compare_t;

typedef enum{
	Right_String,
	Wrong_String
}String_t;


u16 number;

void Smart_Home_on(void);
void Ledon(u32 n);
void ledoff(u32 n);
void Relayon(u32 n);
void Relayoff(u32 n);
void Servo1(u32 n);
void Servo2(u32 n);

/*stage1 without String_Separate */
void string_Compare2(u8*str);


/* stage2 with  String_Separate*/
void string_Compare(u8*str);
String_t String_Separate(c8*string,c8*string2);






#endif /* SMART_HOME_UART_H_ */