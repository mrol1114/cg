#pragma once
#include <GL/glew.h>
#include <string>
#include <utility>
#include <stdexcept>

class Shader
{
public:
	explicit Shader(GLenum type, const char* text = nullptr)
		: m_shader{ glCreateShader(type) }
	{
		if (!m_shader)
		{
			throw std::runtime_error("Failed to create shader");
		}

		if (text)
		{
			SetSource(text);
		}
	}

	~Shader()
	{
		glDeleteShader(m_shader);
	}

	void SetSource(const char* text) noexcept
	{
		glShaderSource(m_shader, 1, &text, nullptr);
	}

	void Compile() noexcept
	{
		glCompileShader(m_shader);
	}

	void GetParameter(GLenum paramName, GLint* p) const noexcept
	{
		glGetShaderiv(m_shader, paramName, p);
	}

	std::string GetInfoLog() const
	{
		int infoLogLength = 0;
		GetParameter(GL_INFO_LOG_LENGTH, &infoLogLength);
		std::string log(static_cast<size_t>(infoLogLength), ' ');
		GLsizei actualSize = 0;
		glGetShaderInfoLog(m_shader, infoLogLength, &actualSize, log.data());
		log.resize(static_cast<size_t>(actualSize));
		return log;
	}

	bool IsCompiled() const noexcept
	{
		int compileStatus = GL_FALSE;
		GetParameter(GL_COMPILE_STATUS, &compileStatus);
		return compileStatus == GL_TRUE;
	}

	operator GLuint() const noexcept
	{
		return m_shader;
	}

private:
	GLuint m_shader = 0u;
};