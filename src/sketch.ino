char foo; //WHY!? This apparently fixes some problems. fml.

/* Real time loop for Mandy's Hard Hat
2014 Mandy and Griff
*/

#include "lights.h"

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

const light_t *eyes = new_light(EYES);
const light_t *gb1 = new_light(GB1);
const light_t *gb2 = new_light(GB2);
const light_t *gb3 = new_light(GB3);
const light_t *ra1 = new_light(RA1);
const light_t *ra2 = new_light(RA2);
const light_t *ra3 = new_light(RA3);

void setup()
{

    Serial.begin(9600);
    // Uncomment to have the arduino wait for serial to connect
    ///*
    while(!Serial) {
        delay(10); //wait for serial port to connect
    }
    //*/

    test_events();
}

void loop()
{
    Serial.println("D");
    delay(6000);
}


void test_events() {
    Serial.println("BEGIN TEST");
    //test_1();
    //test_2();
    //test_3();
    test_4();
    Serial.println("END TEST");
}

/*
void test_1() {
    Serial.println("-- TEST #1 ------------------------------------");
    Serial.println("Execute empty events queue every 10ms for 30 times");
    for (int i = 0; i < 30; i++) {
        execute_events();
        delay(30);
    }
}

void test_2() {
    Serial.println("-- TEST #2 ------------------------------------");
    Serial.println("Turn on left, center, then right, then turn all off at once.");
    unsigned long time = millis() + 1000;
    light_on(LED_CENTER, time+333);
    light_on(LED_RIGHT, time+666);
    light_off(LED_CENTER, time+1000);
    light_off(LED_LEFT, time+1000);
    light_off(LED_RIGHT, time+1000);
    light_on(LED_LEFT, time);

    Serial.println("Execute empty events queue every 10ms for 30 times");
    while (millis() < time+2000) {
        execute_events();
        delay(10);
    }
}
*/
/*
void test_3() {
    Serial.println("TEST #3");
    unsigned long time = millis();
    for (int i = 0; i < 1; i++) {
        Serial.println("1");
        execute_events();
        Serial.println("2");
        fade_light_on(LED_LEFT, 500, time);
        fade_light_on(LED_CENTER, 500, time+333);
        fade_light_on(LED_RIGHT, 500, time+666);
        fade_light_off(LED_LEFT, 500, time+500);
        fade_light_off(LED_CENTER, 500, time+833);
        fade_light_off(LED_RIGHT, 500, time+1166);
        Serial.println("4");
        time += 1000;
    }
    while (millis() < time+1000) {
        execute_events();
    }
}
*/

void test_4() {
    Serial.println("TEST 4");
    unsigned long time;
    while (true) {
        time = millis();
        light_on(
        while (millis() < time+800) {
            execute_events();
        }
    }

}
