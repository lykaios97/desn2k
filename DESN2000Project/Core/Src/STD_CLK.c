/*
 * STD_CLK.c
 *
 *  Created on: 01/08/24
 *      Author: Linfeng
 *   Handles the logic and display of standard clock and alarm
 */

#include "main.h"
#include "Keypad.h"
#include "LCD.h"
#include "STD_CLK.h"
#include "def.h"
#include "coast.h"
#include <string.h>
#include <stdio.h>

// all the variable used by standard clock and alarm
static RTC_HandleTypeDef *rtc_handle;
static UART_HandleTypeDef *uart_handle;
static uint8_t setting_time = 0;
static uint8_t setting_date = 0;
static uint8_t setting_alarm = 0;
static uint8_t setting_day = 0;
static uint8_t snooze_prompt = 0;  // New variable to handle snooze prompt
static char time_str[7] = "";
static char date_str[7] = "";
static char alarm_time_str[5] = "";
static char alarm_day_str[2] = "";
static int time_index = 0;
static int date_index = 0;
static int alarm_time_index = 0;
static int alarm_day_index = 0;
Memory* mem;
int volume1 = 10;

// init for the standard clock require the handler hrtc and huart from main
void STD_CLK_Init(RTC_HandleTypeDef *hrtc, UART_HandleTypeDef *huart)
{
    rtc_handle = hrtc;
    uart_handle = huart;
    LCD_init();
    //LCD_SendCmd(LCD_CLEAR_DISPLAY);
    LCD_SendCmd(LCD_HOME);
}

// primary logic handling of standard clock display and alarm setting
void STD_CLK_Update(Memory *mem_ptr)
{
    mem = mem_ptr;

    // get key and base on key press decides what to do
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

    if (setting_date) {
        if (key == 'D') {
            setting_date = 0;
            setting_time = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            STD_CLK_DisplayCurrentTime();
        } else if (key == 'C') {
            if (date_index < 6) {
                return;  // Wait until full date is entered
            }
            setting_date = 0;
            setting_time = 1;
            time_index = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            LCD_PrintLine1_kavisha("Set Time(HHMMSS)");
            LCD_PrintLine2_kavisha("");

            //load_display(strings_to_page("Set Time(HHMMSS)", ""));
        } else if (key >= '0' && key <= '9' && date_index < 6) {
            date_str[date_index++] = key;
            date_str[date_index] = '\0';
            LCD_PrintLine2_kavisha(date_str);
        }
    } else if (setting_time) {
        if (key == 'D') {
            setting_date = 0;
            setting_time = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            STD_CLK_DisplayCurrentTime();
        } else if (key == 'C') {
            if (time_index < 6) {
                return;  // Wait until full time is entered
            }
            setting_time = 0;
            int hour = (time_str[0] - '0') * 10 + (time_str[1] - '0');
            int minute = (time_str[2] - '0') * 10 + (time_str[3] - '0');
            int second = (time_str[4] - '0') * 10 + (time_str[5] - '0');
            int day = (date_str[0] - '0') * 10 + (date_str[1] - '0');
            int month = (date_str[2] - '0') * 10 + (date_str[3] - '0');
            int year = (date_str[4] - '0') * 10 + (date_str[5] - '0');
            STD_CLK_SetTimeAndDate(hour, minute, second, day, month, year);
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            STD_CLK_DisplayCurrentTime();
        } else if (key >= '0' && key <= '9' && time_index < 6) {
            time_str[time_index++] = key;
            time_str[time_index] = '\0';
            LCD_PrintLine2_kavisha(time_str);
        }
    } else if (setting_alarm) {
        if (key == 'D') {
            setting_alarm = 0;
            setting_day = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            STD_CLK_DisplayCurrentTime();
        } else if (key == 'C') {
            if (alarm_time_index < 4) {
                return;  // Wait until full time is entered
            }
            setting_alarm = 0;
            setting_day = 1;
            alarm_day_index = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            LCD_PrintLine1_kavisha("Set Day(1-7)");
            LCD_PrintLine2_kavisha("");
        } else if (key >= '0' && key <= '9' && alarm_time_index < 4) {
            alarm_time_str[alarm_time_index++] = key;
            alarm_time_str[alarm_time_index] = '\0';
            LCD_PrintLine2_kavisha(alarm_time_str);
        }
    } else if (setting_day) {
        if (key == 'D') {
            setting_alarm = 0;
            setting_day = 0;
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            STD_CLK_DisplayCurrentTime();
        } else if (key == 'C') {
            if (alarm_day_index < 1) {
                return;  // Wait until day is entered
            }
            setting_alarm = 0;
            setting_day = 0;
            int alarm_hour = (alarm_time_str[0] - '0') * 10 + (alarm_time_str[1] - '0');
            int alarm_minute = (alarm_time_str[2] - '0') * 10 + (alarm_time_str[3] - '0');
            int alarm_day = alarm_day_str[0] - '0';
            STD_CLK_SetAlarm(alarm_hour, alarm_minute, alarm_day);
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            STD_CLK_DisplayCurrentTime();
        } else if (key >= '1' && key <= '7' && alarm_day_index < 1) {
            alarm_day_str[alarm_day_index++] = key;
            alarm_day_str[alarm_day_index] = '\0';
            LCD_PrintLine2_kavisha(alarm_day_str);
        }
    } else if (snooze_prompt) {
        if (key == 'C') {
            STD_CLK_AlarmDeactivateHandle();
            // Extend the alarm by 1 minute
            RTC_DateTypeDef sDate;
            RTC_TimeTypeDef sTime;

            HAL_RTC_GetTime(rtc_handle, &sTime, RTC_FORMAT_BIN);
            HAL_RTC_GetDate(rtc_handle, &sDate, RTC_FORMAT_BIN);

            int new_minutes = sTime.Minutes + 1;
            int new_hours = sTime.Hours;

            if (new_minutes >= 60) {
                new_minutes -= 60;
                new_hours += 1;
                if (new_hours >= 24) {
                    new_hours -= 24;
                }
            }

            STD_CLK_SetAlarm(new_hours, new_minutes, sDate.WeekDay);

            snooze_prompt = 0;
            //////LCD_SendCmd(LCD_CLEAR_DISPLAY);
            LCD_PrintLine1_kavisha("Alarm snoozed");
            LCD_PrintLine2_kavisha("1 min");

            mem->functions[ALRM_VIEW].completed = false;
            mem->functions[ALRM_VIEW].active = true;
            //TIM1->CCR3 = volume1;

            HAL_Delay(1000); // Show message for a second before clearing screen and reset
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
        } else if (key == 'D') {
            snooze_prompt = 0;
            STD_CLK_AlarmDeactivateHandle();
        }
    } else {
		if (key == 'D') {
			TIM1->CCR3 = 0;
			snooze_prompt = 1;
			////LCD_SendCmd(LCD_CLEAR_DISPLAY);
			LCD_PrintLine1_kavisha("Snooze?");
			LCD_PrintLine2_kavisha("C:Yes D:No");
		} else if (key == 'C') {
			setting_alarm = 1;
			alarm_time_index = 0;
			//LCD_SendCmd(LCD_CLEAR_DISPLAY);
			LCD_PrintLine1_kavisha("Set Alrm(HHMM)");
			LCD_PrintLine2_kavisha("");
		} else if (key == '#') {
			STD_CLK_SyncTime();
		} else if (key == '*') {
			setting_date = 1;
			date_index = 0;
			//LCD_SendCmd(LCD_CLEAR_DISPLAY);
			LCD_PrintLine1_kavisha("Set Date(DDMMYY)");
			LCD_PrintLine2_kavisha("");
		} else {
			STD_CLK_DisplayCurrentTime();
		}
    }
}

// general function for setting a time and date into RTC use by both manual sync and serial sync
void STD_CLK_SetTimeAndDate(int hour, int minute, int second, int day, int month, int year) {
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    sTime.Hours = hour;
    sTime.Minutes = minute;
    sTime.Seconds = second;

    sDate.Date = day;
    sDate.Month = month;
    sDate.Year = year;
    sDate.WeekDay = STD_CLK_GetWeekday(day, month, year);
    HAL_RTC_SetTime(rtc_handle, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(rtc_handle, &sDate, RTC_FORMAT_BIN);
}

// Using serial communication receive a string representing a date and time and update RTC base on that
void STD_CLK_SyncTime(void) {
    uint8_t buffer[13];  // Buffer to hold the received data
    HAL_StatusTypeDef status;

    // Initialize the buffer to zero
    memset(buffer, 0, sizeof(buffer));

    // Continuously attempt to receive data
    while (1) {
        status = HAL_UART_Receive(uart_handle, buffer, 12, 1000);

        if (status == HAL_OK) {
            buffer[12] = '\0';  // Null-terminate the string

            // Display the received string on the LCD for debugging
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            LCD_PrintLine1_kavisha((char *)buffer);  // Cast to char* for printing

            // Parse the received time and date string into integers
            int hour = (buffer[0] - '0') * 10 + (buffer[1] - '0');
            int minute = (buffer[2] - '0') * 10 + (buffer[3] - '0');
            int second = (buffer[4] - '0') * 10 + (buffer[5] - '0');
            int day = (buffer[6] - '0') * 10 + (buffer[7] - '0');
            int month = (buffer[8] - '0') * 10 + (buffer[9] - '0');
            int year = (buffer[10] - '0') * 10 + (buffer[11] - '0');

            // Update the RTC with the received time and date
            STD_CLK_SetTimeAndDate(hour, minute, second, day, month, year);

            // Clear the display and show the updated time
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            STD_CLK_DisplayCurrentTime();

            break;  // Exit the loop once data is successfully received and processed
        } else {
            //LCD_SendCmd(LCD_CLEAR_DISPLAY);
            LCD_PrintLine1_kavisha("Receiving...");
            LCD_PrintLine2_kavisha("");
        }
    }
}

// the helper function handling generating the string to be displayed in LCD
void STD_CLK_DisplayCurrentTime(void) {
    RTC_DateTypeDef sDate;
    RTC_TimeTypeDef sTime;

    HAL_RTC_GetTime(rtc_handle, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(rtc_handle, &sDate, RTC_FORMAT_BIN);

    char date_str[16];
    char time_str[16];
    char *week_day = getWeekday(sDate.WeekDay);

    // Convert 24-hour format to 12-hour format with AM/PM
    int hour = sTime.Hours;
    char am_pm[] = "AM";
    if (hour == 0) {
        hour = 12;
    } else if (hour == 12) {
        strcpy(am_pm, "PM");
    } else if (hour > 12) {
        hour -= 12;
        strcpy(am_pm, "PM");
    }
    //TIM1->CCR3 = 0;
    snprintf(date_str, sizeof(date_str), "%02d/%02d/%04d %s", sDate.Date, sDate.Month, 2000 + sDate.Year, week_day);
    snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d   %s", hour, sTime.Minutes, sTime.Seconds, am_pm);
    // print the generated string in their respective lines
    LCD_PrintLine1_kavisha(date_str);
    LCD_PrintLine2_kavisha(time_str);
}

// handle what the micro-controller do when alarm time is reached
void STD_CLK_AlarmEventHandle(void) {
    // lights up direct LEDs for debugging, customisable (you can customise the behaviour here)
    mem->functions[ALRM_VIEW].completed = true;
    mem->functions[ALRM_VIEW].active = false;

    TIM1->CCR3 = volume1;
}

// handles the disabling of alarm
void STD_CLK_AlarmDeactivateHandle(void) {
    // disable alarm in RTC (do not delete!!)
    HAL_RTC_DeactivateAlarm(rtc_handle, RTC_ALARM_A);
    // Turn off the LEDs (you can customise the behaviour here)
    LCD_PrintLine1_kavisha("DEACTIVATE");
    mem->functions[ALRM_VIEW].completed = false;
        mem->functions[ALRM_VIEW].active = false;
        //TIM1->CCR3 = 0;
}

// helper function to set alarm A
void STD_CLK_SetAlarm(int hour, int minute, int day) {
    RTC_AlarmTypeDef sAlarm = {0};
    sAlarm.AlarmTime.Hours = hour;
    sAlarm.AlarmTime.Minutes = minute;
    sAlarm.AlarmTime.Seconds = 0;
    sAlarm.AlarmDateWeekDay = day;
    sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;
    sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
    sAlarm.Alarm = RTC_ALARM_A;
    HAL_RTC_SetAlarm_IT(rtc_handle, &sAlarm, RTC_FORMAT_BIN);
}

// base on Zeller's congruence, source: https://www.geeksforgeeks.org/zellers-congruence-find-day-date/
int STD_CLK_GetWeekday(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int h = (day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    // 0=Saturday, 1=Sunday, 2=Monday, ..., 6=Friday
    return (h + 5) % 7 + 1;  // Convert to 1=Monday, 2=Tuesday, ..., 7=Sunday
}

// simple function to get a string for weekdays
char* getWeekday(int day) {
    switch(day) {
        case 1:
            return "Mon";
        case 2:
            return "Tue";
        case 3:
            return "Wed";
        case 4:
            return "Thu";
        case 5:
            return "Fri";
        case 6:
            return "Sat";
        case 7:
            return "Sun";
        default:
            return "Invalid day";
    }
}
