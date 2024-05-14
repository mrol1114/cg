#define _USE_MATH_DEFINES

#include <memory>
#include <vector>
#include <stdexcept>

#include "Square.h"
#include "Window.h"

int main(void)
{
    std::string fragmentShader = R"(
#version 450 core

layout(location = 0) uniform vec2 u_resolution;

void main()
{
    vec2 pixelCoord = gl_FragCoord.xy / u_resolution.xy;
    float dis = distance(pixelCoord, vec2(0.5));
    float isInCircle = step(0.15, dis);

    vec3 color = isInCircle == 1.0 
        ? vec3(1.0) 
        : vec3(1.0, 0.0, 0.0);

    gl_FragColor = vec4(color, 1.0);
}
    )";

    if (!glfwInit())
        throw std::runtime_error("glfw is not initialized");

    GLFWwindow* glfwWindow = glfwCreateWindow(540, 540, "Circle", NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        throw std::runtime_error("could not create window");
    }

    glfwMakeContextCurrent(glfwWindow);

    glewInit();
    if (!GLEW_ARB_shader_objects)
    {
        throw std::runtime_error("glew is not initialized");
    }

    Window window(glfwWindow);
    window.AddDrawable(std::make_shared<Square>());
    window.AddShader(std::make_shared<Shader>(GL_FRAGMENT_SHADER, fragmentShader.c_str()));
    window.Run();

    return 0;
}