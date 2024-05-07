#define _USE_MATH_DEFINES

#include "Window.h"
#include "Line.h"
#include "memory"

int main(void)
{
    glewInit();
    if (!GLEW_ARB_shader_objects)
    {
        return -1;
    }

    Window mainWindow("Syn", 720, 540);
    ShaderProgram sp;
    mainWindow.AddDrawable(std::make_shared<Line>());
    mainWindow.Run();

    return 0;
}