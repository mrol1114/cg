#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <string>
#include <cstdlib>
#include <memory>
#include <vector>
#include <stdexcept>
#include <optional>
#include <chrono>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/orthonormalize.hpp>

#include "IDrawable.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include <glm/fwd.hpp>

class Window
{
public:
    Window(GLFWwindow* window)
        : m_window(window)
        , m_program(std::make_unique<ShaderProgram>())
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
    }

    ~Window()
    {
        glfwTerminate();
    }

    void AddShader(std::shared_ptr<Shader> shader)
    {
        m_shaders.push_back(shader);
    }

    void Run()
    {
        Init();

        glClearColor(1, 1, 1, 0);
        glPointSize(5);

        glUseProgram(*m_program);

        while (!glfwWindowShouldClose(m_window))
        {
            int width, height;
            glfwGetWindowSize(m_window, &width, &height);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            OnMotion();
            Idle();

            SetupProjectionMatrix(width, height);
            SetupCameraMatrix();
            SetupShaderMatrix();

            glBindVertexArray(m_VAO);
            DrawObjects();
            glBindVertexArray(0);

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }

        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void AddDrawable(std::shared_ptr<IDrawable> drawable)
    {
        m_drawableObjects.push_back(drawable);
    }

    const unsigned int& GetVAO()const
    {
        return m_VAO;
    }

    const unsigned int& GetVBO()const
    {
        return m_VBO;
    }

    const float& GetPhase()const
    {
        return m_phase;
    }

private:
    void Init()
    {
        InitShaders();

        for (auto& drawableObject : m_drawableObjects)
        {
            drawableObject->Init();
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Idle()
    {
        auto elapsed = m_previousTime - m_currentTime;

        float delta = elapsed.count() * 0.001f;

        m_phase = fmodf(
            float(m_phase + delta * 2 * M_PI / m_ANIMATION_SPEED),
            float(2 * M_PI)
        );
    }

    void SetupShaderMatrix()
    {
        auto matrix = m_projectionMatrix * m_cameraMatrix;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_shaderMatrix[i*4 + j] = matrix[i][j];
            }
        }

        glUniformMatrix4fv(16, 1, GL_FALSE, m_shaderMatrix);
    }

    void InitShaders()
    {
        if (m_shaders.size() == 0)
        {
            return;
        }

        for (auto& shader : m_shaders)
        {
            shader->Compile();
            if (!shader->IsCompiled())
            {
                auto m = shader->GetInfoLog();
                throw std::runtime_error("Failed to compile shader: " + shader->GetInfoLog());
            }

            m_program->AttachShader(*shader);
        }

        m_program->Link();
        if (!m_program->IsLinked())
        {
            auto m = m_program->GetInfoLog();
            throw std::runtime_error("Failed to link program: " + m_program->GetInfoLog());
        }
    }

    void OnMotion()
    {
        double currMousePosX, currMousePosY;
        glfwGetCursorPos(m_window, &currMousePosX, &currMousePosY);

        if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS
            && m_mousePosX.has_value() && m_mousePosY.has_value())
        {
            if (m_mousePosX == currMousePosX && m_mousePosY == currMousePosY)
            {
                return;
            }

            double dx = currMousePosX - m_mousePosX.value();
            double dy = currMousePosY - m_mousePosY.value();

            int height, width;
            glfwGetWindowSize(m_window, &width, &height);

            GLdouble rotateX = dy * M_PI / width;
            GLdouble rotateY = dx * M_PI / height;
            RotateCamera(rotateX, rotateY);
        }

        m_mousePosX = currMousePosX;
        m_mousePosY = currMousePosY;
    }

    void RotateCamera(double xAngleRadians, double yAngleRadians)
    {
        const glm::dvec3 xAxis{
            m_cameraMatrix[0][0], m_cameraMatrix[1][0], m_cameraMatrix[2][0]
        };
        const glm::dvec3 yAxis{
            m_cameraMatrix[0][1], m_cameraMatrix[1][1], m_cameraMatrix[2][1]
        };

        m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);
        m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);

        m_cameraMatrix = Orthonormalize(m_cameraMatrix);
    }

    void SetupProjectionMatrix(int width, int height)
    {
        glViewport(0, 0, width, height);

        double aspect = double(width) / double(height);

        glMatrixMode(GL_PROJECTION);
        m_projectionMatrix = glm::perspective(60.0 * M_PI / 180.0, aspect, 0.1, 10.0);
        glLoadMatrixd(&m_projectionMatrix[0][0]);
    }

    void SetupCameraMatrix()
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixd(&m_cameraMatrix[0][0]);
    }

    void DrawObjects()
    {
        for (auto& drawableObject : m_drawableObjects)
        {
            drawableObject->Draw();
        }
    }

    glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m)
    {
        const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
        return {
            glm::dvec4{ normalizedMatrix[0], 0.0 },
            glm::dvec4{ normalizedMatrix[1], 0.0 },
            glm::dvec4{ normalizedMatrix[2], 0.0 },
            m[3]
        };
    }

    inline const static int m_FRUSTUM_SIZE = 2;
    inline static const float m_ANIMATION_SPEED = 0.001;

    std::chrono::steady_clock::time_point m_currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point m_previousTime = std::chrono::steady_clock::now();

    std::optional<double> m_mousePosX;
    std::optional<double> m_mousePosY;

    GLFWwindow* m_window;
    std::unique_ptr<ShaderProgram> m_program = nullptr;
    std::vector<std::shared_ptr<IDrawable>> m_drawableObjects = {};
    std::vector<std::shared_ptr<Shader>> m_shaders = {};
    unsigned int m_VAO, m_VBO;
    float m_phase;

    glm::dmat4x4 m_cameraMatrix = glm::lookAt(
        glm::dvec3{ 0.0, 0.0, 5 },
        glm::dvec3{ 0.0, 0.0, 0.0 },
        glm::dvec3{ 0.0, 1.0, 0.0 }
    );
    glm::dmat4x4 m_projectionMatrix = glm::lookAt(
        glm::dvec3{ 0.0, 0.0, 0.0 },
        glm::dvec3{ 0.0, 0.0, 0.0 },
        glm::dvec3{ 0.0, 0.0, 0.0 }
    );
    float m_shaderMatrix[16] = {0.0};
};