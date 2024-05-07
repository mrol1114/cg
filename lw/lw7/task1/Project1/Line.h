#pragma once

#include "./IDrawable.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

class Line : public IDrawable
{
private:
	void Draw() override
	{
		glBegin(GL_LINE_STRIP);
        for (float x = -10; x < 10; x += 0.1) {
            float y = x*x - 3*x - 8;
            glVertex2f(x / 20, y / 20);
        }
        glEnd();
	}
};