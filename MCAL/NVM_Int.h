/*
 * NVM_Int.h
 *
 * Created: 5/5/2024 3:16:53 PM
 *  Author: DELL
 */ 


#ifndef NVM_INT_H_
#define NVM_INT_H_

void EEPROM_WriteSynch(u8 data,u16 address);

u8 EEPROM_ReadSynch(u16 address);
void NVM_SetCallBack(void(*LocalPtr)(void));
void NVM_ReadyInerruptEnable(void);
void NVM_ReadyInerruptDisable(void);

#endif /* NVM_INT_H_ */