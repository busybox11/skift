#pragma once

#include <abi/Process.h>

#include <libsystem/Common.h>
#include <libsystem/Result.h>

int process_this();

Result process_run(const char *command, int *pid);

void __no_return process_exit(int code);

Result process_cancel(int pid);

Result process_get_directory(char *buffer, size_t size);

Result process_set_directory(const char *directory);

int process_sleep(int time);

int process_wait(int pid, int *exit_value);
