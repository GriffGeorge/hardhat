char foo; //WHY!? This apparently fixes some problems. fml.

/* Real time loop for Mandy's Hard Hat
2014 Mandy and Griff
*/

#include "lights.h"
#include "mic.h"

//if you change pins here, make sure to also change them in
//the string_from_pin() function in logging.c
//3, 5, 6, 9, 10, 11, 13
#define EYES 13
#define GB1 5
#define GB2 10
#define GB3 11
#define RA1 3
#define RA2 6
#define RA3 9

//#define TEST

#ifndef TEST
light_t *eyes = new_light(EYES);
light_t *gb1 = new_light(GB1);
light_t *gb2 = new_light(GB2);
light_t *gb3 = new_light(GB3);
light_t *ra1 = new_light(RA1);
light_t *ra2 = new_light(RA2);
light_t *ra3 = new_light(RA3);
#endif

#ifdef TEST
light_t *one = new_light(3);
light_t *two = new_light(5);
light_t *three = new_light(6);
light_t *four = new_light(9);
#endif

void setup()
{

    Serial.begin(9600);
    // Uncomment to have the arduino wait for serial to connect
    /*
    while(!Serial) {
        delay(10); //wait for serial port to connect
    }
    */

    //init_mics();
    test_events();
}

void loop()
{
    Serial.println("D");
    delay(6000);
}


void test_events() {
    Serial.println("BEGIN TEST");
    test_1();
    test_2();
    Serial.println("END TEST");
}

#ifndef TEST
void test_1() {
    Serial.println("TEST 1");
    update_lights();
    unsigned long time = millis();
    light_on(eyes, time);
    light_off(eyes, time+500);
    light_on(gb1, time+500);
    light_off(gb1, time+1000);
    light_on(gb2, time+1000);
    light_off(gb2, time+1500);
    light_on(gb3, time+1500);
    light_off(gb3, time+2000);
    light_on(ra1, time+2000);
    light_off(ra1, time+2500);
    light_on(ra2, time+2500);
    light_off(ra2, time+3000);
    light_on(ra3, time+3000);
    light_off(ra3, time+3500);
    while (millis() < time+4000) {
        update_lights();
    }
}

void test_2() {
    Serial.println("TEST 2");
    update_lights();
    unsigned long time = millis();
    fade_light_on(eyes, 1000, time);
    fade_light_off(eyes, 1000, time+500);
    fade_light_on(gb1, 1000, time+500);
    fade_light_off(gb1, 1000, time+1000);
    fade_light_on(gb2, 1000, time+1000);
    fade_light_off(gb2, 1000, time+1500);
    fade_light_on(gb3, 1000, time+1500);
    fade_light_off(gb3, 1000, time+2000);
    fade_light_on(ra1, 1000, time+2000);
    fade_light_off(ra1, 1000, time+2500);
    fade_light_on(ra2, 1000, time+2500);
    fade_light_off(ra2, 1000, time+3000);
    fade_light_on(ra3, 1000, time+3000);
    fade_light_off(ra3, 1000, time+3500);
    while (millis() < time+5000) {
        update_lights();
    }
}
#endif

#ifdef TEST
void test_1() {
    Serial.println("TEST 1");
    update_lights();
    unsigned long time = millis();
    light_off(one, time+250);
    light_on(two, time+250);
    light_off(two, time+500);
    light_on(three, time+500);
    light_off(three, time+750);
    light_on(four, time+750);
    light_off(four, time+1000);
    light_on(one, time);
    while(millis() < time+1500) {
        update_lights();
    }
}

void test_2() {
    Serial.println("TEST 2");
    update_lights();
    unsigned long time = millis();
    fade_light_on(two, 500, time+250);
    fade_light_on(three, 500, time+500);
    fade_light_on(four, 500, time+750);

    fade_light_off(one, 500, time+500);
    fade_light_off(two, 500, time+750);
    fade_light_off(three, 500, time+1000);
    fade_light_off(four, 500, time+1250);
    fade_light_on(one, 500, time);

    while(millis() < time+2000) {
        update_lights();
    }
}
#endif
