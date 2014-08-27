/* Events library
 * Griff 2014
 *
 * This library enables the execution of either digitalWrite or analogWrite at 
 * an arbitrary time in the future.
 *
 */

#ifndef EVENTS_H
#define EVENTS_H

#include "logging.h"

//if you change pins here, make sure to also change them in
//the string_from_pin() function in logging.c
//3, 5, 6, 9, 10, 11, 13
#define EYES 3
#define GB1 5
#define GB2 6
#define GB3 9
#define RA1 10
#define RA2 11
#define RA3 13

#define MAX_LIGHTS 7
#define MAX_PINS 13

#define OFF_STATE           20
#define ON_STATE            21
#define FADING_OFF_STATE    22
#define FADING_ON_STATE     23


typedef struct light_s light_t;
struct light_s {
    unsigned char pin;
    unsigned char state;
    unsigned char level;
}

typedef struct event_s event_t;
struct event_s {
    light_t *light;
    unsigned long start_time;
    unsigned long end_time;
    unsigned char to_state;
    event_t *next;
};


light_t* new_light(unsigned char pin);
static int schedule_event(light_t *light, unsigned long start_time, 
        unsigned long end_time, unsigned char to_state);

/* returns the number of events executed, or less than zero on error
 */
static int execute_events();
static int clear_events();
static int log_event_queue();
static char* string_from_pin(const char pin);

#endif
