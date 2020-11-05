#pragma once

#include <string>
#include <memory>

#include <glad/glad.h>

namespace walnut {
	namespace gl {
		class Texture2D {
		public:
			Texture2D(GLint width, GLint height, GLint bpp, GLubyte *pixels, GLint magMinFilter, GLint magFilter, GLint wrapS, GLint wrapT);
			~Texture2D();

			void Bind(GLenum slot);
			void Unbind();
		public:
			static std::unique_ptr<Texture2D> LoadFromFiles(const std::string &filepath,
				GLint magMinFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE);
		private:
			GLuint m_ID;
			GLint m_CurrentSlot;

			GLsizei m_TexHeight, m_TexWidth, m_TexBPP;
			GLubyte *m_LocalBuffer;
		};
	}
}

