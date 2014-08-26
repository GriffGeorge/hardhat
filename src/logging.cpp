/* Logging library
 * Griff 2014
 */

#include "logging.h"
/*
static char* error_string(const int error) {
    switch (error) {
        case SUCCESS:       return "SUCCESS";
        case ERR_BAD_ERR:   return "BAD_ERR";
        case ERR_BAD_PARAM: return "BAD_PARAM";
        case ERR_BAD_ENUM:  return "BAD_ENUM";
        case ERR_BAD_PIN:   return "BAD_PIN";
        case ERR_BAD_WRITE_FUNCTION: return "BAD_WRITE_FUNCTION";
        default: log_error(ERR_BAD_ERR, "Bad error number: %d", error); return "BAD_ERROR";
    }
}
*/
void log_error(const int error, const char *msg_fmt, ...) {
    if (LOG_LEVEL >= LOG_LEVEL_ERROR) {
        va_list args;
        char *msg = (char *)malloc(sizeof(char) * LOG_MSG_LENGTH);
        char *time = (char *)malloc(sizeof(char) * TIME_LENGTH);
        snprintf(time, TIME_LENGTH, "%10lu ", millis());
        va_start(args, msg_fmt);
        vsnprintf(msg, LOG_MSG_LENGTH, msg_fmt, args);
        Serial.print(time);
        Serial.print("[  ERROR] ");
        Serial.print(error);
        Serial.print(": ");
        Serial.println(msg);
        va_end(args);
        free(msg);
        free(time);
    }
}
/*
void log_info(const char *msg_fmt, ...) {
    if (LOG_LEVEL >= LOG_LEVEL_INFO) {
        va_list args;
        char *msg = (char *)malloc(sizeof(char) * LOG_MSG_LENGTH);
        char *time = (char *)malloc(sizeof(char) * TIME_LENGTH);
        snprintf(time, TIME_LENGTH, "%10lu ", millis());
        va_start(args, msg_fmt);
        vsnprintf(msg, LOG_MSG_LENGTH, msg_fmt, args);
        Serial.print(time);
        Serial.print("[   INFO] ");
        Serial.println(msg);
        va_end(args);
        free(msg);
        free(time);
    }
}

void log_debug(const char *msg_fmt, ...) {
    if (LOG_LEVEL >= LOG_LEVEL_DEBUG) {
        va_list args;
        char *msg = (char *)malloc(sizeof(char) * LOG_MSG_LENGTH);
        char *time = (char *)malloc(sizeof(char) * TIME_LENGTH);
        snprintf(time, TIME_LENGTH, "%10lu ", millis());
        va_start(args, msg_fmt);
        vsnprintf(msg, LOG_MSG_LENGTH, msg_fmt, args);
        Serial.print(time);
        Serial.print("[  DEBUG] ");
        Serial.println(msg);
        va_end(args);
        free(msg);
        free(time);
    }
}
*/
void log_verbose(const char *msg_fmt, ...) {
    if (LOG_LEVEL >= LOG_LEVEL_VERBOSE) {
        va_list args;
        char *msg = (char *)malloc(sizeof(char) * LOG_MSG_LENGTH);
        char *time = (char *)malloc(sizeof(char) * TIME_LENGTH);
        snprintf(time, TIME_LENGTH, "%10lu ", millis());
        va_start(args, msg_fmt);
        vsnprintf(msg, LOG_MSG_LENGTH, msg_fmt, args);
        Serial.print(time);
        Serial.println(msg);
        va_end(args);
        free(msg);
        free(time);
    }
}
