/*
 *
 *
 *  Created on: Aug 01, 2024
 *      Author: LF
 */
/* STD_CLK.h */

#ifndef __STD_CLK_H
#define __STD_CLK_H

#include "main.h"
#include "coast.h"
#include "LCD.h"
#include <stdio.h>
/* Function Prototypes */
void STD_CLK_Init(RTC_HandleTypeDef *hrtc,  UART_HandleTypeDef *huart);
void STD_CLK_SetTimeAndDate(int hour, int minute, int second, int day, int month, int year);
void STD_CLK_SyncTime(void);
void STD_CLK_DisplayCurrentTime(void);
void STD_CLK_Update(Memory *mem_ptr);
void STD_CLK_AlarmEventHandle (void);
void STD_CLK_AlarmDeactivateHandle (void);
void STD_CLK_SetAlarm(int hour, int minute, int day);
int STD_CLK_GetWeekday(int day, int month, int year);
char* getWeekday(int day);
#endif /* __STD_CLK_H */
