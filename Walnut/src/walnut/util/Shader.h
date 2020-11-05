#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>
#include <memory>

namespace walnut {
	namespace gl {
		class Shader {
		public:
			Shader(const std::string &vertSource, const std::string &fragSource);
			~Shader();

		#pragma region Uniform Setters

			void SetUniform1(const std::string &name, GLfloat val);
			void SetUniform2(const std::string &name, const glm::vec2 &val);
			void SetUniform3(const std::string &name, const glm::vec3 &val);
			void SetUniform4(const std::string &name, const glm::vec4 &val);

			void SetUniform1(const std::string &name, GLdouble val);
			void SetUniform2(const std::string &name, const glm::dvec2 &val);
			void SetUniform3(const std::string &name, const glm::dvec3 &val);
			void SetUniform4(const std::string &name, const glm::dvec4 &val);

			void SetUniform1(const std::string &name, GLint val);

			void SetUniformMat2x2(const std::string &name, const glm::mat2x2 &val);
			void SetUniformMat2x3(const std::string &name, const glm::mat2x3 &val);
			void SetUniformMat2x4(const std::string &name, const glm::mat2x4 &val);
			void SetUniformMat3x2(const std::string &name, const glm::mat3x2 &val);
			void SetUniformMat3x3(const std::string &name, const glm::mat3x3 &val);
			void SetUniformMat3x4(const std::string &name, const glm::mat3x4 &val);
			void SetUniformMat4x2(const std::string &name, const glm::mat4x2 &val);
			void SetUniformMat4x3(const std::string &name, const glm::mat4x3 &val);
			void SetUniformMat4x4(const std::string &name, const glm::mat4x4 &val);

			void SetUniformMat2x2(const std::string &name, const glm::dmat2x2 &val);
			void SetUniformMat2x3(const std::string &name, const glm::dmat2x3 &val);
			void SetUniformMat2x4(const std::string &name, const glm::dmat2x4 &val);
			void SetUniformMat3x2(const std::string &name, const glm::dmat3x2 &val);
			void SetUniformMat3x3(const std::string &name, const glm::dmat3x3 &val);
			void SetUniformMat3x4(const std::string &name, const glm::dmat3x4 &val);
			void SetUniformMat4x2(const std::string &name, const glm::dmat4x2 &val);
			void SetUniformMat4x3(const std::string &name, const glm::dmat4x3 &val);
			void SetUniformMat4x4(const std::string &name, const glm::dmat4x4 &val);

		#pragma endregion setters for uniforms

		#pragma region Getters

			inline GLuint GetID(void) const { return m_ID; }
			inline GLint GetUniformLocation(const std::string &name);

		#pragma endregion Getters

		public:
			static std::unique_ptr<Shader> LoadFromFiles(const std::string &vertPath,
				const std::string &fragPath);
		private:
			static GLuint CompileShader(GLuint type, const std::string &source);
			static GLuint CreateShader(const std::string &vertSource, const std::string &fragSource);
			static std::string ReadFileAsString(const std::string &filepath);
		private:
			std::unordered_map<std::string, GLint> m_UniformLocationCache;
			const GLuint m_ID;
		};
	}
}

