#pragma once

#include <glad/glad.h>

#include "VertexBufferLayout.h"

namespace walnut {
	namespace gl {
		class VertexBuffer {
		public:
			VertexBuffer(const void *data, GLsizeiptr size);
			~VertexBuffer(void);

			inline GLuint GetID(void) const { return m_ID; }
		private:
			GLuint m_ID;
		};
	}
}

