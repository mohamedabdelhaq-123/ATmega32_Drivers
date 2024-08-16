

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#define  LITTLE 1
#define  BIG    0


u8 BCM_Runnable(void);
typedef union{
	u8 arr[22];
	struct{
		/*u8 LedIdx;
		u8 Red;
		u8 Green;
		u8 Blue;
		u8 Intensity;*/
		u8 str[20];
		u16 Sum;  // last 2 bytes are sum
	};
	
}Frame_t;

typedef enum{
	Ok,
	SUM_ERROR,
	IN_PROGRESS
}BCMerror_t;


/* synch function  blocking*/
void UART_SendString(u8*str);
void UART_ReceiveString(u8*str);
void UART_SendChar(c8 ch);
u8 endian_check(void);
u32 endian_convert(u32 num);
u16 endian_convert_16(u16 num);
void diagCallOut(u8*data);
void UART_SendStringCheckSum(u8*str);
u8 UART_ReceiveStringCheckSum(u8*str);

void UART_SendNumber(u32 num);

void UART_SendStringAsynch(u8*str);
void UART_SendStringAsynch2(u8*str);
void UART_ReceiveStringAsynch(u8*str);

#endif /* UART_SERVICES_H_ */