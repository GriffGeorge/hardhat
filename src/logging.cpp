/* Logging library
 * Griff 2014
 */

#include "logging.h"

static char* error_string(const int error) {
    switch (error) {
        case SUCCESS:       return "SUCCESS";
        case ERR_BAD_PARAM: return "BAD_PARAM";
        case ERR_BAD_ENUM:  return "BAD_ENUM";
        default: return "BAD_ERROR";
    }
}

void log_error(const int error, const char *msg_fmt, ...) {
    if (LOG_LEVEL >= LOG_LEVEL_ERROR) {
        va_list args;
        char *msg = (char *)malloc(sizeof(char) * LOG_MSG_LENGTH);
        va_start(args, msg_fmt);
        vsnprintf(msg, LOG_MSG_LENGTH, msg_fmt, args);
        Serial.print("[ERROR] ");
        Serial.print(error_string(error));
        Serial.print(": ");
        Serial.println(msg);
        va_end(args);
        free(msg);
    }
}

void log_info(const char *msg_fmt, ...) {
    if (LOG_LEVEL >= LOG_LEVEL_INFO) {
        va_list args;
        char *msg = (char *)malloc(sizeof(char) * LOG_MSG_LENGTH);
        va_start(args, msg_fmt);
        vsnprintf(msg, LOG_MSG_LENGTH, msg_fmt, args);
        Serial.print("[ INFO] ");
        Serial.println(msg);
        va_end(args);
        free(msg);
    }
}

void log_debug(const char *msg_fmt, ...) {
    if (LOG_LEVEL >= LOG_LEVEL_DEBUG) {
        va_list args;
        char *msg = (char *)malloc(sizeof(char) * LOG_MSG_LENGTH);
        va_start(args, msg_fmt);
        vsnprintf(msg, LOG_MSG_LENGTH, msg_fmt, args);
        Serial.print("[ DEBUG] ");
        Serial.println(msg);
        va_end(args);
        free(msg);
    }
}
