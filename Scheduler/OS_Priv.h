/*
 * OS_Priv.h
 *
 * Created: 5/7/2024 4:40:03 PM
 *  Author: DELL
 */ 


#ifndef OS_PRIV_H_
#define OS_PRIV_H_




static OS_Struct_t tasksArray[NO_OF_Tasks];
volatile static u8 Timer0_Interrupt_counter=1;
volatile static u16  Millis_Counter =1;

#endif /* OS_PRIV_H_ */