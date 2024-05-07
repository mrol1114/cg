#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <string>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>

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

        glfwSetFramebufferSizeCallback(m_window, &Window::OnSize);
    }

    ~Window()
    {
        glfwTerminate();
    }

    // draw clock in different class
    void MainLoop()
    {
        glfwMakeContextCurrent(m_window);

        int width, height;
        glfwGetWindowSize(m_window , &width, &height);
        OnSize(m_window, width, height);

        while (!glfwWindowShouldClose(m_window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0, 0, 0, 0);

            SYSTEMTIME st;
            GetLocalTime(&st);

            DrawClockMarks();
            // вынести в перемнные
            DrawTimeHand(- st.wSecond * 6, 0.7, 3);
            DrawTimeHand(- st.wMinute * 6, 0.6, 4);
            DrawTimeHand(- 30 * st.wHour - st.wMinute * 0.5, 0.5, 6);

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

    void DrawClockMarks()
    {
        for (int i = 0; i <= 12; i++)
        {
            glPushMatrix();
                glTranslated(0, 0, 0);
                glRotated(i * 30, 0, 0, 1);

                glLineWidth(4);

                glBegin(GL_LINES);
                    glVertex2d(0, 0.8);
                    glVertex2d(0, 1);
                glEnd();

            glPopMatrix();
        }
    }

    void DrawTimeHand(double angle, double height, float width)
    {
        glPushMatrix();
            glTranslated(0, 0, 0);
            glRotated(angle, 0, 0, 1);

            glLineWidth(width);

            glBegin(GL_LINES);
                glVertex2d(0, 0);
                glVertex2d(0, height);
            glEnd();
        glPopMatrix();
    }

    GLFWwindow* m_window;
};