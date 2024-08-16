
#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "SEVEN_SEG_Cfg.h"
#include "SEVEN_SEG_Int.h"



void segment_display1(char n)  //basic
{
	if(n<10)
	{
		const char arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
		segmentport1=arr[n]<<1; //common cathode pin0 to pin6
		//segmentport=arr[n]<<1; //common cathode pin1 to pin7
		//segmentport=~arr[n];  //common anode
		
	}
}

void segment_display2(char n)   // unreusable
{
	if(n<100)
	{
		const char arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; // 0,1,2,....,9
		enableport=0b10000000;
		segmentport1=arr[n/10]<<1; //tenths
		_delay_ms(25);
		enableport=0b01000000;
		segmentport2=arr[n%10]<<1; // units
		_delay_ms(5);
	}
}

/***************************************************************/

void segment_display_MLX(char n)   //best  but is used without using decoder
{
	if(n<100)
	{
		const char arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; // 0,1,2,....,9
		set_bit(enableport,7);
		clear_bit(enableport,6);
		segmentport1=arr[n/10]<<1; //tenths
		_delay_ms(5);

		set_bit(enableport,6);
		clear_bit(enableport,7);
		segmentport2=arr[n%10]<<1; // units
		_delay_ms(5);
	}
}


void segment_display_BCD(char n)  // diff ports
{
	if(n<100)
	{
		segmentport1=n/10;
		_delay_ms(5);
		segmentport2=n%10;
		_delay_ms(5);
	}
}

void segment_display_BCD2(char n)  // same port
{
	if(n<100)
	{
		char units=n%10,tenths=n/10;
		segmentport1=(units<<4)|tenths;
		_delay_ms(10);
	}
}

void segment_display_BCD_HEX(char n)  // same port
{
	if(n<100)
	{
		char units=n%16,tenths=n/16;
		segmentport1=(units<<4)|tenths;
		_delay_ms(10);
	}
}