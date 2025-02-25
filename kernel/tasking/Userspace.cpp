#include <libsystem/Logger.h>
#include <libsystem/io/Stream.h>
#include <libsystem/process/Launchpad.h>
#include <libsystem/process/Process.h>

#include "kernel/tasking/Userspace.h"

void userspace_initialize()
{
    logger_info("Starting the userspace...");

    Launchpad *init_lauchpad = launchpad_create("init", "/System/Binaries/init");

    Stream *keyboard_device = stream_open("/Devices/keyboard", OPEN_READ);
    Stream *serial_device = stream_open("/Devices/serial", OPEN_WRITE);

    launchpad_handle(init_lauchpad, HANDLE(keyboard_device), 0);
    launchpad_handle(init_lauchpad, HANDLE(serial_device), 1);
    launchpad_handle(init_lauchpad, HANDLE(serial_device), 2);
    launchpad_handle(init_lauchpad, HANDLE(serial_device), 3);

    int init_process = -1;
    Result result = launchpad_launch(init_lauchpad, &init_process);

    stream_close(keyboard_device);
    stream_close(serial_device);

    if (result != SUCCESS)
    {
        logger_fatal("Failled to start init : %s", result_to_string(result));
    }

    int init_exit_value = 0;
    process_wait(init_process, &init_exit_value);

    logger_fatal("Init has return with code %d!", init_exit_value);
}
