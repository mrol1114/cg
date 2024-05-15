#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <string>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>

#include "CoordinateGrid.h"
#include "Bezier—urve.h"

class Window
{
public:
    Window(const std::string& windowTitle, int windowWidth, int windowHeight)
        : m_coordinateGrid(CoordinateGrid(0.8, 0.2, 0.2))
    {
        if (!glfwInit())
            throw std::runtime_error("glfw is not initialized");

        m_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
        if (!m_window)
        {
            glfwTerminate();
            throw std::runtime_error("could not create window");
        }

        glfwSetFramebufferSizeCallback(m_window, &Window::OnSize);
    }

    ~Window()
    {
        glfwTerminate();
    }
    
    void Run()
    {
        glfwMakeContextCurrent(m_window);

        int width, height;
        glfwGetWindowSize(m_window , &width, &height);
        OnSize(m_window, width, height);

        while (!glfwWindowShouldClose(m_window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1, 1, 1, 0);

            m_coordinateGrid.Draw();
            m_curve.Draw();

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

private:
    static void OnSize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        double aspect = (double)width / height;
        double viewHeight = 2;
        double viewWidth = aspect * viewHeight;

        glOrtho(
            -viewWidth, +viewWidth,
            -viewHeight, +viewHeight,
            -1, 1
        );

        glMatrixMode(GL_MODELVIEW);
    }

    BezierCurve m_curve;
    CoordinateGrid m_coordinateGrid;
    GLFWwindow* m_window;
};