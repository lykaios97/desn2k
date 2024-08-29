/*
 * LCD.c
 *
 *  Created on: Jul 27, 2024
 *      Author: aditya
 */


#include <main.h>
#include <LCD.h>
#include "def.h"
void LCD_init() {
    // Initialise LCD Display
    // E, RS, RW, D4, D5, D6, D7

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /*
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // Initialise LCD_Data
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_D4_GPIO_Port, &GPIO_InitStruct);

    // Initialise LCD_E
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = LCD_E_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_E_GPIO_Port, &GPIO_InitStruct);

    // Initialise LCD_RW
    HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = LCD_RW_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_RW_GPIO_Port, &GPIO_InitStruct);

    // Initialise LCD_RS
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = LCD_RS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_RS_GPIO_Port, &GPIO_InitStruct);
	*/
    // LCD Magic
    // 1. wait for enough time to stabilise
    HAL_Delay(50);

    // 2. send command 0011 (function set) and wait for >=4.1 ms (enough wait inside the pulse)
    LCD_PutNibble(0b0011); LCD_Pulse();

    // 3. send command 0011 (function set) again and wait for >=100 us
    LCD_PutNibble(0b0011); LCD_Pulse();

    // 4. send command 0011 (function set) again
    LCD_PutNibble(0b0011); LCD_Pulse();

    // 5. send command 0010 to set to 4-bit bus mode
    LCD_PutNibble(0b0010); LCD_Pulse();

    // 6. send command 0010 1100 (function set: 4-bit mode, 2-lines, 5x8 font)
    LCD_SendCmd(0b00101100);

    // 7. Send command 0000 1000 to display ON/OFF
    LCD_SendCmd(0b00001000);

    // 8. Send command to clear the display
    LCD_SendCmd(0b00000001);

    // 9. Send command set entry mode (increment cursor, no display shift)
    LCD_SendCmd(0b00000110);

    // 10. send command 0000 1111 to display on, cursor on, blink on
    LCD_SendCmd(0b00001111);
}

/*
 * LCD.c extra functions
 *
 *  Added on: soimtime during lab 2
 *    Author: Linfeng
 */

// General purpose function to put Nibble
void LCD_PutNibble(uint8_t nibble) {
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (nibble >> 0) & 0x01);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (nibble >> 1) & 0x01);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (nibble >> 2) & 0x01);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (nibble >> 3) & 0x01);
}

// Send pulse to LCD
void LCD_Pulse(void) {
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

// Send Command based on command ENUM
void LCD_SendCmd(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
    //HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET); kavisha took this off
    LCD_PutNibble((cmd >> 4) & 0x0F );
    LCD_Pulse();
    LCD_PutNibble((cmd >> 0) & 0x0F);
    LCD_Pulse();
    //HAL_Delay(2); kavisha took this off
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, 0);
}

// Sends a specific 8 bit data to LCD
void LCD_SendData(uint8_t data) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    //HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET); kavisha took this off
    LCD_PutNibble((data >> 4) & 0x0F );
    LCD_Pulse();
    LCD_PutNibble((data >> 0) & 0x0F );
    LCD_Pulse();
    //HAL_Delay(2); kavisha took this off
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, 0);
}

// Sends string to LCD in a loop
void LCD_DisplayString(char* str) {
    while(*str) {
        LCD_SendData(*str++);
    }
}

// Set the location of cursor starting in (0,0)
void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? col : 0x40 + col;
    LCD_SendCmd(0x80 | address);
}

// helper function to print a line in the upper part of LCD
void LCD_PrintLine1(char* str){
    LCD_SetCursor(0, 0);
    LCD_DisplayString(str);
}

// helper function to print a line in the lower part of LCD
void LCD_PrintLine2(char* str){
    LCD_SetCursor(1, 0);
    LCD_DisplayString(str);
}
