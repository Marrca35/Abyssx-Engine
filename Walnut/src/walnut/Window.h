#pragma once

#include <GLFW/glfw3.h>

namespace walnut {
	class Window {
	public:
		Window();
		~Window();
		

	private:
		GLFWwindow *window;
	};
}

