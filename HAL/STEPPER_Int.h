/*
 * STEPPER_Int.h
 *
 * Created: 12/15/2023 4:07:34 PM
 *  Author: DELL
 */ 


#ifndef STEPPER_INT_H_
#define STEPPER_INT_H_

#include "StdTypes.h"
#include "DIO_Int.h"




void Stepper_BiPolar_CW(void);
void Stepper_BiPolar_CCW(void);


void Stepper_UniPolar_CW(void);
void Stepper_UniPolar_CCW(void);
void Stepper_UniPolar_CW_HS(void);
void Stepper_UniPolar_CCW_HS(void);

void Stepper_By_Angle(u8 angle);
void Stepper_By_Cycle(u8 cycle);


#endif /* STEPPER_INT_H_ */