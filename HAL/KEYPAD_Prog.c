
#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "KEYPAD_Int.h"
#include "KEYPAD_Cfg.h"

#define F_CPU  8000000
#include <util/delay.h>


u8 KeysArray[ROW][COL]={ {'7' , '8' , '9' , '/'},   // must be in cfg.c
						 {'4' , '5' , '6' , '*'},
						 {'1' , '2' , '3' , '-'},
						 {'c' , '0' , '=' , '+'}
						 };


void KEYPAD_Init(void)  /* input is pull up mode */
{
	u8 i;
	for(i=0;i<ROW;i++)
	{
		DIO_WritePin(First_Input+i,HIGH);
	}
}


u8 KEYPAD_GetKey(void)
{
	u8 r,c,key=NO_KEY;
	for (r=0;r<ROW;r++)
	{
		DIO_WritePin(First_Output+r,LOW);
		for (c=0;c<COL;c++)
		{
			if (DIO_ReadPin(First_Input+c)==LOW)
			{
				key=KeysArray[r][c];
				_delay_ms(10);
				while(DIO_ReadPin(First_Input+c)==LOW);
				_delay_ms(10);
			}
		}
		DIO_WritePin(First_Output+r,HIGH);
	}
	return key;
}