/*
 *
 *
 *  Created on: Aug 03, 2024
 *      Author: LF
 */
#ifndef TIMER_H
#define TIMER_H

#include "main.h"
#include "coast.h"
// Update the timer logic based on keypad input
void TIMER_Update(Memory *mem_ptr);

// Display the current timer value on the LCD
void TIMER_Display(void);

// Set the timer value in hours, minutes, and seconds
void TIMER_Set(int hour, int minute, int second);

// Start the timer countdown
void TIMER_Start(void);

// Pause the timer countdown
void TIMER_Pause(void);

// Cancel the timer setting process and reset the timer
void TIMER_Cancel(void);

void TIMER_Tick(void);

#endif // TIMER_H
