/*
 *
 *
 *  Created on: Aug 03, 2024
 *      Author: LF
 */
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "main.h"

void STOPWATCH_Init(RTC_HandleTypeDef *hrtc, UART_HandleTypeDef *huart);
void STOPWATCH_Update(void);
void STOPWATCH_Tick(void);

#endif // STOPWATCH_H
