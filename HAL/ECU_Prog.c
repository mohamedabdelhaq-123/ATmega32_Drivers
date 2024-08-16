/*
* ECU_Prog.c
*
* Created: 12/11/2023 12:43:37 PM
*  Author: DELL
*/
#include "StdTypes.h"
#include "DIO_Int.h"
#include "ECU_Int.h"
#include "ECU_Cfg.h"



void LED_Count(u8 i)
{
	u8 x=0,k;
	if(i<=8)
	{
		for(k=0;k<i;k++)
		{
			x|=(1<<k);
			DIO_WritePort(LED_PORT,x);
		}
	}

}