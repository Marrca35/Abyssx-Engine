#include "VertexBuffer.h"

#include <glad/glad.h>

namespace walnut {
	namespace gl {
		VertexBuffer::VertexBuffer(const void *data, GLsizeiptr size)
		{
			glCreateBuffers(1, &m_ID);
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
			glNamedBufferData(m_ID, size, data, GL_STATIC_DRAW);
		}
		VertexBuffer::~VertexBuffer(void)
		{
			glDeleteBuffers(1, &m_ID);
		}
	}
}

