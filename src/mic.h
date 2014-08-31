/* Mic library
 * Griff 2014
 *
 * This library allows the analysis of microphone input.
 */

#ifndef MIC_H
#define MIC_H

#include "logging.h"

#define BUFFER_SIZE 1024

#define FILTERED_INPUT 0
#define UNFILTERED_INPUT 1

typedef struct buffer_s buffer_t;
struct buffer_s {
    int buffer[BUFFER_SIZE];
    int start;
};

void init_mics();
buffer_t *get_filtered_buffer();
//buffer_t *get_unfiltered_buffer();
int read_levels();

#endif
