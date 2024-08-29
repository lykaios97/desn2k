/*
 * state.c
 *
 *  Created on: Aug 1, 2024
 *      Author: aditya
 */

#include <main.h>

// All User Interface states
typedef enum {
	STATE_STD_CLK,
	STATE_STD_ALM,
	STATE_STD_CTD,
	STATE_STD_STP,
	STATE_SCI_T1,
	STATE_SCI_T2,
	STATE_SCI_T3,
	STATE_SCI_T4,
	STATE_EDIT
} State;

// Events
typedef enum {
	EVENT_MODE,
	EVENT_FUNC,
	EVENT_SET,
	EVENT_RESET,
} Event;


typedef struct {
	State fromState;
	Event event;
    State nextState;
//    void (*action)(void);  // pointer to function to execute during the transition
} Transition;

volatile State current_state = STATE_STD_CLK;
volatile State previous_state = STATE_STD_CLK;

// Transition table
const Transition transitions[] = {
	// cycle through standard clock
	{STATE_STD_CLK, EVENT_FUNC, STATE_STD_ALM},
	{STATE_STD_ALM, EVENT_FUNC, STATE_STD_STP},
	{STATE_STD_STP, EVENT_FUNC, STATE_STD_CTD},
	{STATE_STD_CTD, EVENT_FUNC, STATE_STD_CLK},
	// cycle through scientific timers
	{STATE_SCI_T1, EVENT_FUNC, STATE_SCI_T2},
	{STATE_SCI_T2, EVENT_FUNC, STATE_SCI_T3},
	{STATE_SCI_T3, EVENT_FUNC, STATE_SCI_T4},
	{STATE_SCI_T4, EVENT_FUNC, STATE_SCI_T1},
	// switch modes
	{STATE_STD_CLK, EVENT_MODE, STATE_SCI_T1},
	{STATE_STD_ALM, EVENT_MODE, STATE_SCI_T1},
	{STATE_STD_STP, EVENT_MODE, STATE_SCI_T1},
	{STATE_STD_CTD, EVENT_MODE, STATE_SCI_T1},
	{STATE_SCI_T1, EVENT_MODE, STATE_STD_CLK},
	{STATE_SCI_T2, EVENT_MODE, STATE_STD_CLK},
	{STATE_SCI_T3, EVENT_MODE, STATE_STD_CLK},
	{STATE_SCI_T4, EVENT_MODE, STATE_STD_CLK},
	// enter edit mode
	{STATE_STD_CLK, EVENT_SET, STATE_EDIT},
	{STATE_STD_ALM, EVENT_SET, STATE_EDIT},
	// {STATE_STD_STP, EVENT_SET, STATE_EDIT}, // not allowed TODO: delete this line
	{STATE_STD_CTD, EVENT_SET, STATE_EDIT},
	{STATE_SCI_T1, EVENT_SET, STATE_EDIT},
	{STATE_SCI_T2, EVENT_SET, STATE_EDIT},
	{STATE_SCI_T3, EVENT_SET, STATE_EDIT},
	{STATE_SCI_T4, EVENT_SET, STATE_EDIT},
	// return from edit mode to previous state
	// {STATE_EDIT, EVENT_RESET, previous_state},
	// {STATE_EDIT, EVENT_SET, previous_state}
};


void handleEvent(Event event) {
	 for (int i = 0; i < sizeof(transitions) / sizeof(Transition); i++) {
		 if (transitions[i].fromState == current_state && transitions[i].event == event) {
			 if (current_state == STATE_EDIT && event == EVENT_RESET) {
				 current_state = previous_state;
			 } else if (current_state == STATE_EDIT && event == EVENT_SET) {
                // TODO: Code to save the edit goes here
                // move from value in edit buffer slot in memory array
				// memory[current_state] = edit_buffer;
                current_state = previous_state;
            } else {
				 previous_state = current_state;
				 current_state = transitions[i].nextState;
			 }
			 // Run action here if needed in future.
		 }
	 }
}
