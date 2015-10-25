#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32

#include <windows.h>

#else //_WIN32 -> OS X, LINUX

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#endif //_WIN32

static bool shouldContinue = true;

void signal_stop_processing(){
    printf("quitting...\n\n");
    shouldContinue = false;
}

#ifdef _WIN32

bool CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        signal_stop_processing();
        return(TRUE);
    default:
        return FALSE;
    }
}

#else //_WIN32 -> OSX, LINUX

static void signal_handler(int s) {
    signal_stop_processing();
}

#endif //_WIN32

static void set_key_handler()
{
#ifdef _WIN32
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);

#else //_WIN32 -> OS X, LINUX

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = &signal_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

#endif //_WIN32
}

#endif /* KEY_HANDLER_H */
