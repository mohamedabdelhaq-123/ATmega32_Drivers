#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "LCD_Cfg.h"

#define  F_CPU  8000000
#include <util/delay.h>



#if LCD_MODE== _8_bit


static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	// DIO_WritePin(RW,LOW);   to write on lcd rw =0 or connect to ground
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X38);  // 8 bit mode & 16 line
	WriteIns(0X0e);  // 0x0e,0x0f cursor
	WriteIns(0X01);  // clear screen
	_delay_ms(1);
	WriteIns(0X06);  // increment cursor or inc ddram
}



#elif LCD_MODE ==_4_bit


static void WriteIns(u8 ins)
{
	
	DIO_WritePin(RS,LOW);
	DIO_WritePin(d7,get_bit(ins,7));
	DIO_WritePin(d6,get_bit(ins,6));
	DIO_WritePin(d5,get_bit(ins,5));
	DIO_WritePin(d4,get_bit(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(d7,get_bit(ins,3));
	DIO_WritePin(d6,get_bit(ins,2));
	DIO_WritePin(d5,get_bit(ins,1));
	DIO_WritePin(d4,get_bit(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(d7,get_bit(data,7));
	DIO_WritePin(d6,get_bit(data,6));
	DIO_WritePin(d5,get_bit(data,5));
	DIO_WritePin(d4,get_bit(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(d7,get_bit(data,3));
	DIO_WritePin(d6,get_bit(data,2));
	DIO_WritePin(d5,get_bit(data,1));
	DIO_WritePin(d4,get_bit(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X02);
	WriteIns(0X28);
	WriteIns(0X0e);//0x0e,0x0f cursor
	WriteIns(0X01);//clear screen
	_delay_ms(1);
	WriteIns(0X06);

}

#endif





void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
	
	
}

void LCD_Clear(void)
{
	WriteIns(0X01);//clear screen
	_delay_ms(1);
}


void LCD_WriteString(c8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}

void LCD_SetCursor(u8 line ,u8 cell)
{
	if(line==1)
	{
		WriteIns(0x80|(cell-1));
	}
	else if(line==2)
	{
		WriteIns(0xC0|(cell-1));
	}
}


void LCD_WriteNumber(s32 num)
{
	u8 str[20],i=0,n;
	s8 j;
	if(num==0)
	{
		LCD_WriteChar('0');
	}
	if(num<0)
	{
		LCD_WriteChar('-');
		num=num*(-1);
	}
	while(num)
	{
		str[i]=num%10;
		num=num/10;
		i++;
	}
	for(j=i-1;j>=0;j--)
	{
		n=str[j]+'0';
		LCD_WriteChar(n);
	}
}


void LCD_WriteBinary(u8 num)
{
	u8 str[8];
	s8 j;
	for(j=0;j<8;j++)
	{
		if((num>>j)&1)
		{
			str[j]='1';
		}
		else
		{
			str[j]='0';
		}
	}
	for(j=7;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
}

void LCD_WriteBinary2(u8 num)
{
	s8 j;
	for(j=7;j>=0;j--)
	{
		LCD_WriteChar(get_bit(num,j)+'0');
	}
}




void LCD_WriteHex3(u8 num)
{
	u8 i,n,arr[8];
	s8 j;
	while(num)
	{
		n=num%16;
		if(n<10)
		{
			n=n+'0';
		}
		else
		{
			n=n-10+'A';
		}
		arr[i++]=n;
		num=num/16;
	}
	for(j=i-1;j>=0;j--)
	{
		LCD_WriteChar(arr[j]);
	}
	LCD_WriteChar('H');
}



void LCD_WriteHex2(u8 num)
{
	u8 HN = num>>4;
	u8 LN = num & 0x0f;
	if(HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN+'A'-10);
	}
	if(LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	else
	{
		LCD_WriteChar(LN+'A'-10);
	}
}


void LCD_WriteHex(u8 num)
{
	u8 HN = num>>4;
	u8 LN = num & 0x0f;
	const char arr[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	LCD_WriteChar(arr[HN]);
	LCD_WriteChar(arr[LN]);
}



void LCD_ShakeWord2(c8*str)
{
	u8 i=1,j=1;
	while(1)
	{
		if(i==16 && j==1)
		{
			i=1;
			j=2;
		}
		if(i==16 && j==2)
		{
			i=1;
			j=1;
		}
		LCD_SetCursor(j,i);
		LCD_WriteString(str);
		i++;
		_delay_ms(100);
		LCD_Clear();
	}
}


void LCD_ShakeWord(c8*str)
{
	u8 i=1,j=1;
	s8 c;
	while(1)
	{
		if(i==16 && j==1)
		{
			i=1;
			j=2;
		}
		if(i==16 && j==2)
		{
			i=1;
			j=1;
		}
		LCD_SetCursor(j,i);
		LCD_WriteChar(str[i]);
		i++;
		_delay_ms(100);
		LCD_Clear();
	}
}




void LCD_WriteNumber_4D(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}


void LCD_CustomChar(u8 location,u8* pattern)
{
	WriteIns(0x40+(location*8));
	for(u8 i=0;i<8;i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x40);
}


u8 customChar[] = {
	0x04,
	0x0A,
	0x04,
	0x0E,
	0x15,
	0x04,
	0x0A,
	0x11
};

void LCD_CustomChar2(void)
{
	for(u8 i=0;i<8;i++)
	{
		WriteIns(0x40+i);
		WriteData(customChar[i]);
	}
}

void LCD_CustomChar3(void)
{
	WriteIns(0x40);
	WriteData(0x04);
	WriteData(0x0A);
	WriteData(0x04);
	WriteData(0x0E);
	WriteData(0x15);
	WriteData(0x04);
	WriteData(0x0A);
	WriteData(0x11);
}

void LCD_CustomChar4(u8 location,u8* pattern)
{
	WriteIns(0x40+(location*8));
	WriteData(0x04);
	WriteData(0x0A);
	WriteData(0x04);
	WriteData(0x0E);
	WriteData(0x15);
	WriteData(0x04);
	WriteData(0x0A);
	WriteData(0x11);
	
}




