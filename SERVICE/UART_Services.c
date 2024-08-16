

#include "StdTypes.h"
#include "UART_Int.h"
#include "UART_Services.h"

/* synch function */
void UART_SendString(u8*str) // synch. blocking func 
{
	u8 i;
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	
}

void UART_SendChar(c8 ch) // synch. blocking func
{
	
    UART_Send(ch);
	
	
}

void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=UART_Receive(); // to check if there is # at start or not
	for (;str[i]!=13;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;  // to delete # and put null
}

void UART_SendNumber(u32 num)
{
	u8*p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
	/*
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
	*/
}



void UART_ReceiveNumber(u32*pnum)
{
	u32 num=0;
	u8 b1=UART_Receive(); 
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	u8 b4=UART_Receive();
	num=(u32)b1|(u32)b2<<8|(u32)b3<<16|(u32)b4<<24;
	u8*p=&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
}




u8 endian_check(void)
{
	u32 x=1;
	u8*p=&x;
	if (*p==1)
	{
		return LITTLE;
	}
	else
	{
		return BIG;
	}
}

u32 endian_convert(u32 num)
{
	return  (num<<24)|(num>>24)|((num>>8)&(0x0000ff00))|((num<<8)&(0x00ff0000));
}
u16 endian_convert_16(u16 num)
{
	return  (num<<8)|(num>>8);
}


void diagCallOut(u8*data)
{
	
	
}


void UART_SendStringCheckSum(u8*str)
{
	u8 len=0;
	u16 sum=0;
	for (len=0;str[len];len++); //count no of bytes 'char'
	UART_Send(len);            // send sum
	for (len=0;str[len];len++)
	{
		UART_Send(str[len]);  // send data 
		sum+=str[len];
	}
	UART_Send((u8)sum);   // send sum of data sent to check there
	UART_Send((u8)(sum>>8));  // send data in 2 pieces bec func receives u8
}


u8 UART_ReceiveStringCheckSum(u8*str)
{
	u8 i,len,b0,b1;
	u16 sum_rec=0,sum_calc=0;
	len=UART_Receive();  // receive the length of data coming
	for (i=0;i<len;i++)
	{
		str[i]=UART_Receive();  // receive data 
		sum_calc+=str[i]; //  sum of received data 
	}
	b0=UART_Receive();  // low byte of sum
	b1=UART_Receive();  // high byte of sum
	sum_rec=(u16)b0|(u16)(b1<<8); 
	if (sum_rec==sum_calc) // check if data right or wrong 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



static void TX_Func(void);
static void RX_Func(void);
u8*TX_Str; // glob. ptr
u8*RX_Str;
static flag=1;  // to check if the calls of func. will be neglected or not


void UART_SendStringAsynch(u8*str)
{
	if(flag==1)  // neglect any call for func. if last order hasn't finished
	{
		TX_Str=str; // &str = &Tx_str to use glob. ptr not local str
		UART_SendNoBlock(str[0]); // send first byte of data
		UART_TX_InterruptEnable();  // enable interrupt
		UART_TX_SetCallBack(TX_Func);  // in ISR
		flag=0; // take no new order until flag=1
	}
}

static void TX_Func(void)
{
	static u8 i=1;
	if (TX_Str[i]) // the data ends with null
	{
		UART_SendNoBlock(TX_Str[i]);
		i++;
	}
	else
	{
		i=1;
		flag=1; // allow to take new order
	}
}


void UART_ReceiveStringAsynch(u8*str)
{
	UART_RX_InterruptEnable();  // enable interrupt
	UART_RX_SetCallBack(RX_Func); // in ISR
	RX_Str=str;
}

static void RX_Func(void)
{
	static u8 i;
	RX_Str[i]=UART_ReceiveNoBlock();
	i++;
}




Frame_t frame;
Frame_t Dframe;
static u8 R_Flag;
static void RX_Func2 (void);
static u8 dataFlags[5];
#define Intensity_Flag 4
#define Blue_Flag 3
#define Green_Flag 2
#define Red_Flag 1
#define LedIdx_Flag 0   
   
static void RX_Func3 (void);

void BCM_Init(void)  // Basic Communication Module
{
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RX_Func3);	
}

static void RX_Func3 (void)
{
	static u8 i;
	frame.arr[i]=UART_ReceiveNoBlock();
	i++;
	if(i==22)
	{
		for (u8 j=0;j<20;j++)
		{
			Dframe.arr[j]=frame.arr[j];
		}
		i=0;
		flag=1;
	}
}

static void RX_Func2 (void)
{
	static u8 i;
	frame.arr[i]=UART_ReceiveNoBlock(); 
	i++;
	if(i==7)
	{
		for (u8 j=0;j<7;j++)
		{
			Dframe.arr[j]=frame.arr[j]; 
		}
		i=0;
		flag=1;
	}
}
 
u8 BCM_Runnable(void) // basic comm. mod.  to check the sum & find if there is new frame or not
{
	u16 sumCal=0;
	if (flag==1)
	{
		flag=0;
		for(u8 i=0;i<20;i++)
		{
			sumCal+=Dframe.arr[i]; // sum the data without the sum bytes
			dataFlags[i]=1;  // all flags are set to give new values
		}
		if(Dframe.Sum==sumCal)  // check the sum
		{
			R_Flag=1;  // equal
		}
		else
		{
			R_Flag=0; // not equal
		}
	}
	return R_Flag;
}

/*
BCMerror_t BCM_GetIntensity(u8*pintensity)  // make getter to every component in enum ex: intensity ,Red, LedIdx,....
{ 
	BCMerror_t error=Ok;
	if(dataFlags[Intensity_Flag]==1) // if flag is set so this is new value of intensity
	{
		if (R_Flag==1) // if check sum is equal 
		{
			*pintensity=Dframe.Intensity;
		}
		else if (R_Flag==0) 
		{
			error=SUM_ERROR;
		}
		dataFlags[Intensity_Flag]=0;  // clear the flag bec. it is used now
	}
	else   // the same old value of intensity
	{
		error=IN_PROGRESS;
	}
	return error;
}


BCMerror_t BCM_GetLedIdx(u8*pLedIdx)  // make getter to every component in enum ex: intensity ,Red, LedIdx,....
{
	BCMerror_t error=Ok;
	if(dataFlags[LedIdx_Flag]==1) // if flag is set so this is new value of LedIdx
	{
		if (R_Flag==1) // if check sum is equal
		{
			*pLedIdx=Dframe.LedIdx;
		}
		else if (R_Flag==0)
		{
			error=SUM_ERROR;
		}
		dataFlags[LedIdx_Flag]=0;  // clear the flag bec. it is used now
	}
	else   // the same old value of LedIdx
	{
		error=IN_PROGRESS;
	}
	return error;
}





static u8 TX_Strr[10][10];
void func_tx2(void)  // to arrange orders no neglect them
{
	static u8 j=1;
	static u8 i=0;
	if (TX_Strr[i][j])
	{
		UART_SendNoBlock(TX_Strr[i][j]);
		j++;
	}
	else
	{
		j=1;
		i++;
	}
}

void UART_SendStringAshync2(u8*str)
{
	static u8 i=0;
	UART_TX_SetCallBack(func_tx2);
	
	UART_TX_InterruptEnable();
	
	UART_SendNoBlock(str[0]);
	TX_Str[i]=str;
	i++;
}*/






/*
void func_tx2(void)
{
	flag=1;
}

void UART_SendStringInit(void)
{
	UART_TX_SetCallBack(func_tx2);
	UART_TX_InterruptEnable();
}

void UART_SendStringRunnable(void)
{
	static u8 j=0;
	static u8 i=0;
	if (flag==1)
	{
		if (TX_Str[i][j])
		{
			UART_SendNoBlock(TX_Str[i][j]);
			j++;
		}
		else
		{
			j=0;
			i++;
		}
		flag=0;
	}
	
}

void UART_SendStringSetter(u8*str)
{
	TX_Str[i]=str;
	i++;
}

u8* RXStr;
u8 changeflag;
static void func_Rx(void)
{
	static u8 i=0;
	if (changeflag==1)
	{
		i=0;
		changeflag=0;
	}
	RXStr[i]=UART_ReceiveNoBlock();
	i++;
}
void UART_ReceiveStringAshync(u8*str)
{
	UART_RX_SetCallBack(func_Rx);
	
	UART_RX_InterruptEnable();
	if (str!=RXStr)
	{
		changeflag=1;
	}
	RXStr=str;
}


u8 RX_Buffer1[8];
u8 RX_Buffer2[8];
static u8 Bufferflag=0;
u8 readyflag=0;
static void func_Rx2(void)
{
	static u8 i=0;
	
	if (Bufferflag==0)
	{
		RX_Buffer1[i]=UART_ReceiveNoBlock();
	}
	else
	{
		RX_Buffer2[i]=UART_ReceiveNoBlock();
	}
	i++;
	if (i==8)
	{
		i=0;
		readyflag=1;
		Bufferflag^=1;
	}
	
}

void UART_BufferInit(void)
{
	UART_RX_SetCallBack(func_Rx2);
	
	UART_RX_InterruptEnable();
}

u8 UART_BufferGetter(u8*str)
{
	u8 i;
	if (readyflag==0)
	{
		return 0;
	}
	for (i=0;i<8;i++)
	{
		if (Bufferflag==0)
		{
			str[i]=RX_Buffer2[i];
		}
		else
		{
			str[i]=RX_Buffer1[i];
		}
	}
	readyflag=0;
	return 1;
}


	
*/