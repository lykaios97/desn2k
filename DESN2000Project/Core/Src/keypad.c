/*
 * keypad.c
 *
 *  Created on: sometime during lab 2
 *      Author: Linfeng
 */

/*Keypad.c*/
#include "main.h"
#include "Keypad.h"
#include "def.h"
// init for Keypad

/*
void Keypad_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Initialise Rows as Output
  GPIO_InitStruct.Pin = KEYPAD_ROW1_Pin | KEYPAD_ROW2_Pin | KEYPAD_ROW3_Pin | KEYPAD_ROW4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEYPAD_ROW1_GPIO_Port, &GPIO_InitStruct);

  // Initialise Columns as Input with Pull-Up
  GPIO_InitStruct.Pin = KEYPAD_COL1_Pin | KEYPAD_COL2_Pin | KEYPAD_COL3_Pin | KEYPAD_COL4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEYPAD_COL1_GPIO_Port, &GPIO_InitStruct);
}
*/

uint16_t KEYPAD_COL_PINS_keypad[4] = {KEYPAD_COL1_Pin, KEYPAD_COL2_Pin, KEYPAD_COL3_Pin, KEYPAD_COL4_Pin};
uint16_t KEYPAD_ROW_PINS_keypad[4] = {KEYPAD_ROW1_Pin, KEYPAD_ROW2_Pin, KEYPAD_ROW3_Pin, KEYPAD_ROW4_Pin};

char KEYMAP_keypad[4][4] = {
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'},
};

// Read the keypad input and reutrn a Char, debounce built in register keypress on release
char Keypad_GetKey(void) {
// search for the keypress
	for (int c = 0; c < 4; c++) {
		// write pin(cport, cpins[c], 1)
		HAL_GPIO_WritePin(KEYPAD_COL1_GPIO_Port, KEYPAD_COL_PINS_keypad[c], 1);
		for (int r = 0; r < 4; r++) {
			if (HAL_GPIO_ReadPin(KEYPAD_ROW1_GPIO_Port, KEYPAD_ROW_PINS_keypad[r]) == 1) {
				return KEYMAP_keypad[r][c];
				while (HAL_GPIO_ReadPin(KEYPAD_ROW1_GPIO_Port, KEYPAD_ROW_PINS_keypad[r]) == 1) {
					HAL_Delay(200);
				}
			}
		}
		HAL_GPIO_WritePin(KEYPAD_COL1_GPIO_Port, KEYPAD_COL_PINS_keypad[c], 0);
	}

  return '\0';
}

/*
uint8_t KEYPAD_read() {
	uint8_t ret = 0;
	for (int c = 0; c < 4; c++) {
		// write pin(cport, cpins[c], 1)
		HAL_GPIO_WritePin(KEYPAD_COL1_GPIO_Port, KEYPAD_COL_PINS[c], 1);
		for (int r = 0; r < 4; r++) {
			if (HAL_GPIO_ReadPin(KEYPAD_ROW1_GPIO_Port, KEYPAD_ROW_PINS[r]) == 1) {
				ret = KEYMAP[r][c];
				while (HAL_GPIO_ReadPin(KEYPAD_ROW1_GPIO_Port, KEYPAD_ROW_PINS[r]) == 1) {
					HAL_Delay(200);
				}
			}
		}
		HAL_GPIO_WritePin(KEYPAD_COL1_GPIO_Port, KEYPAD_COL_PINS[c], 0);
	}
	return ret;
}
*/
