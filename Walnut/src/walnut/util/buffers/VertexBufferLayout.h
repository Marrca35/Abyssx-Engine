#pragma once

#include <glad/glad.h>

#include <vector>

namespace walnut {
	namespace gl {
		struct VertexBufferElement;
		enum class push_t;

		class VertexBufferLayout {
		public:
			VertexBufferLayout(void);

			void Push(push_t type, GLuint count);
			void Push(push_t type, GLuint count, GLsizei stride);

			std::vector<VertexBufferElement> GetElements(void) const { return m_Elements; }
			GLuint GetStride(void) const { return m_Stride; }
		private:
			std::vector<VertexBufferElement> m_Elements;
			GLuint m_Stride = 0;
		};

		struct VertexBufferElement {
			GLuint type, count;
			GLboolean normalized;

			static GLuint GetSizeOfType(GLuint type);
		};

		enum class push_t {
			Float,
			UInt,
			UChar,
		};
	}
}

