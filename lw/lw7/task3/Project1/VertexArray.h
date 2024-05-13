#pragma once
#define _USE_MATH_DEFINES

#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "./IDrawable.h"

class VertexArray : public IDrawable
{
public:
	VertexArray(int density, const unsigned int& VBO, const unsigned int& VAO, const float& phase)
		: m_VBO(VBO)
		, m_VAO(VAO)
		, m_phase(phase)
	{
		float size = 2.0 / density;

		for (float y = -1; y <= 1; y += size)
		{
			for (float x = -1; x <= 1; x += size)
			{
				AddVertex(x, y, 0);
				AddVertex(x + size, y, 0);
				AddVertex(x, y + size, 0);

				AddVertex(x + size, y, 0);
				AddVertex(x, y + size, 0);
				AddVertex(x + size, y + size, 0);
			}
		}
	}

private:
	void AddVertex(float x, float y, float z)
	{
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		m_vertices.push_back(z);
	}

	void Draw()override
	{
		glUniform1f(0, m_phase);
		glBindVertexArray(m_VAO);

		glDrawArrays(GL_POINTS, 0, m_vertices.size());
		
		glBindVertexArray(0);
	}

	void Init()override
	{
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	std::vector<float> m_vertices;
	const float& m_phase;
	const unsigned int& m_VBO, m_VAO;
};