#pragma once
#include <GL/glew.h>
#include <stdexcept>
#include <utility>
#include <string>

class ShaderProgram
{
public:
	ShaderProgram()
		: m_program{ glCreateProgram() }
	{
		if (!m_program)
		{
			throw std::runtime_error("Failed to create program");
		}
	}

	ShaderProgram(ShaderProgram&& other) noexcept
		: m_program{ std::exchange(other.m_program, 0) }
	{
	}

	~ShaderProgram()
	{
		glDeleteProgram(m_program);
	}

	void AttachShader(GLuint shader) noexcept
	{
		glAttachShader(m_program, shader);
	}

	void Link() noexcept
	{
		glLinkProgram(m_program);
	}

	bool IsLinked() const noexcept
	{
		int linkStatus = GL_FALSE;
		GetParameter(GL_LINK_STATUS, &linkStatus);
		return linkStatus == GL_TRUE;
	}

	void GetParameter(GLenum paramName, GLint* param) const noexcept
	{
		glGetProgramiv(m_program, paramName, param);
	}

	std::string GetInfoLog() const
	{
		GLint bufSize = 0;
		GetParameter(GL_INFO_LOG_LENGTH, &bufSize);
		std::string log(static_cast<size_t>(bufSize), ' ');

		GLsizei actualLength;
		glGetProgramInfoLog(m_program, static_cast<GLsizei>(bufSize), &actualLength, log.data());
		log.resize(static_cast<size_t>(actualLength));

		return log;
	}

	operator GLuint() const noexcept
	{
		return m_program;
	}

private:
	GLuint m_program;
};