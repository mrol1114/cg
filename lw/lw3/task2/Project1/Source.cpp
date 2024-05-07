#define _USE_MATH_DEFINES

#include "Window.h"

int main(void)
{
    Window mainWindow("Clock", 720, 540);
    mainWindow.MainLoop();

    return 0;
}