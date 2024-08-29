/*
 * LCD.h
 *
 *  Created on: Jul 27, 2024
 *      Author: aditya
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

// LCD

// Define LCD instructions added by LF on 02/08/24
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_FUNCTION_SET 0x28 // 4-bit mode, 2 lines, 5x8 font
#define LCD_DISPLAY_ON 0x0C
#define LCD_ENTRY_MODE_SET 0x06 // Increment cursor, no shift
#define LCD_HOME 0x02

// function prototypes added by LF
void LCD_init(void);
void LCD_PutNibble(uint8_t nibble);
void LCD_Pulse(void);
void LCD_SendCmd(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_DisplayString(char* str);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_PrintLine1(char* str);
void LCD_PrintLine2(char* str);

#endif /* INC_LCD_H_ */
