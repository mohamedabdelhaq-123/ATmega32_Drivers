


#ifndef SPI_H_
#define SPI_H_


static void (*SPI_Fptr) (void)=NULLPTR;

void SPI_Init(void);

void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);

u8 SPI_SendReceive(u8 data);
u8 SPI_ReceivePerodic(u8*pdata);
void SPI_SendNoBlock(u8 data);

#endif /* SPI_H_ */