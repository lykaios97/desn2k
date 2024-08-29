/*
 * LEDbar.c
 *
 *  Created on: Jul 27, 2024
 *      Author: aditya
 */

#include <main.h>
#include <LEDBar.h>
#include <math.h>
void LEDBar_Init() {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	// Shift Registers LED Bar
	// Configure and set pins to zero
	GPIO_InitStruct.Pin = SR_RCLK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SR_RCLK_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SR_SRCLK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SR_SRCLK_GPIO_Port, &GPIO_InitStruct);
	//
	GPIO_InitStruct.Pin = SR_SER_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SR_SER_GPIO_Port, &GPIO_InitStruct);
}


void LEDBar_Load(uint16_t data) {
	for (int i = 0; i < 16; i++){
		HAL_GPIO_WritePin(SR_SER_GPIO_Port, SR_SER_Pin, (data & 0x0001 ) ? SET : RESET);
		data >>= 1;
		// trigger clock
		HAL_GPIO_WritePin(SR_SRCLK_GPIO_Port, SR_SRCLK_Pin, SET);
		// HAL_Delay(1);
		HAL_GPIO_WritePin(SR_SRCLK_GPIO_Port, SR_SRCLK_Pin, RESET);
	}
	// trigger latch
	HAL_GPIO_WritePin(SR_RCLK_GPIO_Port, SR_RCLK_Pin, SET);
	// HAL_Delay(1);
	HAL_GPIO_WritePin(SR_RCLK_GPIO_Port, SR_RCLK_Pin, RESET);
}

uint16_t floatToVal(float f) {
	uint16_t val = 0xFFFF;
	val <<= (int)(f * 16);
	return val;
}
