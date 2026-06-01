#pragma once

#include <sys/types.h>

extern pid_t foreground_pid;

void sigint_handler(int signo);
void sigtstp_handler(int signo);
void handle_eof();
void setup_signal_handlers();