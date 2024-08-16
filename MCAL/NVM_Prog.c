#include "MemMap.h"
#include "StdTypes.h"
#include "NVM_Int.h"

static void (*NVM_Fptr) (void)=NULLPTR;

void EEPROM_WriteSynch(u8 data,u16 address)
{
	while(get_bit(EECR,EEWE));  //wait till past writing operation is done
	//while(get_bit(SPMCR,SPMEN));  // unknown
	
	EEAR=address;
	EEDR=data;
	
	cli();                // critical section
	set_bit(EECR,EEMWE);
	set_bit(EECR,EEWE);   // must set before 4 cycle passes since EEMWE=1
	sei();                // glob. int. enable
}


u8 EEPROM_ReadSynch(u16 address)
{
	while(get_bit(EECR,EEWE));  //wait till past writing operation is done
	EEAR=address;
	set_bit(EECR,EERE);
	return EEDR;
}

void NVM_SetCallBack(void(*LocalPtr)(void))
{
	if(NVM_Fptr!=NULLPTR)
	{
		NVM_Fptr=LocalPtr;
	}
}

void NVM_ReadyInerruptEnable(void)
{
	set_bit(EECR,EERIE);
}

void NVM_ReadyInerruptDisable(void)
{
	clear_bit(EECR,EERIE);
}


ISR(EE_RDY_vect)
{
	if(NVM_Fptr!=NULLPTR)
	{
		NVM_Fptr();
	}
}

