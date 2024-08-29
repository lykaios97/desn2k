/*
 * coast.h
 *
 *  Created on: Jul 27, 2024
 *      Author: aditya
 */

#ifndef INC_COAST_H_
#define INC_COAST_H_

/*
 * coast.h
 *
 *  Created on: Jun 4, 2024
 *      Author: kavishachandraratne
 */

#include <stdint.h>
#include "stm32f3xx_hal.h"
#include <stdbool.h>
#include <string.h>

void coast_gpio_init();
void coast_loop_body();
void coast_start();
void coast_handle_interrupt(uint16_t GPIO_Pin);

void display_initial_message();

void initialise_memory_views();

void add_new_preset();

void configure_preset();

typedef uint32_t Time;
typedef int View;

typedef struct
{
    int freq;
    float beats;
    uint16_t lights;
} AV;

typedef struct {
	char name[17];
    Time duration;
    Time time;
    bool active;
    bool completed;
    int av_length;
    AV *av_array;
    uint16_t shift_reg_value;

} Function;

typedef struct {
    char content[2][16];
} Page;

typedef struct {
	char name[17];
    Function functions[8]; // Array of 8 Function objects
    View current_view;
	int tim_max;
} Memory;

typedef struct {
	size_t len;
	Memory array[8];
} Presets;

#define CLCK_VIEW 0
#define ALRM_VIEW 1
#define STOP_VIEW 2
#define TIMR_VIEW 3
#define TIMA_VIEW 4
#define TIMB_VIEW 5
#define TIMC_VIEW 6
#define TIMD_VIEW 7

// Define base frequencies for each note in octave 0
#define BASE_FREQ_C 16.35
#define BASE_FREQ_Cs 17.32
#define BASE_FREQ_D 18.35
#define BASE_FREQ_Ds 19.45
#define BASE_FREQ_E 20.60
#define BASE_FREQ_F 21.83
#define BASE_FREQ_Fs 23.12
#define BASE_FREQ_G 24.50
#define BASE_FREQ_Gs 25.96
#define BASE_FREQ_A 27.50
#define BASE_FREQ_As 29.14
#define BASE_FREQ_B 30.87

// Macro to calculate the frequency for a given note and octave
#define FREQ(note, octave) (BASE_FREQ_##note * (1 << (octave)))

#endif /* INC_COAST_H_ */
