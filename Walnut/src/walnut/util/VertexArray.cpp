#include "VertexArray.h"

#include <glad/glad.h>
#include "buffers/VertexBuffer.h"

#include "buffers/VertexBufferLayout.h"

#include <iostream>

namespace walnut {
	namespace gl {
		VertexArray::VertexArray()
		{
			glCreateVertexArrays(1, &m_ID);
			glBindVertexArray(m_ID);
		}
		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_ID);
		}
		void VertexArray::AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout)
		{
			GLuint bound;
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *) &bound);
			glBindVertexArray(m_ID);
			glBindBuffer(GL_ARRAY_BUFFER, buffer.GetID());
			const auto &elements = layout.GetElements();
			GLuint offset = 0;
			for (GLuint i = 0; i < elements.size(); ++i)
			{
				const auto &element = elements[i];
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *) (uint64_t) offset);
				offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
			}
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(bound);
		}
	}
}

