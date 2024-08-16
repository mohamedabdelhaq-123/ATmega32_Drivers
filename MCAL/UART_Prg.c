/*
 * UART_Prg.c
 *
 * Created: 4/17/2024 7:16:55 PM
 *  Author: DELL
 */ 

#include "StdTypes.h"
#include "MemMap.h"
#include "UART_Int.h"

static void (*UART_RX_Fptr)(void) = NULLPTR;
static void (*UART_TX_Fptr)(void) = NULLPTR;

void UART_Init(void)
{
	/*baud rate*/
	UBRRL=51; //baud = 9600
	// frame by default 8 data 1 start 1 stop in reg ucsrb
	clear_bit(UCSRA,U2X);
	/*enable*/
	set_bit(UCSRB,TXEN);
	set_bit(UCSRB,RXEN);
}

void UART_Send(u8 data)  // blocking func
{
	while(!get_bit(UCSRA,UDRE)); // busy weight  if udre=1 so buffer is empty to be refilled
	UDR=data;
	
}


u8 UART_Receive(void)  // Read buffer
{
	while(!get_bit(UCSRA,RXC));
	return UDR;
}

u8 UART_ReceivePerodic(u8*pdata)
{
	if (get_bit(UCSRA,RXC))
	{
		*pdata=UDR;
		return 1;
	}
	return 0;
}


void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}




void UART_RX_InterruptEnable(void)
{
	set_bit(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	clear_bit(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	set_bit(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	clear_bit(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}


ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}