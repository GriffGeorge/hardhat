/* Logging library
 * Griff 2014
 *
 * This library enables logging to Serial at three levels: error, info, debug.
 *
 */

#ifndef LOGGING_H
#define LOGGING_H

#include <Arduino.h>

#define LOG_LEVEL_ERROR   0
#define LOG_LEVEL_INFO    1
#define LOG_LEVEL_DEBUG   2
#define LOG_LEVEL_VERBOSE 3
#define LOG_LEVEL LOG_LEVEL_VERBOSE

#define LOG_MSG_LENGTH 1024
#define TIME_LENGTH 12

// if you add errors here, add them also to the error_string() function in logging.c
#define SUCCESS                  0
#define ERR_BAD_ERR             -100
#define ERR_BAD_PARAM           -101
#define ERR_BAD_ENUM            -102
#define ERR_BAD_PIN             -103
#define ERR_BAD_WRITE_FUNCTION  -104
#define ERR_TOO_MANY_LIGHTS     -105
#define ERR_INVALID_STATE       -106
#define ERR_NOT_YET             -107
#define ERR_UNEXPECTED          -108

//static char* error_string(const int error);
void log_error(const int error, const char *msg_fmt, ...);
//void log_info(const char *msg_fmt, ...);
//void log_debug(const char *msg_fmt, ...);
void log_verbose(const char *msg_fmt, ...);

#endif
