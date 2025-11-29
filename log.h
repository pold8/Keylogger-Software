#ifndef LOG_H
#define LOG_H

void InitializeLog(void);

void WriteToLog(const char *text_to_log);

void CloseLog(void);

#endif