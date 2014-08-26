/* Lights library
 * Griff 2014
 *
 * This library is a layer of abstraction, allowing control of the lights on the
 * arduino without worrying about how the scheduler is implemented.
 */

#ifndef LIGHTS_H
#define LIGHTS_H

#include "events.h"
#include "logging.h"

#define MIN_LEVEL 0
#define MAX_LEVEL 255

#define MIN_LEVEL_STEP 5

//void light_on(const char light);
void light_on(const char light, const unsigned long time);
//void light_off(const char light);
void light_off(const char light, const unsigned long time);

//void fade_light_on(const char light, const unsigned int duration);
void fade_light_on(const char light, const unsigned int duration, 
        const unsigned long time);
//void fade_light_off(const char light, const unsigned int duration);
void fade_light_off(const char light, const unsigned int duration,
        const unsigned long time);
//void fade_light(const char light, const unsigned int duration,
//        const unsigned char level_start, const unsigned char level_end);
void fade_light(const char light, const unsigned int duration,
        const unsigned char level_start, const unsigned char level_end,
        const unsigned long time);


#endif
