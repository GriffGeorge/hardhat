/* Mic library
 * Griff 2014
 *
 * This library allows the analysis of microphone input.
 */

#ifndef MIC_H
#define MIC_H

#include <Arduino.h>

#define BUFFER_SIZE 1024

#define FILTERED_INPUT 0
#define UNFILTERED_INPUT 1

#define FILTERED_INPUT_DEFAULT_AVG 119
#define UNFILTERED_INPUT_DEFAULT_AVG 122

#define MIN_LEVEL 385
#define MAX_LEVEL 639

typedef struct buffer_s buffer_t;
struct buffer_s {
    unsigned char buffer[BUFFER_SIZE];
    int start;
    float avg;
    float avg_deflect;
};

void init_mics(int input_type);
buffer_t *get_buffer();
int read_levels(int input_type);

#endif
