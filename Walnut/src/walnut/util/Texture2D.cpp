#include "Texture2D.h"

#include <stb_image.h>

namespace walnut {
	namespace gl {
		Texture2D::Texture2D(GLint width, GLint height, GLint bpp, GLubyte *pixels,
			GLint magMinFilter, GLint magFilter, GLint wrapS, GLint wrapT)
			: m_TexWidth(width), m_TexHeight(height), m_TexBPP(bpp), m_LocalBuffer(pixels), m_CurrentSlot(-1)
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magMinFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_TexWidth, m_TexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		Texture2D::~Texture2D()
		{
			glDeleteTextures(1, &m_ID);
		}
		void Texture2D::Bind(GLenum slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_ID);
			m_CurrentSlot = static_cast<GLint>(slot);
		}
		void Texture2D::Unbind()
		{
			if (m_CurrentSlot < 0)
				return;
			GLenum slot = static_cast<GLenum>(m_CurrentSlot);
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, 0);
			m_CurrentSlot = -1;
		}
		std::unique_ptr<Texture2D> Texture2D::LoadFromFiles(const std::string &filepath, GLint magMinFilter, GLint magFilter, GLint wrapS, GLint wrapT)
		{
			GLint width, height, bpp;
			GLubyte *pixels;
			stbi_set_flip_vertically_on_load(1);
			pixels = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);
			auto ret = std::make_unique<Texture2D>(width, height, bpp, pixels, magMinFilter, magFilter, wrapS, wrapT);
			if (pixels)
			{
				stbi_image_free(pixels);
			}
			return ret;
		}
	}
}

