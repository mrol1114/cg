#pragma once

#include "IDrawable.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <GL/glu.h> 
#include <GLFW/glfw3.h>

#include "IDrawable.h"

class CoordinateGrid : public IDrawable
{
public:
    CoordinateGrid(float size, float endSize)
        : m_size(size)
        , m_endSize(endSize)
    {
    }

	void Draw()override
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
        {
            glColor3ub(0, 0, 255);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, m_size);
            glVertex3f(0, 0, m_size);
            glVertex3f(-arrowOffset2, 0, m_size - arrowOffset);
            glVertex3f(0, 0, m_size);
            glVertex3f(+arrowOffset2, 0, m_size - arrowOffset);
        }
        glEnd();
	}

private:
    float m_size;
    float m_endSize;
};