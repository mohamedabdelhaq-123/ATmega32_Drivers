
#ifndef LCD_H_
#define LCD_H_





/*
#define  d7   PINA6
#define  d6   PINA5
#define  d5   PINA4
#define  d4   PINA3*/



void LCD_Init(void);

void LCD_Clear(void);

void LCD_WriteChar(u8 ch);
void LCD_WriteString(c8*str);
/** line 1:2  cell 1:16 **/
void LCD_SetCursor(u8 line ,u8 cell);

void LCD_WriteNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteBinary2(u8 num);
void LCD_WriteHex(u8 num);
void LCD_WriteHex2(u8 num);
void LCD_WriteHex3(u8 num);

void LCD_CustomChar(u8 location,u8* pattern);
void LCD_CustomChar2(void);

void LCD_ShakeWord(c8*str);

void LCD_WriteNumber_4D(u16 num);




void LCD_SetCursorString(u8 line,u8 cell,u8*str);


//https://drive.google.com/drive/folders/1_BeF51ffa8_V_pInf5cpwjPyjdSLC8HL?usp=share_link


#endif /* LCD_H_ */