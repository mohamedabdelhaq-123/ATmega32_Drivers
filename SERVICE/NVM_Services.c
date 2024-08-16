#include "StdTypes.h"
#include "MemMap.h"
#include "NVM_Int.h"
#include "NVM_Services.h"
#include "NVM_Cfg.h"

void Password_WriteSynch(u8*str)
{
	for(u8 i=0;str[i];i++)
	{
		EEPROM_WriteSynch(str[i],Password_Start_address+i);
	}
}

void Password_ReadSynch(u8*str)
{
	for(u8 i=0;str[i];i++)
	{
		str[i]=EEPROM_ReadSynch(Password_Start_address+i);
		LCD_WriteString("out");
		LCD_WriteChar(str+i);
	}
}