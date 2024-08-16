/*
 * StdTypes.h
 *
 * Created: 12/7/2023 10:17:27 PM
 *  Author: DELL
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_

#define  set_bit(reg,bit)    (reg|=(1<<bit))
#define  clear_bit(reg,bit)  (reg&=~(1<<bit))
#define  toggle_bit(reg,bit) (reg^=(1<<bit))
#define  get_bit(reg,bit)    ((reg>>bit)&1)

#define F_CPU  8000000UL
#include <util/delay.h> // has the delay function of this atmega

typedef unsigned char u8;
typedef signed char s8;
typedef char c8;

typedef unsigned int u16;
typedef signed int s16;

typedef unsigned long u32;
typedef signed long s32;

#define  NULLPTR  ((void*)0)

typedef enum{
	false,
	true,
	}Bool_t;

typedef enum{
	OK,
	NOK,
	NULL_PTR,
	OUT_OF_RANGE
}Error_t;

#define  Maxu8  ((u8)255)
#define  Minu8  ((u8)0)

#define  Maxs8  ((s8)127)
#define  Mins8  ((s8)-128)
#define  zeros8  ((s8)0)


#endif /* STDTYPES_H_ */