/*
 * UART_Int.h
 *
 * Created: 4/17/2024 7:15:53 PM
 *  Author: DELL
 */ 


#ifndef UART_INT_H_
#define UART_INT_H_



void UART_Init(void);


void UART_Send(u8 data);

u8 UART_Receive(void);

u8 UART_ReceivePerodic(u8*pdata);

u8 UART_ReceiveNoBlock(void);
void UART_SendNoBlock(u8 data);


void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));



#endif /* UART_INT_H_ */