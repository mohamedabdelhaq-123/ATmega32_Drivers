/*
* DIO_Prog.c
*
* Created: 12/7/2023 10:41:02 PM
*  Author: DELL
*/

#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Cfg.h"
#include "DIO_Int.h"
#include "DIO_Priv.h"


void DIO_Init(void)
{
	DIO_Pin_t i;
	for(i=PINA0;i<TOTAL_PINS;i++)  // init all pins acc to the array in dio_cfg.c
	{
		DIO_InitPin(i, DIO_PinsStatusArray[i]);
	}
}

static void DIO_InitPin(DIO_Pin_t pin, DIO_PinStatus_t status)
{
	DIO_Port_t port=pin/8;  //  0 to 7 port=0 porta  , 8 to 15 port=1  portb .....
	u8 pin_num=pin%8;  // no of pin
	switch(status)
	{
		case output:
		switch(port)
		{
			case pa:
			set_bit(ddra,pin_num);
			clear_bit(porta,pin_num);
			break;
			case pb:
			set_bit(ddrb,pin_num);
			clear_bit(portb,pin_num);
			break;
			case pc:
			set_bit(ddrc,pin_num);
			clear_bit(portc,pin_num);
			break;
			case pd:
			set_bit(ddrd,pin_num);
			clear_bit(portd,pin_num);
			break;
		}
		break;
		case infree:
		switch(port)
		{
			case pa:
			clear_bit(ddra,pin_num);
			clear_bit(porta,pin_num);
			break;
			case pb:
			clear_bit(ddrb,pin_num);
			clear_bit(portb,pin_num);
			break;
			case pc:
			clear_bit(ddrc,pin_num);
			clear_bit(portc,pin_num);
			break;
			case pd:
			clear_bit(ddrd,pin_num);
			clear_bit(portd,pin_num);
			break;
		}
		break;
		case inpullup:
		switch(port)
		{
			case pa:
			clear_bit(ddra,pin_num);
			set_bit(porta,pin_num);
			break;
			case pb:
			clear_bit(ddrb,pin_num);
			set_bit(portb,pin_num);
			break;
			case pc:
			clear_bit(ddrc,pin_num);
			set_bit(portc,pin_num);
			break;
			case pd:
			clear_bit(ddrd,pin_num);
			set_bit(portd,pin_num);
			break;
		}
		break;
	}
	
}


void DIO_WritePin(DIO_Pin_t pin,DIO_PinVoltage_t volt)
{
	DIO_Port_t port=pin/8;  //  0 to 7 port=0 porta  , 8 to 15 port=1  portb .....
	u8 pin_num=pin%8;  // no of pin
	if (volt==HIGH)
	{
		switch(port)
		{
			case pa:
			set_bit(porta,pin_num);
			break;
			case pb:
			set_bit(portb,pin_num);
			break;
			case pc:
			set_bit(portc,pin_num);
			break;
			case pd:
			set_bit(portd,pin_num);
			break;
		}
	}
	else
	{
		switch(port)
		{
			case pa:
			clear_bit(porta,pin_num);
			break;
			case pb:
			clear_bit(portb,pin_num);
			break;
			case pc:
			clear_bit(portc,pin_num);
			break;
			case pd:
			clear_bit(portd,pin_num);
			break;
		}
	}
}

DIO_PinVoltage_t DIO_ReadPin(DIO_Pin_t pin)
{
	DIO_Port_t port=pin/8;  //  0 to 7 port=0 porta  , 8 to 15 port=1  portb .....
	u8 pin_num=pin%8;  // no of pin
	DIO_PinVoltage_t volt=LOW;
	switch(port)
	{
		case pa:
		volt=get_bit(pina,pin_num);
		break;
		case pb:
		volt=get_bit(pinb,pin_num);
		break;
		case pc:
		volt=get_bit(pinc,pin_num);
		break;
		case pd:
		volt=get_bit(pind,pin_num);
		break;
	}
	return volt;
}


void DIO_WritePort(DIO_Port_t port,u8 data)
{
	switch(port)
	{
		case pa:
		porta=data;
		break;
		case pb:
		portb=data;
		break;
		case pc:
		portc=data;
		break;
		case pd:
		portd=data;
		break;
	}
}

u8 DIO_ReadPort(DIO_Port_t port)
{
	u8 data;
	switch(port)
	{
		case pa:
		data=porta;
		break;
		case pb:
		data=portb;
		break;
		case pc:
		data=portc;
		break;
		case pd:
		data=portd;
		break;
	}
	return data;
}

void DIO_TogglePin(DIO_Pin_t pin)
{
	if(DIO_ReadPin(pin)==LOW)
	{
		DIO_WritePin(pin,HIGH);
	}
	else
	{
		DIO_WritePin(pin,LOW);

	}
}

