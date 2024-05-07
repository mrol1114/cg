#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <string>
#include <cstdlib>
#include <memory>
#include <vector>
#include <stdexcept>
#include <optional>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/orthonormalize.hpp>

#include "IDrawable.h"

class Window
{
public:
    Window(const std::string& windowTitle, int windowWidth, int windowHeight)
    {
        if (!glfwInit())
            throw std::runtime_error("glfw is not initialized");

        m_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
        if (!m_window)
        {
            glfwTerminate();
            throw std::runtime_error("could not create window");
        }
    }

    ~Window()
    {
        glfwTerminate();
    }

    void Run()
    {
        glfwMakeContextCurrent(m_window);
        glClearColor(1, 1, 1, 0);

        while (!glfwWindowShouldClose(m_window))
        {
            int width, height;
            glfwGetWindowSize(m_window, &width, &height);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            OnMotion();
            SetupProjectionMatrix(width, height);
            SetupCameraMatrix();

            DrawObjects();

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

    void AddDrawable(std::shared_ptr<IDrawable> drawable)
    {
        m_drawableObjects.push_back(drawable);
    }

private:
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
        // раз
        m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);
        m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);

        m_cameraMatrix = Orthonormalize(m_cameraMatrix);
    }

    void SetupProjectionMatrix(int width, int height)
    {
        glViewport(0, 0, width, height);

        double aspect = double(width) / double(height);

        glMatrixMode(GL_PROJECTION);
        const auto projMat = glm::perspective(60.0 * M_PI / 180.0, aspect, 0.1, 10.0);
        glLoadMatrixd(&projMat[0][0]);
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

    const static int m_FRUSTUM_SIZE = 2;

    std::optional<double> m_mousePosX;
    std::optional<double> m_mousePosY;

    GLFWwindow* m_window;
    std::vector<std::shared_ptr<IDrawable>> m_drawableObjects = {};

    glm::dmat4x4 m_cameraMatrix = glm::lookAt(
        glm::dvec3{ 0.0, 0.0, 2 },
        glm::dvec3{ 0.0, 0.0, 0.0 },
        glm::dvec3{ 0.0, 1.0, 0.0 }
    );
};