#include <math.h>
#include <GLFW/glfw3.h>

#include "Window.h"

int main(void)
{
    Window window("Bezier curve", 720, 540);
    window.Run();

    return 0;
}