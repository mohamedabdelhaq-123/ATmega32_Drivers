/*
 * DIO_Priv.h
 *
 * Created: 12/7/2023 10:50:19 PM
 *  Author: DELL
 */ 


#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_

extern const DIO_PinStatus_t DIO_PinsStatusArray[TOTAL_PINS]; // use the status array in dio only to use in func

 static void DIO_InitPin(DIO_Pin_t pin, DIO_PinStatus_t status);


#endif /* DIO_PRIV_H_ */