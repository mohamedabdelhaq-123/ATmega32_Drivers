/*
 * LCD_Cfg.h
 *
 * Created: 1/31/2024 8:52:07 PM
 *  Author: DELL
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define  RS  PINA1
#define  EN  PINA2

#define  LCD_PORT   pa

#define _4_bit 1
#define _8_bit 0

#define d7 PINA6
#define d6 PINA5
#define d5 PINA4
#define d4 PINA3


/* _4_bit : _8_bit */
#define LCD_MODE  _4_bit



#endif /* LCD_CFG_H_ */