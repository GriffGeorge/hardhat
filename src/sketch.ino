char foo; //WHY!? This apparently fixes some problems. fml.

/* Real time loop for Mandy's Hard Hat
2014 Mandy and Griff
*/

#include <stdlib.h>
#include "events.h"


void setup()
{
    Serial.begin(9600);
    while(!Serial) {
        delay(10); //wait for serial port to connect
    }

    test_events();
}

void loop()
{
    Serial.println("Delay 3 seconds");
    Serial.println("Holy shit!");
    delay(3000);
}


void test_events() {
    unsigned long time; // will be used multiple times to store time values

    Serial.println("\n\n\n-------------------------------------");
    Serial.println("Three blinks to start test.");
    digitalWrite(10, HIGH);
    delay(500);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(11, LOW);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);

    Serial.println("Execute empty events queue every 10ms for 30 times");
    for (int i = 0; i < 30; i++) {
        execute_events();
        delay(30);
    }

    time = millis() + 1000;
    Serial.println("Schedule 10 HIGH in one second.");
    schedule_event(time, DIGITAL_WRITE_FUNC, 10, HIGH);
    int ret = 0;
    while ((ret = execute_events()) == 0) {
        ;
    }
    Serial.print(ret); Serial.println(" event(s) executed");

    Serial.println("Three blinks to end test.");
    digitalWrite(10, HIGH);
    delay(500);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(11, LOW);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    Serial.println("Test Over");
}
