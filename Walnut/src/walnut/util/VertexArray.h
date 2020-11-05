#pragma once

#include <glad/glad.h>

namespace walnut {
	namespace gl { 
	#ifndef __buffers
		class VertexBuffer;
		class VertexBufferLayout;
	#endif
		class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout);

			inline GLuint GetID(void) const { return m_ID; }
		private:
			GLuint m_ID;
		};
	}
}

