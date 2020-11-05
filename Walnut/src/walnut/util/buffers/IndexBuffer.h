#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

namespace walnut {
	namespace gl {
		class IndexBuffer {
		public:
			IndexBuffer(const glm::u32vec3 data[], GLint count);
			~IndexBuffer(void);

			inline GLuint GetID(void) const { return m_ID; }
			inline GLuint GetCount(void) const { return m_Count; }
		private:
			GLuint m_ID, m_Count;
		};
	}
}

