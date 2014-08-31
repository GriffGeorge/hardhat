/* Mic library
 * Griff 2014
 */

#include "mic.h"

buffer_t f_buffer;
//buffer_t u_buffer;

void init_mics() {
    f_buffer.start = 0;
    //u_buffer.start = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        f_buffer.buffer[i] = 0;
 //       u_buffer.buffer[i] = 0;
    }
}

buffer_t *get_filtered_buffer() {
    return &f_buffer;
}
/*
buffer_t *get_unfiltered_buffer() {
    return &u_buffer;
}
*/
int read_levels() {
    f_buffer.buffer[f_buffer.start] = analogRead(FILTERED_INPUT);
 //   u_buffer.buffer[u_buffer.start] = analogRead(UNFILTERED_INPUT);
    f_buffer.start++;
  //  u_buffer.start++;
}
