#include "StdTypes.h"
#include "MemMap.h"
#include "SPI.h"
#include "SPI_Cfg.h"


void SPI_Init(void)
{
	#if SPI_MODE==Master
	
	clear_bit(SPCR,DORD);   // DORD=0, MSB transmitted first & slave must be same as Master
	set_bit(SPCR,MSTR);     // Master
	
	clear_bit(SPCR,SPR0);  // CLK= Fcpu/4 =8/4= 2 MHZ
	clear_bit(SPCR,SPR1);
	clear_bit(SPSR,SPI2X);  // double speed bit
	
	clear_bit(SPCR,CPOL);   // 1st pulse is Rising edge
	clear_bit(SPCR,CPHA);   // Read on rising edge 
	
	#elif SPI_MODE==Slave
	
	clear_bit(SPCR,DORD);   // DORD=0, MSB transmitted first & slave must be same as Master
	clear_bit(SPCR,MSTR);   // Slave
	
    #endif
	
	set_bit(SPCR,SPE);  	// SPI ENABLE
	
}


void SPI_InterruptEnable(void)
{
	set_bit(SPCR,SPIE);
}

void SPI_InterruptDisable(void)
{
	clear_bit(SPCR,SPIE);
}


ISR(SPI_STC_vect)
{
	if(SPI_Fptr!=NULLPTR)
	{
		SPI_Fptr();
	}
}

void SPI_SetCallBack(void(*LocalFptr)(void))
{
	SPI_Fptr=LocalFptr;
}

u8 SPI_SendReceive(u8 data)  // send & receive bec spi is fast 
{
	SPDR=data;               // send 
	while(!get_bit(SPSR,SPIF));  // wait till data is trans.
	return SPDR;               // receive 
}

void SPI_Send(u8 data)  
{
	SPDR=data;               
}

u8 SPI_Receive(void)  
{
	while(!get_bit(SPSR,SPIF)); 
	return SPDR;               
}


u8 SPI_ReceivePerodic(u8*pdata)  // for slave
{
	if (get_bit(SPSR,SPIF))    // flag is set when the exchange btw buffers of Master & slave 
	{
		*pdata=SPDR;
		return 1;
	}
	return 0;
}

void SPI_SendNoBlock(u8 data)  // for slave
{
	SPDR=data;   // Put data and leave
}