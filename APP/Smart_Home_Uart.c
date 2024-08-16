/*
#include "StdTypes.h"
#include "Smart_Home_Uart.h"
#include "UART_Services.h"
#include "LCD_Int.h"
#include "SERVO_Int.h"

tasks_t tasks[NofTasks]={ {"Servo1",Servo1},
	{"Servo2",Servo2},
{"Relayoff",Relayoff},
{"Relayon",Relayon},
{"ledoff",ledoff},
{"Ledon",Ledon}  };


void Ledon(u32 n)
{
	LCD_SetCursor(1,1);
	LCD_WriteString("TaskDone ledon");
	LCD_SetCursor(2,1);
	LCD_WriteNumber(n);
}

void ledoff(u32 n)
{
	
}

void Relayon(u32 n)
{
	LCD_SetCursor(1,1);
	LCD_WriteString("TaskDoneRelayon");
}

void Relayoff(u32 n)
{
	
}

void Servo1(u32 n)
{
	Servo_Position(n,Servo_Enter);
}

void Servo2(u32 n)
{
	Servo_Position(n,Servo_Exit);
}


void Smart_Home_on(void)
{
	String_t error;
	LCD_WriteString("Smart Home");
	u8 received_string[20]={0}; // to avoid last reslts
	u8 Separated_String[20]={0};
	number=0;
	UART_ReceiveString(received_string);
	error =String_Separate(received_string,Separated_String);
	if(error==Wrong_String)
	{
		UART_SendString("Wrong String");
	}
	else if(error== Right_String)
	{
		string_Compare(Separated_String);
	}
}



String_t String_Separate(c8*string,c8*string2)
{
	u8 i=0,j=0;
	u8 strn[20];
	for(i=0;string[i]!='_';i++)  // letters
	{

		string2[i]=string[i];
	}
	string2[i]='\0'; // end string with null
	i++;
	while(string[i])  // number in strn
	{
		strn[j]=string[i];
		j++;
		i++;
	}
	strn[j]=0;    // end string with null
	for(i=0; strn[i]; i++)  //strn to int
	{
		if(strn[i]>='0'&& strn[i]<='9')
		{
			number=number*10+(strn[i]-'0');
		}
		else
		{
			return Wrong_String;  //if there are sth else than numbers in string form
		}
	}
	return Right_String;
}

void string_Compare(u8*str)
{
	u8 i=0,j=0;
	Compare_t error=No_Matching;
	for(j=0;j<NofTasks && error==No_Matching ;j++)
	{
		error =  Okk;
		for(i=0; str[i] || (tasks[j].str[i]) ; i++)
		{
			if((str[i]-'A'+'a')!=tasks[j].str[i] && (str[i]-'a'+'A')!=tasks[j].str[i] && str[i]!=tasks[j].str[i])  // all must agree that letter is wrong
			{
				error=No_Matching;
			}
		}
	}
	if(error==No_Matching)
	{
		UART_SendString("Wrong Frame");
	}
	else
	{
		j--;
		tasks[j].fptr(number);
		UART_SendString("Right Frame");
	}
}

/***** stage 2 with string_separate *****/

/*

void Smart_Home_on(void)
{
	String_t error;
	u8 received_string[20]={0}; // to avoid last reslts
	u8 Separated_String[20]={0};
	number=0;
	UART_ReceiveString(received_string);
	error =String_Separate(received_string,Separated_String);
	if(error==Wrong_String)
	{
		UART_SendString("Wrong String");
	}
	else if(error== Right_String)
	{
		string_Compare(Separated_String);
	}
}



String_t String_Separate(c8*string,c8*string2)
{
	u8 i=0,j=0;
	u8 strn[20];
	String_t status ;
	for(i=0;string[i]!='_';i++)  // letters
	{

		string2[i]=string[i];
	}
	i++;
	while(string[i])  // number in strn
	{
		strn[j]=string[i];
		j++;
		i++;
	}
	strn[j]=0;
	for(i=0; strn[i]; i++)  //strn to int
	{
		if(strn[i]>='0'&& strn[i]<='9')
		{
			number=number*10+(strn[i]-'0');
		}
		else
		{
			return Wrong_String;  //if there are sth else than numbers in string form
		}
	}
	return Right_String;
}

void string_Compare(u8*str)
{
	u8 i=0,j=0;
	Compare_t error=No_Matching;
	for(j=0;j<NofTasks && error==No_Matching ;j++)
	{
		error =  Okk;
		for(i=0; str[i]||tasks[j].str[i]; i++)
		{
			if((str[i]-'A'+'a')!=tasks[j].str[i] && (str[i]-'a'+'A')!=tasks[j].str[i] && str[i]!=tasks[j].str[i])  // all must agree that letter is wrong
			{
				error=No_Matching;
			}
		}
	}
	if(error==No_Matching)
	{
		UART_SendString("Wrong Frame");
	}
	else
	{
		j--;
		tasks[j].fptr(number);
		UART_SendString("Right Frame");
	}
}*/



/***  stage1  without string separate **/

/*
void string_Compare2(u8*str)
{
u8 i=0,j=0,n=8;
Compare_t error=No_Matching;
for(j=0;j<NofTasks && error==No_Matching ;j++)
{
error =  Okk;
for(i=0; str[i]||tasks[j].str[i]; i++)
{
if((str[i]-'A'+'a')!=tasks[j].str[i] && (str[i]-'a'+'A')!=tasks[j].str[i] && str[i]!=tasks[j].str[i])  // all must agree that letter is wrong
{
error=No_Matching;
}
}
//UART_SendString(tasks[j].str);
//_delay_ms(150);
}
if(error==No_Matching)
{
UART_SendString("Wrong Frame");
}
else
{
j--;
tasks[j].fptr(n);
UART_SendString("Right Frame");
}
}


void Smart_Home_on(void)
{
UART_ReceiveString(received_string);
string_Compare(received_string);
}*/

