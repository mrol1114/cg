#pragma once

#include <cstdlib>
#include <GLFW/glfw3.h>

class CoordinateGrid
{
public:
    CoordinateGrid(float size, float endSize, float markSize)
        : m_size(size)
        , m_endSize(endSize)
    {
    }

	void Draw()
	{
        float arrowOffset = m_size * m_endSize;
        float arrowOffset2 = arrowOffset * 0.5;

        glBegin(GL_LINES);
        {
            glColor3ub(255, 0, 0);

            glVertex3f(0, 0, 0);
            glVertex3f(m_size, 0, 0);
            glVertex3f(m_size, 0, 0);
            glVertex3f(m_size - arrowOffset, -arrowOffset2, 0);
            glVertex3f(m_size, 0, 0);
            glVertex3f(m_size - arrowOffset, +arrowOffset2, 0);
        }
        {
            glColor3ub(0, 255, 0);

            glVertex3f(0, 0, 0);
            glVertex3f(0, m_size, 0);
            glVertex3f(0, m_size, 0);
            glVertex3f(-arrowOffset2, m_size - arrowOffset, 0);
            glVertex3f(0, m_size, 0);
            glVertex3f(+arrowOffset2, m_size - arrowOffset, 0);
        }
        glEnd();

        /*for (size_t i = 0; i < MARKS_COUNT; i++)
        {
            glBegin(GL_LINES);
            {
                glColor3ub(255, 0, 0);

                glVertex3f(- m_markSize / 2, i * m_size / MARKS_COUNT, 0);
                glVertex3f(m_markSize / 2, i * m_size / MARKS_COUNT, 0);
            }
        }

        for (size_t i = 0; i < MARKS_COUNT; i++)
        {
            glBegin(GL_LINES);
            {
                glColor3ub(0, 255, 0);

                glVertex3f(i * m_size / MARKS_COUNT, - m_markSize / 2, 0);
                glVertex3f(i * m_size / MARKS_COUNT, m_markSize / 2, 0);
            }
        }*/
	}

private:
    inline static size_t MARKS_COUNT = 10;

    float m_size;
    float m_endSize;
    float m_markSize;
};