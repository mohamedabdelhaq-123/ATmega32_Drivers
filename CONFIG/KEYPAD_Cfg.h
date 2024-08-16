/*
 * KEYPAD_Cfg.h
 *
 * Created: 2/21/2024 7:41:19 AM
 *  Author: DELL
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define COL 4
#define ROW 4




/** Integration Constraints :  Driver won't run if output and input pins aren't after each other **/
#define First_Input  PINA0
#define First_Output   PINB4


#endif /* KEYPAD_CFG_H_ */