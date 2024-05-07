#define _USE_MATH_DEFINES

#include "Window.h"
#include "CoordinateGrid.h"
#include "SnubDodecahedron.h"
#include "memory"

int main(void)
{
    Window mainWindow("Snub 3d", 720, 540);
    mainWindow.AddDrawable(std::make_shared<CoordinateGrid>(1, 0.1));
    mainWindow.AddDrawable(std::make_shared<SnubDodecahedron>());
    mainWindow.Run();

    return 0;
}