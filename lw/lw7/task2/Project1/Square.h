#pragma once
#include "./IDrawable.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/ext.hpp>

class Square : public IDrawable
{
private:
	void Draw()override
	{
        glBegin(GL_QUADS);
        {
            glVertex2f(-1.0, -1.0);
            glVertex2f(1.0, -1.0);
            glVertex2f(1.0, 1.0);
            glVertex2f(-1.0, 1.0);
        }
        glEnd();
	}
};
