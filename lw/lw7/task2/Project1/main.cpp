#define _USE_MATH_DEFINES

#include <memory>
#include <vector>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/orthonormalize.hpp>


GLuint loadAndCompileShader(GLenum shaderType, const char* sourceCode) {
    // Create the shader
    GLuint shader = glCreateShader(shaderType);

    if (shader) {
        // Pass the shader source code
        glShaderSource(shader, 1, &sourceCode, NULL);

        // Compile the shader source code
        glCompileShader(shader);

        // Check the status of compilation
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            // Get the info log for compilation failure
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen) {
                std::vector< char > buf(infoLen);

                glGetShaderInfoLog(shader, infoLen, NULL, &buf[0]);

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

int main(void)
{
    std::string vertexShaderCircle = R"(
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

    auto m_window = glfwCreateWindow(720, 540, "syn", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("could not create window");
    }

    glfwMakeContextCurrent(m_window);

    glewInit();
    if (!GLEW_ARB_shader_objects)
    {
        throw std::runtime_error("glew is not initialized");
    }


    auto shader = loadAndCompileShader(GL_FRAGMENT_SHADER, vertexShaderCircle.c_str());

    auto program = glCreateProgram();

    glAttachShader(program, shader);
    glLinkProgram(program);

    glUseProgram(program);

    glClearColor(1, 1, 1, 0);

    while (!glfwWindowShouldClose(m_window))
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glUniform2f(0, width, height);

        glBegin(GL_QUADS);
        {
            glVertex2f(-1.0, -1.0);
            glVertex2f(1.0, -1.0);
            glVertex2f(1.0, 1.0);
            glVertex2f(-1.0, 1.0);
        }
        glEnd();

        glViewport(0, 0, width, height);

        double aspect = double(width) / double(height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-aspect, +aspect, -1, 1, 0, 10);
        glMatrixMode(GL_MODELVIEW);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    return 0;
}