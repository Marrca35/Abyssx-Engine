#include "Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

namespace walnut {
	namespace gl {
		Shader::Shader(const std::string &vertSource, const std::string &fragSource)
			: m_ID(CreateShader(vertSource, fragSource))
		{ }

		Shader::~Shader()
		{
			glDeleteProgram(m_ID);
		}

		std::unique_ptr<Shader> Shader::LoadFromFiles(const std::string &vertPath,
			const std::string &fragPath)
		{
			return std::make_unique<Shader>(ReadFileAsString(vertPath), ReadFileAsString(fragPath));
		}

		std::string Shader::ReadFileAsString(const std::string &filepath)
		{
			std::string result;
			std::ifstream in(filepath, std::ios::in | std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				result.resize((size_t) in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&result[0], result.size());
				in.close();
			}
			else
			{
				return "";
			}

			return result;
		}

	#pragma region Uniform Setters

		void Shader::SetUniform1(const std::string &name, GLfloat val)
		{
			glProgramUniform1fv(m_ID, GetUniformLocation(name), 1, &val);
		}

		void Shader::SetUniform2(const std::string &name, const glm::vec2 &val)
		{
			glProgramUniform2fv(m_ID, GetUniformLocation(name), 1, glm::value_ptr(val));
		}

		void Shader::SetUniform3(const std::string &name, const glm::vec3 &val)
		{
			glProgramUniform3fv(m_ID, GetUniformLocation(name), 1, glm::value_ptr(val));
		}

		void Shader::SetUniform4(const std::string &name, const glm::vec4 &val)
		{
			glProgramUniform4fv(m_ID, GetUniformLocation(name), 1, glm::value_ptr(val));
		}

		void Shader::SetUniform1(const std::string &name, GLdouble val)
		{
			glProgramUniform1dv(m_ID, GetUniformLocation(name), 1, &val);
		}

		void Shader::SetUniform2(const std::string &name, const glm::dvec2 &val)
		{
			glProgramUniform2dv(m_ID, GetUniformLocation(name), 1, glm::value_ptr(val));
		}

		void Shader::SetUniform3(const std::string &name, const glm::dvec3 &val)
		{
			glProgramUniform3dv(m_ID, GetUniformLocation(name), 1, glm::value_ptr(val));
		}

		void Shader::SetUniform4(const std::string &name, const glm::dvec4 &val)
		{
			glProgramUniform4dv(m_ID, GetUniformLocation(name), 1, glm::value_ptr(val));
		}

		void Shader::SetUniform1(const std::string &name, GLint val)
		{
			glProgramUniform1iv(m_ID, GetUniformLocation(name), 1, &val);
		}

		void Shader::SetUniformMat2x2(const std::string &name, const glm::mat2x2 &val)
		{
			glProgramUniformMatrix2fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat2x3(const std::string &name, const glm::mat2x3 &val)
		{
			glProgramUniformMatrix2x3fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat2x4(const std::string &name, const glm::mat2x4 &val)
		{
			glProgramUniformMatrix2x4fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat3x2(const std::string &name, const glm::mat3x2 &val)
		{
			glProgramUniformMatrix3x2fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat3x3(const std::string &name, const glm::mat3x3 &val)
		{
			glProgramUniformMatrix3fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat3x4(const std::string &name, const glm::mat3x4 &val)
		{
			glProgramUniformMatrix3x4fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat4x2(const std::string &name, const glm::mat4x2 &val)
		{
			glProgramUniformMatrix4x2fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat4x3(const std::string &name, const glm::mat4x3 &val)
		{
			glProgramUniformMatrix4x3fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat4x4(const std::string &name, const glm::mat4x4 &val)
		{
			glProgramUniformMatrix4fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat2x2(const std::string &name, const glm::dmat2x2 &val)
		{
			glProgramUniformMatrix2dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat2x3(const std::string &name, const glm::dmat2x3 &val)
		{
			glProgramUniformMatrix2x3dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat2x4(const std::string &name, const glm::dmat2x4 &val)
		{
			glProgramUniformMatrix2x4dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat3x2(const std::string &name, const glm::dmat3x2 &val)
		{
			glProgramUniformMatrix3x2dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat3x3(const std::string &name, const glm::dmat3x3 &val)
		{
			glProgramUniformMatrix3dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat3x4(const std::string &name, const glm::dmat3x4 &val)
		{
			glProgramUniformMatrix3x4dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat4x2(const std::string &name, const glm::dmat4x2 &val)
		{
			glProgramUniformMatrix4x2dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat4x3(const std::string &name, const glm::dmat4x3 &val)
		{
			glProgramUniformMatrix4x3dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

		void Shader::SetUniformMat4x4(const std::string &name, const glm::dmat4x4 &val)
		{
			glProgramUniformMatrix4dv(m_ID, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
		}

	#pragma endregion setters for uniforms

		GLint Shader::GetUniformLocation(const std::string &name)
		{
			if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
				return m_UniformLocationCache[name];

			GLint location = glGetUniformLocation(m_ID, name.c_str());
			if (location == -1)
			{
				std::cerr << "Uniform '" << name << "' doesn't exist!" << std::endl;
			}

			m_UniformLocationCache[name] = location;
			return location;
		}

		GLuint Shader::CompileShader(GLuint type, const std::string &source)
		{
			GLuint id = glCreateShader(type);
			const char *src = source.c_str();
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);

			GLint result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				GLchar *message = new char[length];
				glGetShaderInfoLog(id, length, &length, message);
				std::cout << "Failed compilation of " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
				std::cout << message << std::endl;
				delete[] message;
				glDeleteShader(id);
				return 0;
			}

			return id;
		}

		GLuint Shader::CreateShader(const std::string &vertSource, const std::string &fragSource)
		{
			GLuint programID = glCreateProgram();
			GLuint vertexID = CompileShader(GL_VERTEX_SHADER, vertSource);
			GLuint fragmentID = CompileShader(GL_FRAGMENT_SHADER, fragSource);

			glAttachShader(programID, vertexID);
			glAttachShader(programID, fragmentID);
			glLinkProgram(programID);
			//glValidateProgram(programID);

			GLint result;
			glGetProgramiv(programID, GL_VALIDATE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
				GLchar *message = new char[length];
				glGetProgramInfoLog(programID, length, &length, message);
				std::cout << message << std::endl;
				delete[] message;
				glDeleteProgram(programID);
				return 0;
			}

			glDeleteShader(vertexID);
			glDeleteShader(fragmentID);

			return programID;
		}
	}
}

