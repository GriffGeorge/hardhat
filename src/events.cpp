/* Events library
 * Griff 2014
 */

#include "events.h"

//#include <stdlib.h>

event_t *events = NULL;
event_t *last_event = NULL;
int events_size = 0;

int schedule_event(unsigned long time, unsigned char write_function, 
        unsigned char pin, unsigned char level)
{
    //log_verbose("Schedule event with time %lu, write_function %d, pin %s, level %d", 
    //        time, write_function, string_from_pin(pin), level);

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
        last_event = new_event;
    }

    //log_event_queue();
    return SUCCESS;
}

int execute_event(const event_t *event) {
    if (event == NULL) {
        return ERR_BAD_PARAM;
    }
    //log_verbose("Execute event %p with time %lu, write_function %d, pin %s, level %d",
    //        event, event->time, event->write_function, 
    //        string_from_pin(event->pin), event->level);
    switch (event->write_function) {
        case DIGITAL_WRITE_FUNC: 
            digitalWrite(event->pin, event->level);
            break;
        case ANALOG_WRITE_FUNC:
            analogWrite(event->pin, event->level);
            break;
        default:
            return ERR_BAD_ENUM;
    }
    return SUCCESS;
}

int execute_events()
{
    //log_verbose("Executing events");
    //log_event_queue(); //log the events (if logging is turned on)

    //three cases: no events, one event, many events
    int events_executed = 0;

    //if no events:
    if (events == NULL) {
        //log_verbose("No events in queue.");
        return events_executed;
    }

    event_t *cursor = events;
    unsigned long current_time = millis();
        
    //execute the first event and delete it, if needed
    while (cursor != NULL && current_time >= cursor->time) {
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
        if (current_time >= cursor->next->time) {
            if (execute_event(cursor->next) == 0) {
                events_executed++;
            }
            event_t *event_to_delete = cursor->next;
            if (last_event == event_to_delete) {
                last_event = cursor;
            }
            cursor->next = cursor->next->next;
            free(event_to_delete);
            //log_event_queue();
            continue;
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
/*
int log_event_queue()
{
    event_t *cursor = events;
    log_verbose("Event Queue: (events->%p, last_event->%p)",
            events, last_event);
    while (cursor != NULL) {
        log_verbose("\tAt %lu set pin %s to %d. Pointers: %p->%p", 
                cursor->time, string_from_pin(cursor->pin), cursor->level,
                cursor, cursor->next);
        cursor = cursor->next;
    }
    return 0;
}
*/
/*
static char* string_from_pin(const char pin) {
    switch (pin) {
    //OUT OF DATE
        case LED_LEFT:      return "LED_LEFT";
        case LED_CENTER:    return "LED_CENTER";
        case LED_RIGHT:     return "LED_RIGHT";
        default: log_error(ERR_BAD_PIN, "Bad pin number: %d", pin); return "BAD_PIN_NUMBER";
    }
}
*/
