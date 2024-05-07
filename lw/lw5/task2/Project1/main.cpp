#define _USE_MATH_DEFINES

#include "Window.h"
#include "memory"

int main(void)
{
    Window mainWindow("Cube 3d", 720, 540);
    mainWindow.Run();

    return 0;
}