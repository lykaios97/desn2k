
/*
 *
 *
 *  Created on: Aug 03, 2024
 *      Author: LF
 */
#include "stopwatch.h"
#include "LCD.h"
#include "Keypad.h"
#include <stdio.h>

// Stopwatch variables
static int stopwatch_hour = 0;
static int stopwatch_minute = 0;
static int stopwatch_second = 0;
static uint8_t stopwatch_running = 0;

// Initialize the stopwatch with the RTC and UART handles


// Update the stopwatch logic based on keypad input
void STOPWATCH_Update()
{
    char key = Keypad_GetKey();

    if (key == 'C') {
        if (stopwatch_running) {
            stopwatch_running = 0;
        } else {
            stopwatch_running = 1;
        }
    } else if (key == 'D') {
        stopwatch_running = 0;
        stopwatch_hour = 0;
        stopwatch_minute = 0;
        stopwatch_second = 0;
        LCD_SendCmd(LCD_CLEAR_DISPLAY);
        STOPWATCH_Display();
    } else {
	STOPWATCH_Display();
    }
}

// This function is called by the TIM7 interrupt handler
void STOPWATCH_Tick(void)
{
    if (stopwatch_running) {
        stopwatch_second++;
        if (stopwatch_second >= 60) {
            stopwatch_second = 0;
            stopwatch_minute++;
            if (stopwatch_minute >= 60) {
                stopwatch_minute = 0;
                stopwatch_hour++;
            }
        }
    }
}

// Display the current stopwatch value on the LCD
void STOPWATCH_Display(void)
{
    char display_str[16];
    snprintf(display_str, sizeof(display_str), "%02d:%02d:%02d", stopwatch_hour, stopwatch_minute, stopwatch_second);
    LCD_PrintLine1("Stopwatch:");
    LCD_PrintLine2(display_str);
}
