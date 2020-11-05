#include "VertexBufferLayout.h"

#include <cassert>

#include <glad/glad.h>

namespace walnut {
	namespace gl {
		VertexBufferLayout::VertexBufferLayout(void) : m_Stride(0)
		{ }
		void VertexBufferLayout::Push(push_t type, GLuint count)
		{
			switch (type)
			{
				case push_t::Float:
					m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
					break;
				case push_t::UInt:
					m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
					break;
				case push_t::UChar:
					m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
					break;
			}
		}
		void VertexBufferLayout::Push(push_t type, GLuint count, GLsizei stride)
		{
			m_Stride = stride;
			switch (type)
			{
				case push_t::Float:
					m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
					break;
				case push_t::UInt:
					m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
					break;
				case push_t::UChar:
					m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
					break;
			}
		}
		GLuint VertexBufferElement::GetSizeOfType(GLuint type)
		{
			switch (type)
			{
				case GL_FLOAT:
				case GL_UNSIGNED_INT:
					return 4;
				case GL_UNSIGNED_BYTE:
					return 1;
			}
			assert(false);
			return 0;
		}
	}
}

