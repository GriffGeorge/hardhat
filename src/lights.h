/* Lights library
 * Griff 2014
 *
 * This library is a layer of abstraction, allowing control of the lights on the
 * arduino without worrying about how the scheduler is implemented.
 */

#ifndef LIGHTS_H
#define LIGHTS_H

#include "logging.h"

#define MIN_LEVEL 0
#define MAX_LEVEL 255

#define MIN_LEVEL_STEP 5

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
};

typedef struct event_s event_t;
struct event_s {
    light_t *light;
    unsigned long start_time;
    unsigned long end_time;
    unsigned char to_state;
    event_t *next;
};

light_t* new_light(unsigned char pin);

int update_lights();
void light_on(light_t *light);
void light_on(light_t *light, const unsigned long time);
void light_off(light_t *light);
void light_off(light_t *light, const unsigned long time);

void fade_light_on(light_t *light, const unsigned int duration);
void fade_light_on(light_t *light, const unsigned int duration, 
        const unsigned long time);
void fade_light_off(light_t *light, const unsigned int duration);
void fade_light_off(light_t *light, const unsigned int duration,
        const unsigned long time);

//private! Don't use these.
static int schedule_event(light_t *light, unsigned long start_time, 
        unsigned long end_time, unsigned char to_state);
static int clear_events();
//static int log_event_queue();
//static char* string_from_pin(const char pin);

#endif
