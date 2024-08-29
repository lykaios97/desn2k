/*
 * keypad.h
 *
 *  Created on: Sometime during Lab 2
 *      Author: aditya
 */


#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

// Keypad
#define KEYPAD_ROW1_Pin GPIO_PIN_11
#define KEYPAD_ROW1_GPIO_Port GPIOB
#define KEYPAD_ROW2_Pin GPIO_PIN_12
#define KEYPAD_ROW2_GPIO_Port GPIOB
#define KEYPAD_ROW3_Pin GPIO_PIN_13
#define KEYPAD_ROW3_GPIO_Port GPIOB
#define KEYPAD_ROW4_Pin GPIO_PIN_14
#define KEYPAD_ROW4_GPIO_Port GPIOB
#define KEYPAD_COL1_Pin GPIO_PIN_8
#define KEYPAD_COL1_GPIO_Port GPIOA
#define KEYPAD_COL2_Pin GPIO_PIN_9
#define KEYPAD_COL2_GPIO_Port GPIOA
#define KEYPAD_COL3_Pin GPIO_PIN_10
#define KEYPAD_COL3_GPIO_Port GPIOA
#define KEYPAD_COL4_Pin GPIO_PIN_11
#define KEYPAD_COL4_GPIO_Port GPIOA

void Keypad_Init(void);
char Keypad_GetKey(void);

#endif /* INC_KEYPAD_H_ */
