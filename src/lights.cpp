/* Lights library
 * Griff 2014
 */

#include "lights.h"

void light_on(const char light) {
    light_on(light, millis());
}

void light_on(const char light, const unsigned long time) {
    schedule_event(time, DIGITAL_WRITE_FUNC, light, HIGH);
}

void light_off(const char light) {
    light_off(light, millis());
}
void light_off(const char light, const unsigned long time) {
    schedule_event(time, DIGITAL_WRITE_FUNC, light, LOW);
}

void fade_light_on(const char light, const unsigned int duration) {
    fade_light_on(light, duration, millis());
}

void fade_light_on(const char light, const unsigned int duration, 
        unsigned long time) {
    fade_light(light, duration, MIN_LEVEL, MAX_LEVEL, time);
}

void fade_light_off(const char light, const unsigned int duration) {
    fade_light_off(light, duration, millis());
}

void fade_light_off(const char light, const unsigned int duration,
        unsigned long time) {
    fade_light(light, duration, MAX_LEVEL, MIN_LEVEL, time);
}

void fade_light(const char light, const unsigned int duration,
        const unsigned char level_start, const unsigned char level_end) {
    fade_light(light, duration, level_start, level_end, millis());
}

void fade_light(const char light, const unsigned int duration,
        const unsigned char level_start, const unsigned char level_end,
        unsigned long time) {
    Serial.println("3");
    //bad parameters
    if (duration < 0) {
        log_error(ERR_BAD_PARAM, "Duration may not be less than zero: %d", 
                duration);
    }

    Serial.println("4");
    //take care of divide by zero errors. 
    if (level_end == level_start) {
        return;
    }
    if (duration == 0) {
        schedule_event(time, ANALOG_WRITE_FUNC, light, level_end);
        return;
    }
    Serial.println("5");
    
    //calculate rate of change.
    long level_change = (level_end - level_start);
    unsigned long level_step = MIN_LEVEL_STEP;
    if (level_change < 0) {
        level_step *= -1;
    }
    unsigned long time_step = duration/(level_change / level_step);
    Serial.println("6");

    //schedule the fade
    unsigned char level = level_start;
    for (time; time < time+duration; time += time_step) {
        if ((level_change > 0 && level > level_end) ||
                (level_change < 0 && level < level_end)) {
            level = level_end;
        }

        schedule_event(time, ANALOG_WRITE_FUNC, light, level);
        time += time_step;
        level += level_step;
    }
}
