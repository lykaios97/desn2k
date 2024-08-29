/*
 * LEDbar.h
 *
 *  Created on: Jul 27, 2024
 *      Author: aditya
 */

#ifndef INC_LEDBAR_H_
#define INC_LEDBAR_H_

// Shift Register LED Bar
#define SR_RCLK_Pin GPIO_PIN_7
#define SR_RCLK_GPIO_Port GPIOB
#define SR_SRCLK_Pin GPIO_PIN_0
#define SR_SRCLK_GPIO_Port GPIOC
#define SR_SER_Pin GPIO_PIN_15
#define SR_SER_GPIO_Port GPIOB


void LEDBar_Load(uint16_t data);
uint16_t floatToVal(float f);
#endif /* INC_LEDBAR_H_ */
