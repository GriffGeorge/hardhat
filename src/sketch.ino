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

#define BUTTON 1

#define BUFFER_SIZE 512
#define SAMPLE_SIZE 5

#define FLASH_MODE 0
#define MUSIC_MODE 1
#define DEFAULT_MODE FLASH_MODE

#define LOG

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

buffer_t *buffer = NULL;
int input_type = FILTERED_INPUT;
int i = 0; //used for the for loop
float sample_avg = 0.0;
int index = 0;
unsigned char light_level = 0;
unsigned char reverse_light_level = 0;

volatile int mode = DEFAULT_MODE;

void button_interrupt() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > 200) {
        switch (mode) {
            case FLASH_MODE: mode = MUSIC_MODE; break;
            case MUSIC_MODE: mode = FLASH_MODE; break;
            default: mode = DEFAULT_MODE; break;
        }
        last_interrupt_time = interrupt_time;
#ifdef LOG
        Serial.print("Switch mode to ");
        Serial.println(mode);
#endif
    }
}

void setup()
{

    Serial.begin(9600);
    // Uncomment to have the arduino wait for serial to connect
    
    /*
    while(!Serial) {
        delay(10); //wait for serial port to connect
    }
    */
    
    init_mics(input_type);
    buffer = get_buffer();
    attachInterrupt(BUTTON, button_interrupt, LOW);
}

void loop() {
    switch (mode) {
        case FLASH_MODE: flash_mode(); break;
        case MUSIC_MODE: music_mode(); break;
        default: mode = DEFAULT_MODE; break;
    }
}

void flash_mode() {
    Serial.println("FLASH MODE");
    unsigned long time = millis();

    //1800 ms
    for (int i = 0; i < 3; i++) {
        flash_light_on(eyes, 100, time);
        flash_light_on(eyes, 100, time+200);
        time += 600;
    }

    while (millis() < time) {
        update_lights();
    }

    //1200 ms
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            flash_light_on(gb1, 50, time+100);
            flash_light_on(gb2, 50, time+100);
            flash_light_on(gb3, 50, time+100);
            time += 100;
            while (millis() < time) {
                update_lights();
            }
        }

        for (int j = 0; j < 4; j++) {
            flash_light_on(ra1, 50, time+100);
            flash_light_on(ra2, 50, time+100);
            flash_light_on(ra3, 50, time+100);
            time += 100;
            while (millis() < time) {
                update_lights();
            }
        }
    }

    while (millis() < time) {
        update_lights();
    }

    //1200ms
    for (int i = 0; i < 3; i++) {
        flash_light_on(gb1, 200, time);
        flash_light_on(gb2, 200, time);
        flash_light_on(gb3, 200, time);
        flash_light_on(ra1, 200, time+200);
        flash_light_on(ra2, 200, time+200);
        flash_light_on(ra3, 200, time+200);
        time += 400;
    }

    while (millis() < time) {
        update_lights();
    }

    //800ms
    flash_light_on(gb1, 200, time);
    flash_light_on(gb2, 200, time+100);
    flash_light_on(gb3, 200, time+200);
    flash_light_on(ra3, 200, time+300);
    flash_light_on(ra2, 200, time+400);
    flash_light_on(ra1, 200, time+500);
    flash_light_on(eyes, 200, time+600);
    time += 800;

    while (millis() < time) {
        update_lights();
    }

    //600ms
    light_on(gb1, time);
    light_on(gb2, time+100);
    light_on(gb3, time+200);
    light_on(ra3, time+300);
    light_on(ra2, time+400);
    light_on(ra1, time+500);
    light_on(eyes, time+600);
    time += 600;

    while (millis() < time) {
        update_lights();
    }

    //800ms
    flash_light_off(gb1, 200, time);
    flash_light_off(gb2, 200, time+100);
    flash_light_off(gb3, 200, time+200);
    flash_light_off(ra3, 200, time+300);
    flash_light_off(ra2, 200, time+400);
    flash_light_off(ra1, 200, time+500);
    flash_light_off(eyes, 200, time+600);
    time += 800;

    while (millis() < time) {
        update_lights();
    }

    //600ms
    light_off(gb1, time);
    light_off(gb2, time+100);
    light_off(gb3, time+200);
    light_off(ra3, time+300);
    light_off(ra2, time+400);
    light_off(ra1, time+500);
    light_off(eyes, time+600);
    time += 600;

    while (millis() < time) {
        update_lights();
    }
}

void music_mode()
{
    read_levels(input_type);

#ifdef LOG
    Serial.print("\t");
#endif

    sample_avg = 0.0;
    index = 0;
    for(i = 1; i <= SAMPLE_SIZE ; i++) {
        index = ((buffer->start-i) % 512);
        if (index < 0) {
            sample_avg += 0;
        } else {
            sample_avg += 
                abs(buffer->buffer[index] - 
                        round(buffer->avg));
        }
#ifdef LOG
        /*
            Serial.print((buffer->start-i) % BUFFER_SIZE);
            Serial.print(":");
            Serial.print(abs(buffer->buffer[(buffer->start-i) % BUFFER_SIZE] - 
                    round(buffer->avg)));
            Serial.print(", ");
        */
#endif
    }
    sample_avg /= SAMPLE_SIZE;

    light_level = constrain(map(
            (int)(sample_avg*100),
            (int)(abs(buffer->avg_deflect*100)),
            (int)(abs(buffer->avg_deflect*200)),
            0, 255), MIN_LEVEL, MAX_LEVEL);

    reverse_light_level = map(light_level, 0, 255, 100, 0);
    

    if (light_level < MAX_LEVEL/4) {
        light_level = 0;
        reverse_light_level = 100;
    }
    analogWrite(EYES, light_level);
    analogWrite(GB1, light_level);
    analogWrite(GB2, light_level);
    analogWrite(GB3, light_level);
    analogWrite(RA1, light_level);
    analogWrite(RA2, light_level);
    analogWrite(RA3, light_level);

#ifdef LOG
    Serial.print("\t = ");
    Serial.print(sample_avg);
    Serial.print("\t");
    Serial.print(light_level);
    Serial.print("\t");
    Serial.print(reverse_light_level);

    /*
    for(i = 0; i < light_level / 10; i++) {
        Serial.print("-");
    }
    */
    Serial.println();
#endif
}


