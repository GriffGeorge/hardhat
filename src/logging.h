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
#define LOG_LEVEL LOG_LEVEL_DEBUG

#define LOG_MSG_LENGTH 1024

// if you add errors here, add them also to the error_string() function in logging.c
#define SUCCESS 0
#define ERR_BAD_PARAM -101
#define ERR_BAD_ENUM -102

void log_error(const int error, const char *msg_fmt, ...);
void log_info(const char *msg_fmt, ...);
void log_debug(const char *msg_fmt, ...);

#endif
