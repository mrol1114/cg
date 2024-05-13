#pragma once
#define _USE_MATH_DEFINES

#include "./IDrawable.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/ext.hpp>

class Line : public IDrawable
{
private:
    void Draw() override
    {
        constexpr glm::vec4 defaultColor{ 0, 0, 0, 0 };
        glColor4fv(glm::value_ptr(defaultColor));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

        glBegin(GL_LINE_STRIP);
        for (float x = -10; x < 10; x += 0.001)
        {
            glVertex3f(x, 0, 0);
        }
        glEnd();

        glDisableVertexAttribArray(0);
    }

    void Init()override
    {
    }
};