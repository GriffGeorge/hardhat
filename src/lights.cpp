/* Lights library
 * Griff 2014
 */

#include "lights.h"


light_t lights[MAX_LIGHTS];
int lights_size = 0;

event_t *events = NULL;
event_t *last_event = NULL;
int events_size = 0;

light_t* new_light(unsigned char pin) {
    if (lights_size >= MAX_LIGHTS) {
        return NULL;
    }

    lights[lights_size].pin = pin;
    lights[lights_size].state = OFF_STATE;
    lights[lights_size].level = 0;

    pinMode(pin, OUTPUT);

    lights_size++;

    return &(lights[lights_size-1]);
}


static int schedule_event(light_t *light, unsigned long start_time, 
        unsigned long end_time, unsigned char to_state)
{
    /*
    Serial.print("Schedule pin ");
    Serial.print(light->pin);
    Serial.print(", start ");
    Serial.print(start_time);
    Serial.print(", end ");
    Serial.print(end_time);
    Serial.print(", to state ");
    Serial.println(to_state);
    */

    //allocate memory for the new event
    event_t *new_event = (event_t *) malloc(sizeof(event_t));

    //set up the new events parameters
    new_event->light = light;
    new_event->start_time = start_time;
    new_event->end_time = end_time;
    new_event->to_state = to_state;
    new_event->next = NULL;

    //add the new event to the list
    if (events == NULL) {
        events = new_event;
        last_event = new_event;
    } else {
        last_event->next = new_event;
        last_event = new_event;
    }

    return 0;
}

static int execute_event(const event_t *event) {
    if (event == NULL) {
        return -1;
    }

    unsigned long current_time = millis();

    if (current_time < event->start_time) {
        return -1;
    }

    if (current_time >= event->end_time) {
        switch (event->to_state) {
            case OFF_STATE:
            case FADING_OFF_STATE:
                digitalWrite(event->light->pin, MIN_LEVEL);
                event->light->state = OFF_STATE;
                break;
            case ON_STATE:
            case FADING_ON_STATE:
                digitalWrite(event->light->pin, MAX_LEVEL);
                event->light->state = ON_STATE;
                break;
            default:
                return -1;
        }
        return 0;
    }

    event->light->state = event->to_state;

    if (event->light->state == FADING_ON_STATE) {
        analogWrite(event->light->pin, 
                constrain(
                    map(current_time, event->start_time, event->end_time, 
                        MIN_LEVEL, MAX_LEVEL), 
                    MIN_LEVEL, MAX_LEVEL));
    } else if (event->light->state == FADING_OFF_STATE) {
        analogWrite(event->light->pin, 
                constrain(
                    map(current_time, event->start_time, event->end_time, 
                        MAX_LEVEL, MIN_LEVEL), 
                    MIN_LEVEL, MAX_LEVEL));
    }
    return 0;
}

int update_lights()
{

    //three cases: no events, one event, many events
    int events_executed = 0;

    //if no events:
    if (events == NULL) {
        return events_executed;
    }

    event_t *cursor = events;
    unsigned long current_time = millis();
        
    //execute the first event and delete it, if needed
    while (cursor != NULL && current_time >= cursor->start_time) {
        if (execute_event(cursor) == 0) {
            events_executed++;
        }
        
        if (cursor->start_time <= current_time 
                && current_time <= cursor->end_time) {
            //avoids an infinite loop
            break;
        } else if (current_time >= cursor->end_time) {
            events = cursor->next;
            free(cursor);
            
            //if the list is empty
            if (events == NULL) {
                last_event = NULL;
                return events_executed;
            }
            cursor = events;
        }

    }

    //execute the rest of the events if the list isn't empty
    while (cursor->next != NULL) {
        if (current_time >= cursor->next->start_time) {
            if (execute_event(cursor->next) == 0) {
                events_executed++;
            }

            if (current_time >= cursor->next->end_time) {
                event_t *event_to_delete = cursor->next;
                if (last_event == event_to_delete) {
                    last_event = cursor;
                }
                cursor->next = cursor->next->next;
                free(event_to_delete);
                continue;
            }
        }
        cursor = cursor->next;
    }


    return events_executed;
}

static int clear_events()
{
    //TODO: if events are partway through, complete them.
    while (events != NULL) {
        event_t *event_to_delete = events;
        events = events->next;
        free(event_to_delete);
    }
    last_event = events;
    events_size = 0;
    return 0;
}

void light_on(light_t *light) {
    light_on(light, millis());
}

void light_on(light_t *light, const unsigned long time) {
    schedule_event(light, time, time, ON_STATE);
}

void light_off(light_t *light) {
    light_off(light, millis());
}
void light_off(light_t *light, const unsigned long time) {
    schedule_event(light, time, time, OFF_STATE);
}

void flash_light_on(light_t *light, const unsigned int duration) {
    flash_light_on(light, duration, millis());
}

void flash_light_on(light_t *light, const unsigned int duration,
        const unsigned long time) {
    light_on(light, time);
    light_off(light, time+duration);
}

void flash_light_off(light_t *light, const unsigned int duration) {
    flash_light_off(light, duration, millis());
}

void flash_light_off(light_t *light, const unsigned int duration,
        const unsigned long time) {
    light_off(light, time);
    light_on(light, time+duration);
}

void fade_light_on(light_t *light, const unsigned int duration) {
    fade_light_on(light, duration, millis());
}

void fade_light_on(light_t *light, const unsigned int duration, 
        unsigned long time) {
    schedule_event(light, time, time+duration, FADING_ON_STATE);
}

void fade_light_off(light_t *light, const unsigned int duration) {
    fade_light_off(light, duration, millis());
}

void fade_light_off(light_t *light, const unsigned int duration,
        unsigned long time) {
    schedule_event(light, time, time+duration, FADING_OFF_STATE);
}
