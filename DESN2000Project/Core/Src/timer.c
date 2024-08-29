#include "timer.h"
#include "LCD.h"
#include "Keypad.h"
#include "coast.h"
/*
 *
 *
 *  Created on: Aug 03, 2024
 *      Author: LF
 */
#include <stdio.h>

// Timer variables
static int timer_hour = 0;
static int timer_minute = 0;
static int timer_second = 0;
static uint8_t setting_timer = 0;
static uint8_t timer_running = 0;
static char timer_str[7] = "";
static int timer_index = 0;
static uint32_t total_timer_seconds = 0;


// Update the timer logic based on keypad input
void TIMER_Update(Memory *mem_ptr)
{
    // Update your alarm sequence here (customisable) and pending an audio sequence

    if (timer_running && timer_hour == 0 && timer_minute == 0 && timer_second == 0) {
	timer_running = 0;
	//LCD_SendCmd(LCD_CLEAR_DISPLAY);
	LCD_PrintLine1_kavisha("Timer Ended");
    }
    // Get key and base on key press decides what to do
    char key = KEYPAD_read();

	if (key == 'A') {
		mem_ptr->current_view = (((mem_ptr->current_view + 4) % 8) / 4) * 4;
		if (mem_ptr->current_view < 4) {
			//LCD_printstr("Clock Mode");
			//load_display(strings_to_page("Clock Mode", ""));
            LCD_PrintLine1_kavisha("Clock Mode");
            LCD_PrintLine2_kavisha("");

		} else {
			//LCD_printstr("Scientific Mode");
			//load_display(strings_to_page("Scientific Mode", ""));
            LCD_PrintLine1_kavisha("Scientific Mode");
            LCD_PrintLine2_kavisha("");
		}
		HAL_Delay(1000);
		return;

	} else if (key == 'B') {
		mem_ptr->current_view = ((mem_ptr->current_view + 1) % 4) + (mem_ptr->current_view/4)*4;
						if (mem_ptr->current_view >= TIMA_VIEW &&mem_ptr->current_view > mem_ptr->tim_max) {
							mem_ptr->current_view = TIMA_VIEW;
						}
						if (mem_ptr->current_view == ALRM_VIEW) {
							mem_ptr->current_view = STOP_VIEW;
						}
		return;
	}

    if (setting_timer) {
        if (key == 'D') {
            setting_timer = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            TIMER_Display();
        } else if (key == 'C') {
            if (timer_index < 6) {
                return; // Wait until full time is entered
            }
            setting_timer = 0;
            int hour = (timer_str[0] - '0') * 10 + (timer_str[1] - '0');
            int minute = (timer_str[2] - '0') * 10 + (timer_str[3] - '0');
            int second = (timer_str[4] - '0') * 10 + (timer_str[5] - '0');
            TIMER_Set(hour, minute, second);
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            TIMER_Display();
        } else if (key >= '0' && key <= '9' && timer_index < 6) {
            timer_str[timer_index++] = key;
            timer_str[timer_index] = '\0';
            LCD_PrintLine2_kavisha(timer_str);
        }
    } else {
        if (key == '#') {
            TIMER_Start();
        } else if (key == '*') {
            TIMER_Pause();
        } else if (key == 'C') {
            setting_timer = 1;
            timer_index = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            LCD_PrintLine1_kavisha("Set Timer HHMMSS");
            LCD_PrintLine2_kavisha("");
        } else if (key == 'D') {
            TIMER_Cancel();
        } else {
            TIMER_Display();
        }
    }
}

// This function is called by the TIM7 interrupt handler
void TIMER_Tick(void)
{
    if (timer_running) {
        if (timer_hour == 0 && timer_minute == 0 && timer_second == 0) {
            timer_running = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            LCD_PrintLine1_kavisha("Timer Ended");
        }

        // Decrement the timer
        if (timer_second == 0) {
            timer_second = 59;
            if (timer_minute == 0) {
                timer_minute = 59;
                if (timer_hour != 0) {
                    timer_hour--;
                }
            } else {
                timer_minute--;
            }
        } else {
            timer_second--;
        }
    }
}

// Display the current timer value on the LCD
void TIMER_Display(void)
{
    char display_str[16];
    snprintf(display_str, sizeof(display_str), "%02d:%02d:%02d", timer_hour, timer_minute, timer_second);
    LCD_PrintLine1_kavisha("Timer:");
    LCD_PrintLine2(display_str);
}

// Set the timer value in hours, minutes, and seconds
void TIMER_Set(int hour, int minute, int second)
{
    timer_hour = hour;
    timer_minute = minute;
    timer_second = second;
    total_timer_seconds = hour * 3600 + minute * 60 + second;
}

// Start the timer countdown
void TIMER_Start(void)
{
    timer_running = 1;
}

// Pause the timer countdown
void TIMER_Pause(void)
{
    timer_running = 0;
}

// Cancel the timer setting process and reset the timer
void TIMER_Cancel(void)
{
    setting_timer = 0;
    timer_running = 0;
    timer_hour = 0;
    timer_minute = 0;
    timer_second = 0;
    total_timer_seconds = 0;
    //LCD_SendCmd(LCD_CLEAR_DISPLAY);
    TIMER_Display();
}
