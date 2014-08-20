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

#define DIGITAL_WRITE_FUNC 0
#define ANALOG_WRITE_FUNC 1

#define MAX_PINS 13

typedef struct event_s event_t;
struct event_s {
    unsigned long time;
    unsigned char write_function;
    unsigned char pin;
    unsigned char level;
    event_t *next;
};

int schedule_event(unsigned long time, unsigned char write_function, 
        unsigned char pin, unsigned char level);

/* returns the number of events executed, or less than zero on error
 */
int execute_events();

int clear_events();

#endif
