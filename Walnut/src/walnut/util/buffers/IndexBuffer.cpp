#include "IndexBuffer.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

namespace walnut {
	namespace gl {
		IndexBuffer::IndexBuffer(const glm::u32vec3 data[], GLint count) : m_Count(count)
		{
			glCreateBuffers(1, &m_ID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
			glNamedBufferData(m_ID, count * sizeof(GLuint), data, GL_STATIC_DRAW);
		}
		IndexBuffer::~IndexBuffer(void)
		{
			glDeleteBuffers(1, &m_ID);
		}
	}
}

