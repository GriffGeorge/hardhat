/* Mic library
 * Griff 2014
 */

#include "mic.h"

#define LOG

static buffer_t buffer;

void init_mics(int input_type) {
    buffer.start = 0;
    switch (input_type) {
        case FILTERED_INPUT: buffer.avg = FILTERED_INPUT_DEFAULT_AVG; break;
        case UNFILTERED_INPUT_DEFAULT_AVG: buffer.avg = UNFILTERED_INPUT_DEFAULT_AVG; break;
    }
    buffer.avg_deflect = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        switch (input_type) {
            case FILTERED_INPUT: buffer.buffer[i] = FILTERED_INPUT_DEFAULT_AVG; break;
            case UNFILTERED_INPUT_DEFAULT_AVG: buffer.buffer[i] = UNFILTERED_INPUT_DEFAULT_AVG; break;
            default: buffer.buffer[i] = 0; break;
        }
    }
}

buffer_t *get_buffer() {
    return &buffer;
}

int read_levels(int input_type) {
#ifdef LOG
    Serial.print(buffer.start);
    Serial.print("\t: ");
#endif

    //remove old data from the averages
    buffer.avg_deflect *= ((float)BUFFER_SIZE);
    buffer.avg_deflect -= abs(((float)buffer.buffer[buffer.start])-buffer.avg);
    buffer.avg *= ((float)BUFFER_SIZE);
    buffer.avg -= buffer.buffer[buffer.start];

#ifdef LOG
    Serial.print(buffer.buffer[buffer.start]);
    Serial.print(" -> ");
#endif

    //read into the buffer
    buffer.buffer[buffer.start] = (unsigned char)(constrain(
                analogRead(input_type), MIN_LEVEL, MAX_LEVEL) - MIN_LEVEL);

    //correct the averages
    buffer.avg += ((float)buffer.buffer[buffer.start]);
    buffer.avg /= ((float)BUFFER_SIZE);
    buffer.avg_deflect += abs(((float)buffer.buffer[buffer.start])-buffer.avg);
    buffer.avg_deflect /= ((float)BUFFER_SIZE);

#ifdef LOG
    Serial.print(buffer.buffer[buffer.start]);
    Serial.print("\t");
    Serial.print(buffer.avg);
    Serial.print(" | ");
    Serial.print(round(buffer.avg));
    Serial.print("\t");
    Serial.print(buffer.avg_deflect);
#endif

    buffer.start = (buffer.start + 1) % BUFFER_SIZE;
}
