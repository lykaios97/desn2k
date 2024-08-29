/*
 * coast.c
 *
 *  Created on: Jul 27, 2024
 *      Author: aditya
 */


/*
 * coast.c
 *
 *  Created on: Jun 4, 2024
 *      Author: kavishachandraratne
 */

#include "coast.h"
#include "coast.h"
#include "def.h"
#include "Keypad.h"
#include "LCD.h"
#include "main.h"
#include "STD_CLK.h"
#include "timer.h"
#include <stdio.h>
#include <string.h>

//RTC_TypeDef* TIM1;

Time str_to_time(char *time_str);
bool play_av(AV av);
bool KEYPAD_key_pressed();
char num_to_nokia(char c, int press_count);
Page date_and_time(Time time);
Page strings_to_page(char* str1, char* str2);
uint8_t KEYPAD_read();
int task2_active = 1;
char task2_pitch_str[17] = "";
int volume = 5;
int task_num = 0;

int debug_clockAlrm = 1;
int debug_timer = 0;
int debug_stopwatch = 0;

int position = 0;

const Page start_page1 = {{
    {'S', 'c', 'i', 'e', 'n', 'T', 'i', 'm', 'e', 'r', '4', '2', '0', ' ', ' ', ' ',},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
}};

Page start_page2 = {{
    {'M', 'a', 'n', 'u', 'f', 'a', 'c', 't', 'u', 'r', 'e', 'd', ' ', 'b', 'y', ' ',},
    {'A', 'L', 'K', ' ', 'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', ' ', 'I', 'n', 'c',},
}};

Page sample = {{
    {'P', 'C', 'R', ' ', 'T', 'E', 'S', 'T', 'I', 'N', 'G', ' ', ' ', ' ', ' ', ' ', },
    {'A', ' ', ' ', ' ', '0', '1', 'h', '1', '2', 'm', '3', '2', 's', '3', '1', 'c', },
}};

AV f1_theme[] = {
    {(int)FREQ(D, 4), 2, 0xAAAA},
    {(int)FREQ(E, 4), 0.5, 0xBBBB},
    {(int)FREQ(F, 4), 0.5, 0xCCCC},
    {(int)FREQ(D, 4), 2, 0xBBBB},
    {(int)FREQ(C, 4), 2, 0xCCCC},
    {(int)FREQ(C, 4), 2, 0xBBBB},
    {(int)FREQ(A, 3), 2, 0xDDDD},
    {(int)FREQ(B, 3), 4, 0x1111},
    {0, 1, 0}, // Silence
    {(int)FREQ(D, 4), 2, 0xCCCC},
    {(int)FREQ(E, 4), 0.5, 0xBBBB},
    {(int)FREQ(F, 4), 0.5, 0xCCCC},
    {(int)FREQ(D, 4), 2, 0xBBBB},
    {(int)FREQ(C, 4), 2, 0xCCCC},
    {(int)FREQ(C, 4), 2, 0xBBBB},
    {(int)FREQ(F, 4), 2, 0xDDDD},
    {(int)FREQ(G, 4), 4, 0x1111},
};

AV darude[] = {
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 1.4, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 1.4, 0xBBBB},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},

    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(E, 4), 1.4, 0xEEEE},
    {(int)FREQ(D, 4), 0.3, 0xDDDD},
    {(int)FREQ(D, 4), 0.3, 0xDDDD},
    {(int)FREQ(D, 4), 0.3, 0xDDDD},
    {(int)FREQ(D, 4), 0.3, 0xDDDD},
    {(int)FREQ(D, 4), 0.3, 0xDDDD},
    {(int)FREQ(D, 4), 0.3, 0xDDDD},
    {(int)FREQ(D, 4), 1.4, 0xDDDD},
    {(int)FREQ(A, 3), 0.3, 0xAAAA},
    {(int)FREQ(A, 3), 0.3, 0xAAAA},

    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 1.4, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(B, 3), 1.4, 0xBBBB},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {0, 1, 0}, // Silence
};

AV alors[] = {
    {(int)FREQ(A, 3), 0.7, 0xAAAA},
	{0, 0.3, 0xBBBB},
    {(int)FREQ(D, 4), 0.7, 0xDDDD},
	{0, 0.3, 0xBBBB},
    {(int)FREQ(A, 4), 0.7, 0xAAAA},
	{0, 0.3, 0xBBBB},
    {(int)FREQ(A, 4), 0.7, 0xAAAA},
	{0, 0.3, 0xBBBB},
    {(int)FREQ(A, 4), 0.7, 0xAAAA},
    {0, 1, 0}, // Silence

    {(int)FREQ(F, 4), 0.7, 0xFFFF},
	{0, 0.3, 0xBBBB},
    {(int)FREQ(As, 4), 0.7, 0xAAAA},
	{0, 0.3, 0xBBBB},
    {(int)FREQ(E, 4), 0.7, 0xEEEE},
	{0, 0.3, 0xBBBB},
    {(int)FREQ(E, 4), 0.7, 0xEEEE},

	{0, 1, 0xBBBB},
    //{(int)FREQ(E, 4), 0.7, 0xBBBB},

    {(int)FREQ(E, 4), 0.7, 0xEEEE},
	{0, 0.7, 0xBBBB},
    {(int)FREQ(D, 4), 0.7, 0xDDDD},
	{0, 0.7, 0xBBBB},
	{(int)FREQ(F, 4), 1.4, 0xFFFF},
    {0, 0.8, 0}, // Silence
    {(int)FREQ(F, 4), 0.7, 0xFFFF},
	{0, 0.05, 0xBBBB},

	{(int)FREQ(F, 4), 1.4, 0xFFFF},
    {0, 0.8, 0}, // Silence
    {(int)FREQ(F, 4), 2.1, 0xFFFF},
	{0, 0.3, 0xBBBB},
    {(int)FREQ(G, 4), 0.7, 0xAAAA},
	{0, 0.3, 0xBBBB},
	{(int)FREQ(E, 4), 1.4, 0xEEEE},
    {0, 0.8, 0}, // Silence
    {(int)FREQ(D, 4), 0.7, 0xDDDD},
	{0, 0.3, 0xBBBB},
    {0, 1, 0}, // Silence

};

AV fur_elise[] = {
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(Ds, 4), 0.3, 0xDDDD},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(Ds, 4), 0.3, 0xBBBB},
    {(int)FREQ(E, 4), 0.3, 0xEEEE},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(D, 4), 0.3, 0xDDDD},
    {(int)FREQ(C, 4), 0.3, 0xCCCC},
    {(int)FREQ(A, 3), 0.6, 0xAAAA},
    {0, 0.3, 0xBBBB},

    {(int)FREQ(C, 3), 0.3, 0xCCCC},
	{(int)FREQ(E, 3), 0.3, 0xEEEE},
    {(int)FREQ(A, 3), 0.3, 0xAAAA},
    {(int)FREQ(B, 3), 0.6, 0xBBBB},
    {0, 0.3, 0xBBBB},
    {(int)FREQ(E, 3), 0.3, 0xEEEE},
	{(int)FREQ(Gs, 3), 0.3, 0xCCCC},
    {(int)FREQ(B, 3), 0.3, 0xBBBB},
    {(int)FREQ(C, 4), 1, 0xCCCC},
    {0, 1, 0}, // Silence
};

size_t getArrayLength(AV array[]) {
    return sizeof(f1_theme) / sizeof(f1_theme[0]);
}

Page current_page = start_page1;

Memory memory;

/*
Memory memory = {
		.name = "Testing Lab",
		.functions = {{"TIME&DATE", 11233, 3211, false, false, 0},
					  {"ALARM", 1233123, 3211123, false, false, 0},
					  {"STOPWATCH", 0, 0, false, true, 0},
					  {"TIMER", 321123, 321123, false, false, 17, f1_theme},
					  {"A.PCR TESTING", 1231, 0, false, true, 17, f1_theme},
					  {"B.ADAPTOR LIG", 12333, 0, false, false, 17, f1_theme},
					  {"C.CUTLET", 45666, 0, false, false, 17, f1_theme},
					  {"D.ROLL", 654, 0, false, false, 17, f1_theme},
		},
		.current_view = 5,
		.tim_max = 7,
};
Memory new_preset = {
		.name = "New Preset",
		.functions = {{"TIME&DATE", 11233, 3211, false, false, 0},
					  {"ALARM", 1233123, 3211123, false, false, 0},
					  {"STOPWATCH", 0, 0, false, true, 0},
					  {"TIMER", 0, 0, false, false, 17, f1_theme},
					  {"A.", 0, 0, false, false, 17, f1_theme},
					  {"B.", 0, 0, false, false, 17, f1_theme},
					  {"C.", 0, 0, false, false, 17, f1_theme},
					  {"D.", 0, 0, false, false, 17, f1_theme},
		},
		.current_view = 0,
		.tim_max = 7,
};
*/
Presets presets = {
        .len = 2,
        .array = {{  .name = "TESTING LAB",
                .functions = {{"TIME&DATE", 11233, 3211, false, false, 0},
                              {"ALARM", 1233123, 3211123, false, false, 17, f1_theme},
                              {"STOPWATCH", 0, 0, false, true, 0},
                              {"TIMER", 321123, 321123, false, false, 17, f1_theme},
                              {"A.PCR TESTING", 1234, 0, false, true, 17, f1_theme},
                              {"B.ADAPTOR LIG", 2555, 0, false, false, 43, darude},
                              {"C.CUTLET", 100, 0, true, false, 37, alors},
                              {"D.ROLL", 5999, 0, false, false, 20, fur_elise},
                },
                .current_view = 5,
                .tim_max = 7,
        },

                {        .name = "New Preset",
                        .functions = {{"TIME&DATE", 11233, 3211, false, false, 0},
                                      {"ALARM", 1233123, 3211123, false, false, 17, f1_theme},
                                      {"STOPWATCH", 0, 0, false, true, 0},
                                      {"TIMER", 0, 0, false, false, 17, f1_theme},
                                      {"A.", 0, 0, false, false, 17, f1_theme},
                                      {"B.", 0, 0, false, false, 43, darude},
                                      {"C.", 0, 0, false, false, 19, alors},
                                      {"D.", 0, 0, false, false, 20, fur_elise},
                        },
                        .current_view = 0,
                        .tim_max = 7,
                },
        },
};

uint16_t brightness = 0;
uint8_t status_D1;
uint8_t status_D2;
uint8_t status_D3;
uint8_t status_D4;

static TIM_HandleTypeDef *htim2_handle;
static TIM_HandleTypeDef *htim3_handle;



void LED_PWM_Init(TIM_HandleTypeDef *htim2, TIM_HandleTypeDef *htim3) {
	htim2_handle = htim2;
	htim3_handle = htim3;
}

static ADC_HandleTypeDef *hadc2_handle;
static ADC_HandleTypeDef *hadc3_handle;

void LDR_ADC_Init(ADC_HandleTypeDef *hadc2, ADC_HandleTypeDef *hadc3) {
	hadc2_handle = hadc2;
	hadc3_handle = hadc3;
}

void LED_state(){
	HAL_ADC_Start(&hadc2);
	HAL_ADC_Start(&hadc3);
	HAL_ADC_PollForConversion(&hadc2, 5);
	HAL_ADC_PollForConversion(&hadc3, 1);

	uint32_t ldr2 = HAL_ADC_GetValue(hadc3_handle);
	uint32_t ldr1 = HAL_ADC_GetValue(hadc2_handle);

	status_D1 = memory.functions[TIMA_VIEW].active;
	status_D2 = memory.functions[TIMB_VIEW].active;
	status_D3 = memory.functions[TIMC_VIEW].active;
	status_D4 = memory.functions[TIMD_VIEW].active;

	//TODO: Get this calibrated
	if (ldr1 > 1000) {
		brightness = 1000;
	} else if ( ldr1 < 50) {
		brightness = 100;
	} else {
		brightness = 1000 - ldr1;
	}

	TIM2->CCR1 = brightness;
	TIM2->CCR3 = status_D1 ? brightness : 0;
	TIM3->CCR1 = status_D2 ? brightness : 0;
	TIM3->CCR2 = status_D3 ? brightness : 0;
	TIM2->CCR2 = status_D4 ? brightness : 0;
}
void coast_gpio_init() {
	LCD_init();
	load_set_reg_num(0);
    STD_CLK_Init(&hrtc, &huart2);
    //Keypad_Init();
    //LCD_init();
	LDR_ADC_Init(&hadc2, &hadc3);

	LED_PWM_Init(&htim2, &htim3);
    //TIM1 = htim1.Instance;
}

void coast_start() {
	switch (task_num) {
	case 0:
	    //Keypad_Init();
	    LCD_init();
		project_start();
		break;
	case 1:
	    //Keypad_Init();
	    LCD_init();
		break;
	}
}

void coast_loop_body() {
	switch (task_num) {
	case 0:
		project();
		break;
	case 1:
		STD_CLK_Update(&memory);
		/*
	    if (debug_clockAlrm == 1) {
		} else if (debug_timer == 1) {
			TIMER_Update(&memory);
		} else if (debug_stopwatch == 1) {
			STOPWATCH_Update(&memory);
	    }
	    */

	    break;
	}
	LED_state();
	//	  LEDBar_Load(floatToVal(0.5));
}

void coast_handle_interrupt(uint16_t GPIO_Pin) {
	switch (task_num) {
	case 0:
		for (int i = TIMR_VIEW; i <=TIMD_VIEW && i <=memory.tim_max; i++) {
			memory.functions[i].completed = false;
		}

		if (GPIO_Pin == SW1_Pin) {
			memory.current_view = TIMA_VIEW;
			if (memory.functions[TIMA_VIEW].time != 0) {
				memory.functions[memory.current_view].active = !memory.functions[memory.current_view].active;
			}
		} else if (GPIO_Pin == SW2_Pin) {
			memory.current_view = TIMB_VIEW;
			if (memory.functions[memory.current_view].time != 0) {
				memory.functions[memory.current_view].active = !memory.functions[memory.current_view].active;
			}
		} else if (GPIO_Pin == SW3_Pin) {
			memory.current_view = TIMC_VIEW;
			if (memory.functions[memory.current_view].time != 0) {
				memory.functions[memory.current_view].active = !memory.functions[memory.current_view].active;
			}
		} else if (GPIO_Pin == B1_Pin) {
			for (int VIEW = TIMA_VIEW; VIEW <= memory.tim_max; VIEW++) {
				if (memory.functions[VIEW].time != 0 && !memory.functions[VIEW].completed) {
					memory.functions[VIEW].active = true;
				}
			}
		}
	}
}

// uint16_t D_PORTS[4] = {D1_GPIO_Port, D2_GPIO_Port, D3_GPIO_Port, D4_GPIO_Port};
// uint16_t D_PINS[4] = {D1_Pin, D2_Pin, D3_Pin, D4_Pin};

void coast_handle_tim7_interrupt(void) {
    // lights up direct LEDs for debugging, customisable (you can customise the behaviour here)
	/*
	for (int i = 0; i <= TIM_MAX-TIMA_VIEW; i++) {
		if (memory.functions[i+TIMA_VIEW].active) {
		    HAL_GPIO_TogglePin(D_PORTS[i], D_PINS[i]);
		} else {
		    HAL_GPIO_WritePin(D_PORTS[i], D_PINS[i], 0);
		}
	}
	if (memory.functions[TIMA_VIEW].active) {
		HAL_GPIO_TogglePin(D1_GPIO_Port, D1_Pin);
	} else {
		//HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, 0);
	}
*/


}

void coast_handle_tim6_interrupt() {
	// increment stopwatch if active
	// decrement all active timers
	if (memory.functions[STOP_VIEW].active) {
		memory.functions[STOP_VIEW].time += 1;
	}
	for (int i = TIMR_VIEW; i <= memory.tim_max; i++) {
		if (memory.functions[i].active) {
			if (memory.functions[i].time == 0) {
				for (int j = TIMR_VIEW; j <= memory.tim_max && j <=memory.tim_max; j++) {
					memory.functions[j].completed = false;
				}
				memory.functions[i].active = false;
				memory.functions[i].completed = true;
			} else {
				memory.functions[i].time -= 1;
			}
			if (i > TIMR_VIEW) {
				// HAL_GPIO_TogglePin(D1_GPIO_Port, D1_Pin);
				status_D1 = !status_D1;
			} else {
				// HAL_GPIO_TogglePin(D1_GPIO_Port, D1_Pin);
				status_D1 = !status_D1;
			}
		} else {
			if (i > TIMR_VIEW) {
				// HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, 0);
				status_D1 = 0;
			} else {
				// HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, 1);
				status_D1 = 1;
			}

		}
	}
}
void project_start() {
    display_initial_message();

	load_display(strings_to_page("Configure", ""));
    HAL_Delay(1000);
    // cycle thorugh presets if new is chosen copy that to the next place and get input
    configure_preset();
    initialise_memory_views();
}

void configure_preset()
{
    int p = 0;
    int repeat_preset = true;
    while (repeat_preset)
    {
        load_display(strings_to_page("Select Preset", presets.array[p].name));
        handle_preset_selection(&p, &repeat_preset);
    }
}

void handle_preset_selection(int *p, bool *repeat_preset)
{
	for (int i = 0; i < 1000; i++)
	{
		char c = KEYPAD_read();
		if (c != 0)
		{
			if (c == 'B')
			{
				*p = (*p + 1) % presets.len;
			}
			else if (c == 'C')
			{
				memory = presets.array[*p];
				if (*p == presets.len - 1)
				{
					add_new_preset();
				}
				*repeat_preset = false;
				break;
			}
		}
	}
}

void add_new_preset()
{
	presets.array[presets.len] = presets.array[presets.len - 1];
	presets.len += 1;

	char label[16] = "";
	
	get_preset_label(label);

	

	load_display(strings_to_page("Enter Num Timers", "Between 1-4"));
	HAL_Delay(1000);
	load_display(strings_to_page("Enter Num Timers", ""));
	while (true)
	{
		char c = KEYPAD_read();
		if (c >= '1' && c <= '4')
		{
			char buff[2];
			buff[0] = c;
			buff[1] = '\0';
			load_display(strings_to_page("Enter Num Timers", buff));
			memory.tim_max = atoi(buff) + 3;
			HAL_Delay(200);
			break;
		}
	}

	for (int VIEW = TIMA_VIEW; VIEW <= memory.tim_max; VIEW++)
	{
		memory.current_view = VIEW;
		edit_label();
		edit_duration();
	}
}

void get_preset_label(char *label)
{
	load_display(strings_to_page("Preset Label", ""));
	// LCD_SendCmd(0x80 | 0x40);
	LCD_SetCursor(1, 0);
	HAL_Delay(200);

	bool repeat = true;
	
	while (repeat)
	{
		load_display(strings_to_page("Preset Label", label));
		// LCD_SendCmd(0x80 | 0x40 + strlen(label));
		LCD_SetCursor(1, strlen(label));
		for (int i = 0; i < 10000; i++)
		{

			char c = KEYPAD_read();
			if (c != 0)
			{
				HAL_Delay(100);
				if (c == '*')
				{
					// backspace
					if (strlen(label) > 0){
						label[strlen(label) - 1] = '\0';
					}

					load_display(strings_to_page("Preset Label", label));
					LCD_SetCursor(1, strlen(label));
					// LCD_SendCmd(0x80 | 0x40 + strlen(label));

					continue;
				}
				else if (c == '#')
				{
					// enter - finish entering label
					repeat = false;
					break;
				}
				else if (c >= '0' && c <= '9')
				{
					append_char_to_label(c, label);
					// char *name = label;
					// LCD_SendCmd(0x80 | strlen(label));
					LCD_SetCursor(0, strlen(label));
					break;
				}
			}
		}
	}
}

void append_char_to_label(char c, char *label)
{
	// Find the current length of the name string
	size_t len = strlen(label);

	int press_count = 1;
	// Ensure there is space to add one more character and a null terminator
	if (len < 17 - 1)
	{
		label[len] = num_to_nokia(c, press_count);
		label[len + 1] = '\0';
	}

	load_display(strings_to_page("Preset Label", label));
	// LCD_SendCmd(0x80 | 0x40 + strlen(label) - 1);
	LCD_SetCursor(1, strlen(label) - 1);

	int repeat = 1;
	int j = 0;
	while (repeat && j < 2)
	{
		j++;
		for (int i = 0; i < 20000; i++)
		{
			char r = KEYPAD_read();
			if (r != c && r != 0)
			{
				repeat = 0;
				break;
			}
			if (r == c)
			{
				press_count++;
				label[len] = num_to_nokia(c, press_count);
				load_display(strings_to_page("Preset Label", label));
				j = 0;
				break;
			}
		}
		// LCD_SendCmd(0x80 | 0x40 + strlen(label) - 1);
		LCD_SetCursor(1, strlen(label) - 1);
	}
}


void initialise_memory_views()
{
	memory.current_view = 0;

    for (int VIEW = TIMA_VIEW; VIEW <= TIMD_VIEW; VIEW++)
    {
        memory.functions[VIEW].time = memory.functions[VIEW].duration;
        memory.functions[VIEW].active = false;
        memory.functions[VIEW].completed = false;
    }
}

void display_initial_message()
{
    load_display(strings_to_page("", ""));
    HAL_Delay(1000);
    load_display(strings_to_page("ScienTimer 420", ""));
    HAL_Delay(1000);
    load_display(strings_to_page("Manufactured by", "ALK EMBEDDED INC"));
    HAL_Delay(1000);
    
}

void edit_label() {

	char buffer[16];

	switch(memory.current_view) {
	case TIMA_VIEW:
		strcpy(buffer, "Timer 1");
		break;
	case TIMB_VIEW:
		strcpy(buffer, "Timer 2");
		break;
	case TIMC_VIEW:
		strcpy(buffer, "Timer 3");
		break;
	case TIMD_VIEW:
		strcpy(buffer, "Timer 4");
		break;
	}

	load_display(strings_to_page(buffer, "Edit LABEL"));
	HAL_Delay(500);

	LCD_load_display_edit();
	LCD_SendCmd(0x80 | strlen(memory.functions[memory.current_view].name));

	bool repeat = true;

	while (repeat) {

		for (int i = 0; i < 10000; i++) {

			char c = KEYPAD_read();

			if (c != 0) {
				char str[2];
				str[0] = c;
				str[1] = '\0';

				HAL_Delay(100);
				if (c == '*') {
					// backspace
					//load_display(strings_to_page("", "backspace"));
					//HAL_Delay(100);
					int current_view = memory.current_view;
					char* name = memory.functions[current_view].name;

					// Find the current length of the name string
					size_t len = strlen(name);

					name[len-1] = '\0';


					LCD_load_display_edit();
					LCD_SendCmd(0x80 | strlen(memory.functions[memory.current_view].name));
					continue;
				} else if (c == '#') {
					repeat = false;
					break;
				} else if (c >= '0' && c <= '9') {
					int current_view = memory.current_view;
					char* name = memory.functions[current_view].name;

					// Find the current length of the name string
					size_t len = strlen(name);

					int press_count = 1;
					// Ensure there is space to add one more character and a null terminator
					if (len < 17 - 1) {
						name[len] = num_to_nokia(c, press_count);
						name[len + 1] = '\0';
					}

					LCD_load_display_edit();
					LCD_SendCmd(0x80 | strlen(memory.functions[memory.current_view].name)-1);

					int repeat = 1;
					int j = 0;
					while (repeat && j < 2) {
						j++;
						for (int i = 0; i < 20000; i++) {
							char r = KEYPAD_read();
							if (r != c && r != 0) {
								repeat = 0;

								break;
							}
							if (r == c) {
								press_count++;
								name[len] = num_to_nokia(c, press_count);
								LCD_load_display_edit();
								j = 0;
								break;
							}
						}
						LCD_SendCmd(0x80 | strlen(memory.functions[memory.current_view].name)-1);
					}

					LCD_SendCmd(0x80 | strlen(memory.functions[memory.current_view].name));
					break;
				}
			}
		}
	}
}

uint16_t get_bar(int VIEW) {
	uint32_t time = memory.functions[VIEW].time;
	uint32_t duration =  memory.functions[VIEW].duration;

    // Avoid division by zero
    if (duration == 0) {
        return 0xFFFF; // If duration is zero, return all 1's
    }

    // Calculate the proportion as a float
    float proportion = (float)time / (float)duration;

    // Normalize the proportion to the range [0, 16]
    uint8_t numberOfOnes = (uint8_t)(proportion * 16);

    // Create the 16-bit value with numberOfOnes leading 1's
    uint16_t leftFilledValue = 0xFFFF << (16 - numberOfOnes);
		/*
	for (int i = 0; i <= TIM_MAX-TIMA_VIEW; i++) {
		if (memory.functions[i+TIMA_VIEW].active) {
		    HAL_GPIO_TogglePin(D_PORTS[i], D_PINS[i]);
		} else {
		    HAL_GPIO_WritePin(D_PORTS[i], D_PINS[i], 0);
		}
	}
		*/

    if (memory.functions[VIEW].shift_reg_value == leftFilledValue && memory.functions[VIEW].active) {
    	memory.functions[VIEW].shift_reg_value = 0;
    	return 0;
    } else {
    	memory.functions[VIEW].shift_reg_value = leftFilledValue;
    }

    return leftFilledValue;
}

void project() {

	play_audio_visual();

	switch (memory.current_view) {

	case CLCK_VIEW:

		STD_CLK_Update(&memory);
		break;
	case ALRM_VIEW:

		TIMER_Update(&memory);
		break;
	default:

		LCD_load_display();

		load_set_reg_num(get_bar(memory.current_view));

		if (is_SW4_pressed_debouncing_method2()) {
			if (memory.tim_max == 7) {
				memory.current_view = TIMD_VIEW;
				if (memory.functions[TIMD_VIEW].time != 0) {
					memory.functions[memory.current_view].active = !memory.functions[memory.current_view].active;
				}
			}
		}

		for (int i = 0; i < 1000; i++) {
			char c = KEYPAD_read();

			if (c == 'A') {
				memory.current_view = (((memory.current_view + 4) % 8) / 4) * 4;
				if (memory.current_view < 4) {
					//LCD_printstr("Clock Mode");
					load_display(strings_to_page("Clock Mode", ""));

				} else {
					//LCD_printstr("Scientific Mode");
					load_display(strings_to_page("Scientific Mode", ""));
				}
				HAL_Delay(1000);

			} else if (c == 'B') {
				memory.current_view = ((memory.current_view + 1) % 4) + (memory.current_view/4)*4;
				if (memory.current_view >= TIMA_VIEW && memory.current_view > memory.tim_max) {
					memory.current_view = TIMA_VIEW;
				}
				if (memory.current_view == ALRM_VIEW) {
					memory.current_view = STOP_VIEW;
				}
			} else if (c == 'C') {
				// SET
				switch (memory.current_view) {
				case ALRM_VIEW:
					memory.functions[memory.current_view].active = !memory.functions[memory.current_view].active;
					if (memory.functions[memory.current_view].active) {
						load_display(strings_to_page("", "ALARM ON"));
					} else {
						load_display(strings_to_page("", "ALARM OFF"));
					}
					HAL_Delay(100);
					break;
				case STOP_VIEW:
					memory.functions[memory.current_view].active = !memory.functions[memory.current_view].active;
					if (memory.functions[memory.current_view].active) {
						//load_display(strings_to_page("", "Starting"));
					} else {
						//load_display(strings_to_page("", "Pausing"));
					}
					//HAL_Delay(100);
					break;
				default:
					if (memory.functions[memory.current_view].time != 0) {
						memory.functions[memory.current_view].active = !memory.functions[memory.current_view].active;

					}
					if (memory.functions[memory.current_view].active) {
						//load_display(strings_to_page("", "Starting TIMER"));
					} else {
						//load_display(strings_to_page("", "Pausing TIMER"));
					}
					//HAL_Delay(100);
					break;
				}

			} else if (c == 'D') {
				// RESET
				switch (memory.current_view) {
				case CLCK_VIEW:
					/*
					 *
					 */
					break;
				case ALRM_VIEW:
					/*
					memory.functions[memory.current_view].time = memory.functions[memory.current_view].duration;
					memory.functions[memory.current_view].active = false;
					load_display(strings_to_page("", "Resetting ALARM"));

					HAL_Delay(100);
					*/
					break;

				default:
					memory.functions[memory.current_view].time = memory.functions[memory.current_view].duration;
					memory.functions[memory.current_view].active = false;
					load_display(strings_to_page("", "Resetting TIMER"));

					HAL_Delay(100);
					break;
				}

			} else if (c == '#') { //EDIT MODE

				if (memory.current_view >= TIMR_VIEW && memory.current_view <= TIMD_VIEW) {

					if (memory.functions[memory.current_view].active) {
						load_display(strings_to_page("", "Editing Disabled"));
						HAL_Delay(100);
						break;
					}

					if (memory.current_view >= TIMA_VIEW && memory.current_view <= TIMD_VIEW) {
						edit_label();
					}

					edit_duration();

					break;
				}

			}
		}
		break;
	}
}

void edit_duration() {

	load_display(strings_to_page("", "Edit DURATION"));
	HAL_Delay(500);
	bool repeat = true;
	char time_str[13] = "00h00m00s00c";
	int at = 0;
	while (repeat) {
		load_display(strings_to_page("Edit DURATION", time_str));
		LCD_SendCmd(0x80 | 0x40+at);
		memory.functions[memory.current_view].duration = str_to_time(time_str);
		for (int i = 0; i < 10000; i++) {

			char c = KEYPAD_read();

			if (c == '*') {
				time_str[at] = '0';
				memory.functions[memory.current_view].duration = str_to_time(time_str);
				load_display(strings_to_page("Edit DURATION", time_str));
				LCD_SendCmd(0x80 | 0x40+at);
				if (at != 0) {
					at -= 1;
					if (at % 3 == 2) {
						at--;
					}
				}
			} else if (c == '#') {
				repeat = false;
				break;
			} else if (c >= '0' && c <= '9') {
				time_str[at] = c;
				memory.functions[memory.current_view].duration = str_to_time(time_str);
				load_display(strings_to_page("Edit DURATION", time_str));
				LCD_SendCmd(0x80 | 0x40+at);
				at += 1;
				if (at % 3 == 2) {
					at++;
				}
				if (at > 11) {
					repeat = false;
					break;
				}
			}

		}
	}
	memory.functions[memory.current_view].time = memory.functions[memory.current_view].duration;
	load_display(strings_to_page("", "Saved"));
	HAL_Delay(100);
}

Time str_to_time(char time_str[13]) {
	time_str[12] = '\0';
    int hours, minutes, seconds, centiseconds;

    // Extract hours, minutes, seconds, and centiseconds from the string
    sscanf(time_str, "%02dh%02dm%02ds%02dc", &hours, &minutes, &seconds, &centiseconds);

    // Convert the time to centiseconds
    int totalCentiseconds = (hours * 3600 * 100) + (minutes * 60 * 100) + (seconds * 100) + centiseconds;

    return totalCentiseconds;
}

void play_audio_visual() {
    for (int i = TIMR_VIEW; i <=TIMD_VIEW && i <= memory.tim_max; i++) {
		//TIM1->CCR3 = 0;

		while(memory.functions[i].completed == true) {

			for (int j = 0; j < memory.functions[i].av_length; j++) {
				if (memory.functions[i].completed == false) {
					i = TIMR_VIEW;
					break;
				}

				load_display(strings_to_page("Timer Finished", memory.functions[i].name));

				if (play_av(memory.functions[i].av_array[j])) {
					load_set_reg_num(~0);
					memory.functions[i].completed = false;
					i = TIMR_VIEW;
					TIM1->CCR3 = 0;
					break;
				}
			}
		}
    }
}

bool play_av(AV av) {
	int beat = 320;

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns(av.freq) - 1;
	load_set_reg_num(av.lights);
	//HAL_Delay(beat * av.beats);

	for (int i = 0; i < 7000*av.beats; i++) {
		if (KEYPAD_key_pressed()) {
			return true;
		}
	}

	TIM1->CCR3 = 0;
	load_set_reg_num(0);

	/*
	for (int i = 0; i < 5*av.beats; i++) {
		if (KEYPAD_key_pressed()) {
			return true;
		}
	}
*/
	return false;
}

int timestr_to_time(char *buffer) {
	uint32_t hours, minutes, seconds, centiseconds;
	sscanf(buffer, "%02u%02u%02u%02u", &hours, &minutes, &seconds, &centiseconds);
	return (hours * 360000) + (minutes * 6000) + (seconds * 100) + centiseconds;
}

char num_to_nokia(char c, int press_count) {
    switch (c) {
        case '1':
            return "1"[press_count%1 - 1];
        case '2':
            return "ABC2"[(press_count - 1)%4];
        case '3':
            return "DEF3"[(press_count - 1)%4];
        case '4':
            return "GHI4"[(press_count - 1)%4];
        case '5':
            return "JKL5"[(press_count - 1)%4];
        case '6':
            return "MNO6"[(press_count - 1)%4];
        case '7':
            return "PQRS7"[(press_count - 1)%5];
        case '8':
            return "TUV8"[(press_count - 1)%4];
        case '9':
            return "WXYZ9"[(press_count - 1)%5];
        case '0':
            return " 0"[(press_count - 1)%2];  // Space character for '0'
        default:
            return 0;  // Invalid input
	}
}

// Function to append a character to a string
void append_char_to_string(char* str, char c, size_t buffer_size) {
    size_t len = strlen(str);
    if (len + 1 < buffer_size) {
        str[len] = c;
        str[len + 1] = '\0';
    } else {
        // Handle buffer overflow
        printf("Buffer overflow: cannot append character\n");
    }
}

void LCD_load_display(char key) {
	char buffer[17];
	switch (memory.current_view) {
	case CLCK_VIEW:
	    //time_to_timediff_string(memory.functions[memory.current_view].time, buffer);
	    //load_display(date_and_time(memory.functions[memory.current_view].time));
	    //load_display(strings_to_page(memory.functions[memory.current_view].name, buffer));

		//STD_CLK_Update();
		//display_current_time();

		//STD_CLK_Update(key);

		break;
	case ALRM_VIEW:
	    time_to_timeofday_string(memory.functions[memory.current_view], buffer);
	    load_display(strings_to_page("ALARM      DAILY", buffer));

		//TIMER_Update();
		break;
	default:
	    time_to_timediff_string(memory.functions[memory.current_view], buffer);
		load_display(strings_to_page(memory.functions[memory.current_view].name, buffer));
		break;
	}
}

void display_current_time() {
    RTC_DateTypeDef sDate;
    RTC_TimeTypeDef sTime;

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    char date_str[17];
    char time_str[17];
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

    snprintf(date_str, 17, "%02d/%02d/%04d %s", sDate.Date, sDate.Month, 2000 + sDate.Year, week_day);
    snprintf(time_str, 17, "%02d:%02d:%02d   %s", hour, sTime.Minutes, sTime.Seconds, am_pm);

    // print the generated string in their respective lines

	//snprintf(date_str, 17, "DATE  21/07/2024");
	//snprintf(time_str, 17, "TIME    12:32:32");
    //LCD_PrintLine1(date_str);
    //LCD_PrintLine2(time_str);

    load_display(strings_to_page(date_str, time_str));
}

void LCD_load_display_edit() {
	char buffer[17];
	switch (memory.current_view) {
	case ALRM_VIEW:
	    time_to_timeofday_string(memory.functions[memory.current_view], buffer);
	    load_display(strings_to_page("ALARM      DAILY", buffer));
		break;
	default:
	    time_to_timediff_string_edit(memory.functions[memory.current_view], buffer);
		load_display(strings_to_page(memory.functions[memory.current_view].name, buffer));
		break;
	}
}

Page date_and_time(Time time) {
	char buffer1[17];
	char buffer2[17];

	snprintf(buffer1, 17, "DATE  21/07/2024");
	snprintf(buffer2, 17, "TIME    12:32:32");
	return strings_to_page(buffer1, buffer2);
}

void time_to_timediff_string(Function func, char* buffer) {
    // Calculate hours, minutes, seconds, and centiseconds
    uint32_t hours = func.time / 360000;
    uint32_t minutes = (func.time % 360000) / 6000;
    uint32_t seconds = (func.time % 6000) / 100;
    uint32_t centiseconds = func.time % 100;

    // Format the string with leading zeros
    if (func.active) {
    	snprintf(buffer, 17, "ON  %02uh%02um%02us%02uc", hours, minutes, seconds, centiseconds);
    } else {
    	snprintf(buffer, 17, "OFF %02uh%02um%02us%02uc", hours, minutes, seconds, centiseconds);
    }
}

void time_to_timediff_string_edit(Function func, char* buffer) {
    // Calculate hours, minutes, seconds, and centiseconds
    uint32_t hours = func.time / 360000;
    uint32_t minutes = (func.time % 360000) / 6000;
    uint32_t seconds = (func.time % 6000) / 100;
    uint32_t centiseconds = func.time % 100;

    // Format the string with leading zeros
    if (func.active) {
    	snprintf(buffer, 17, "ON  %02uh%02um%02us%02uc", hours, minutes, seconds, centiseconds);
    } else {
    	snprintf(buffer, 17, "    %02uh%02um%02us%02uc", hours, minutes, seconds, centiseconds);
    }
}

void time_to_timeofday_string(Function func, char* buffer) {
    // Calculate hours, minutes, seconds, and centiseconds
    uint32_t hours = func.time / 360000;
    uint32_t minutes = (func.time % 360000) / 6000;

    // Format the string with leading zeros

    if (func.active) {
    	snprintf(buffer, 17, "ON         %02u:%02um", hours, minutes);
    } else {
    	snprintf(buffer, 17, "OFF        %02u:%02um", hours, minutes);
    }
}

Page strings_to_page(char* str1, char* str2) {
    Page page;

    // Initialize the entire content array to spaces
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 16; ++j) {
            page.content[i][j] = ' ';
        }
    }

    // Copy str1 to the first row of content without null-terminator
    for (int i = 0; i < 16 && str1[i] != '\0'; ++i) {
        page.content[0][i] = str1[i];
    }

    // Copy str2 to the second row of content without null-terminator
    for (int i = 0; i < 16 && str2[i] != '\0'; ++i) {
        page.content[1][i] = str2[i];
    }

    return page;
}

void display_screen(char* line1, char* line2) {
	LCD_goto_line(0);
	LCD_printstr(line1);
	LCD_goto_line(1);
	LCD_printstr(line2);
	LCD_goto_line(0);
}


void LCD_goto_line(int l) {
	if (l == 0) {
		LCD_SendCmd(0x80 | 0x00); // move cursor to line 0
		position = 0;
	} else if (l == 1) {
		LCD_SendCmd(0x80 | 0x40); // move cursor to line 1
		position = 16;
	}
}

uint16_t KEYPAD_COL_PINS[4] = {KEYPAD_COL1_Pin, KEYPAD_COL2_Pin, KEYPAD_COL3_Pin, KEYPAD_COL4_Pin};
uint16_t KEYPAD_ROW_PINS[4] = {KEYPAD_ROW1_Pin, KEYPAD_ROW2_Pin, KEYPAD_ROW3_Pin, KEYPAD_ROW4_Pin};

uint8_t KEYMAP[4][4] = {
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'},
};

uint8_t KEYPAD_read() {
	uint8_t ret = 0;
	for (int c = 0; c < 4; c++) {
		// write pin(cport, cpins[c], 1)
		HAL_GPIO_WritePin(KEYPAD_COL1_GPIO_Port, KEYPAD_COL_PINS[c], 1);
		for (int r = 0; r < 4; r++) {
			if (HAL_GPIO_ReadPin(KEYPAD_ROW1_GPIO_Port, KEYPAD_ROW_PINS[r]) == 1) {
				ret = KEYMAP[r][c];
				while (HAL_GPIO_ReadPin(KEYPAD_ROW1_GPIO_Port, KEYPAD_ROW_PINS[r]) == 1) {
					for (int k = 0; k < 10; k++) {
						if (is_SW4_pressed_debouncing_method2()) {
							if (memory.tim_max == 7) {
								memory.current_view = TIMD_VIEW;
								if (memory.functions[TIMD_VIEW].time != 0) {
									memory.functions[memory.current_view].active = !memory.functions[memory.current_view].active;
								}
							}
						}
					}
				}
			}
		}
		HAL_GPIO_WritePin(KEYPAD_COL1_GPIO_Port, KEYPAD_COL_PINS[c], 0);
	}
	return ret;
}

bool KEYPAD_key_pressed() {
	for (int c = 0; c < 4; c++) {
		// write pin(cport, cpins[c], 1)
		HAL_GPIO_WritePin(KEYPAD_COL1_GPIO_Port, KEYPAD_COL_PINS[c], 1);
		for (int r = 0; r < 4; r++) {
			if (HAL_GPIO_ReadPin(KEYPAD_ROW1_GPIO_Port, KEYPAD_ROW_PINS[r]) == 1) {
				return true;
			}
		}
		HAL_GPIO_WritePin(KEYPAD_COL1_GPIO_Port, KEYPAD_COL_PINS[c], 0);
	}
	return false;
}

// Smart load to prevent flashing
void load_display(Page page) {
    for (int line = 0; line < 2; line++) {
    	int cursor_shift = 0;
    	LCD_SendCmd(0x80 | line*0x40); // move cursor to pos
        for (int pos = 0; pos < 16; pos++) {

            // Check if char at position has to be changed
            if (page.content[line][pos] != current_page.content[line][pos]) {

                if (cursor_shift != 0) {
                    // shift cursor by cursor_shift positions to the right to current
                    LCD_SendCmd(0x80 | line*0x40 + pos); // move cursor to pos
                    cursor_shift = 0;
                }

                // Put char at current location
                LCD_SendData((uint8_t) page.content[line][pos]);
            } else {
                cursor_shift++;
            }
        }
    }
    LCD_SendCmd(0x80 | 33);
    current_page = page;
}

void LCD_PrintLine1_kavisha(char * str1) {
    Page page;

    // Initialize the entire content array to spaces
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 16; ++j) {
            page.content[i][j] = ' ';
        }
    }

    // Copy str2 to the second row of content without null-terminator
    for (int i = 0; i < 16 && str1[i] != '\0'; ++i) {
        page.content[0][i] = str1[i];
    }

    // Copy str1 to the first row of content without null-terminator
    for (int i = 0; i < 16 && current_page.content[1][i] != '\0'; ++i) {
        page.content[1][i] = current_page.content[1][i];
    }

    for (int line = 0; line < 2; line++) {
    	int cursor_shift = 0;
    	LCD_SendCmd(0x80 | line*0x40); // move cursor to pos
        for (int pos = 0; pos < 16; pos++) {

            // Check if char at position has to be changed
            if (page.content[line][pos] != current_page.content[line][pos]) {

                if (cursor_shift != 0) {
                    // shift cursor by cursor_shift positions to the right to current
                    LCD_SendCmd(0x80 | line*0x40 + pos); // move cursor to pos
                    cursor_shift = 0;
                }

                // Put char at current location
                LCD_SendData((uint8_t) page.content[line][pos]);
            } else {
                cursor_shift++;
            }
        }
    }
    LCD_SendCmd(0x80 | 33);
    current_page = page;
}

void LCD_PrintLine2_kavisha(char * str2) {
    Page page;

    // Initialize the entire content array to spaces
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 16; ++j) {
            page.content[i][j] = ' ';
        }
    }

    // Copy str1 to the first row of content without null-terminator
    for (int i = 0; i < 16 && current_page.content[0][i] != '\0'; ++i) {
        page.content[0][i] = current_page.content[0][i];
    }

    // Copy str2 to the second row of content without null-terminator
    for (int i = 0; i < 16 && str2[i] != '\0'; ++i) {
        page.content[1][i] = str2[i];
    }

    for (int line = 0; line < 2; line++) {
    	int cursor_shift = 0;
    	LCD_SendCmd(0x80 | line*0x40); // move cursor to pos
        for (int pos = 0; pos < 16; pos++) {

            // Check if char at position has to be changed
            if (page.content[line][pos] != current_page.content[line][pos]) {

                if (cursor_shift != 0) {
                    // shift cursor by cursor_shift positions to the right to current
                    LCD_SendCmd(0x80 | line*0x40 + pos); // move cursor to pos
                    cursor_shift = 0;
                }

                // Put char at current location
                LCD_SendData((uint8_t) page.content[line][pos]);
            } else {
                cursor_shift++;
            }
        }
    }
    LCD_SendCmd(0x80 | 33);
    current_page = page;
}


int convert_hertz_to_ns(int hertz) {
	return 1000000 / hertz;
}

void c_major_scale() {
	TIM1->CCR3 = 10;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(C, 4)) - 1;
	HAL_Delay(1000);
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(D, 4)) - 1;
	HAL_Delay(500);
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(E, 4)) - 1;
	HAL_Delay(500);
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(F, 4)) - 1;
	HAL_Delay(500);
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(G, 4)) - 1;
	HAL_Delay(500);
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(A, 4)) - 1;
	HAL_Delay(500);
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(B, 4)) - 1;
	HAL_Delay(500);
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(C, 5)) - 1;
	HAL_Delay(1000);
	TIM1->CCR3 = 0;
}

void f1_theme_func() {
	int beat = 320;

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(D, 4)) - 1;
	HAL_Delay(beat*3);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(E, 4)) - 1;
	HAL_Delay(beat/2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(F, 4)) - 1;
	HAL_Delay(beat/2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(D, 4)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(C, 4)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(C, 4)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(A, 3)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(B, 3)) - 1;
	HAL_Delay(beat*4);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = 0;
	HAL_Delay(beat*1);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(D, 4)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(E, 4)) - 1;
	HAL_Delay(beat/2);
	TIM1->CCR3 = volume;
	HAL_Delay(10);

	TIM1->ARR = convert_hertz_to_ns((int)FREQ(F, 4)) - 1;
	HAL_Delay(beat/2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(D, 4)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(C, 4)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(C, 4)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(F, 4)) - 1;
	HAL_Delay(beat*2);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = volume;
	TIM1->ARR = convert_hertz_to_ns((int)FREQ(G, 4)) - 1;
	HAL_Delay(beat*4);
	TIM1->CCR3 = 0;
	HAL_Delay(10);

	TIM1->CCR3 = 0;
}

int is_SW4_pressed_debouncing_method2()
{
    int delay = 1;
    int n = 10;
    int count = 4;

    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        HAL_Delay(delay);
        if (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == 0)
        {
            counter = 0;
        }
        else
        {
            counter++;
        }
        if (counter >= count)
        {
            return 1;
        }
    }
    return 0;
}

void load_set_reg_num(int task4_num)
{
    for (int i = 0; i < 16; i++)
    {
        int bit = ((task4_num >> i) & 1);
        HAL_GPIO_WritePin(SR_SER_GPIO_Port, SR_SER_Pin, bit);
        silent_tick_shift_reg();
    }

    HAL_GPIO_WritePin(SR_RCLK_GPIO_Port, SR_RCLK_Pin, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(SR_RCLK_GPIO_Port, SR_RCLK_Pin, 0);
    HAL_Delay(1);
}

void tick_shift_reg()
{
    HAL_GPIO_WritePin(SR_SRCLK_GPIO_Port, SR_SRCLK_Pin, 1);
    HAL_GPIO_WritePin(SR_RCLK_GPIO_Port, SR_RCLK_Pin, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(SR_SRCLK_GPIO_Port, SR_SRCLK_Pin, 0);
    HAL_GPIO_WritePin(SR_RCLK_GPIO_Port, SR_RCLK_Pin, 0);
    HAL_Delay(1);
}

void silent_tick_shift_reg()
{
    HAL_GPIO_WritePin(SR_SRCLK_GPIO_Port, SR_SRCLK_Pin, 1);
    HAL_GPIO_WritePin(SR_RCLK_GPIO_Port, SR_RCLK_Pin, 0);
    HAL_Delay(1);
    HAL_GPIO_WritePin(SR_SRCLK_GPIO_Port, SR_SRCLK_Pin, 0);
    HAL_GPIO_WritePin(SR_RCLK_GPIO_Port, SR_RCLK_Pin, 0);
    HAL_Delay(1);
}
