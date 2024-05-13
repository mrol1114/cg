#define _USE_MATH_DEFINES

#include <memory>

#include "Window.h"
#include "Line.h"

int main(void)
{
    std::string vertexShaderCircle = R"(
#version 450 core

layout (location=0) in vec4 position;
layout (location=16) uniform mat4 u_matrix;

void main()
{
    float r = 0.5;
    float x = r * cos(position.x);
    float y = r * sin(position.x);
    gl_Position = u_matrix * vec4(x, y, 0, 1);
}
    )";

    if (!glfwInit())
        throw std::runtime_error("glfw is not initialized");

    GLFWwindow* glfwWindow = glfwCreateWindow(720, 540, "Circle", NULL, NULL);
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
    window.AddDrawable(std::make_shared<Line>());
    window.AddShader(std::make_shared<Shader>(GL_VERTEX_SHADER, vertexShaderCircle.c_str()));
    window.Run();

    return 0;
}