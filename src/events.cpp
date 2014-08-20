/* Events library
 * Griff 2014
 */

#include "events.h"

#include <stdlib.h>
#include <stdarg.h>

event_t *events = NULL;
event_t *last_event = NULL;
int events_size = 0;

int schedule_event(unsigned long time, unsigned char write_function, 
        unsigned char pin, unsigned char level)
{
    log_debug("Schedule event with time %d, write_function %d, pin %d, level %d", 
            time, write_function, pin, level);

    //check for valid parameters
    if (time < 0) {
        log_error(ERR_BAD_PARAM, "time was less than 0");
        return ERR_BAD_PARAM;
    }

    if (write_function != DIGITAL_WRITE_FUNC 
            && write_function != ANALOG_WRITE_FUNC) {
        log_error(ERR_BAD_PARAM, "write_function was not an accepted value");
        return ERR_BAD_PARAM;
    }

    if (pin < 0 || pin > MAX_PINS) {
        log_error(ERR_BAD_PARAM, "pin was a bad value");
        return ERR_BAD_PARAM;
    }

    //allocate memory for the new event
    event_t *new_event = (event_t *) malloc(sizeof(event_t));

    //set up the new events parameters
    new_event->time = time;
    new_event->write_function = write_function;
    new_event->pin = pin;
    new_event->level = level;
    new_event->next = NULL;

    //add the new event to the list
    if (events == NULL) {
        events = new_event;
        last_event = new_event;
    } else {
        last_event->next = new_event;
    }

    return SUCCESS;
}

int execute_event(const event_t *event) {
    if (event == NULL) {
        return ERR_BAD_PARAM;
    }
    log_debug("Execute event with time %d, write_function %d, pin %d, level %d",
            event->time, event->write_function, event->pin, event->level);
    switch (event->write_function) {
        case DIGITAL_WRITE_FUNC: 
            digitalWrite(event->pin, event->level);
            break;
        case ANALOG_WRITE_FUNC:
            analogWrite(event->pin, event->level);
            break;
        default:
            log_error(ERR_BAD_ENUM, 
                    "write_function was not an acceptable value");
            return ERR_BAD_ENUM;
            break;
    }
    return SUCCESS;
}

int execute_events()
{
    log_debug("Executing events");
    //three cases: no events, one event, many events
    int events_executed = 0;

    //if no events:
    if (events == NULL) {
        log_debug("No events in queue.");
        return events_executed;
    }

    event_t *cursor = events;
    unsigned long current_time = millis();
        
    //execute the first event and delete it, if needed
    while (cursor != NULL && current_time <= cursor->time) {
        if (execute_event(cursor) == 0) {
            events_executed++;
        }
        
        events = cursor->next;
        free(cursor);
        
        //if the list is empty
        if (events == NULL) {
            last_event = NULL;
            return events_executed;
        }

        cursor = events;
    }

    //execute the rest of the events
    while (cursor->next != NULL) {
        if (current_time <= cursor->next->time) {
            if (execute_event(cursor->next) == 0) {
                events_executed++;
            }
            event_t *event_to_delete = cursor->next;
            if (last_event == event_to_delete) {
                last_event = cursor;
            }
            cursor->next = cursor->next->next;
            free(event_to_delete);
        }
        cursor = cursor->next;
    }

    return events_executed;
}

int clear_events()
{
    while (events != NULL) {
        event_t *event_to_delete = events;
        events = events->next;
        free(event_to_delete);
    }
    last_event = events;
    events_size = 0;
    return SUCCESS;
}
