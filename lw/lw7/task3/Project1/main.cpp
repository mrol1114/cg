#define _USE_MATH_DEFINES

#include <memory>

#include "Window.h"
#include "Line.h"
#include "VertexArray.h"

int main(void)
{
    std::string vertexShaderCircle = R"(
#version 450 core

layout (location=0) in vec3 position;
layout (location=16) uniform mat4 u_matrix;
layout (location=0) uniform float u_phase;

void main()
{
    float endPoistionZ = (position.x*position.x / 0.5 / 2) + (position.y*position.y / 0.5 / 2);
    vec4 endPosition = vec4(position.xy, endPoistionZ, 1.0);

    float startPoistionZ = (position.x*position.x / 0.5 / 2) - (position.y*position.y / 0.5 / 2);
    vec4 startPosition = vec4(position.xy, startPoistionZ, 1.0);

    vec4 vertex = mix(startPosition, endPosition, u_phase);

    gl_Position = u_matrix * vertex;
}
    )";

    if (!glfwInit())
        throw std::runtime_error("glfw is not initialized");

    GLFWwindow* glfwWindow = glfwCreateWindow(720, 540, "Paraboloid", NULL, NULL);
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
    window.AddDrawable(std::make_shared<VertexArray>(8, window.GetVBO(), window.GetVAO(), window.GetPhase()));
    window.AddShader(std::make_shared<Shader>(GL_VERTEX_SHADER, vertexShaderCircle.c_str()));
    window.Run();

    return 0;
}