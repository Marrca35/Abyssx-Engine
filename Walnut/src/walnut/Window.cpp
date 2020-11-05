#include "Window.h"

namespace walnut {
	Window::Window()
	{
		window = glfwCreateWindow(640, 480, "Walnut 0.1.0", NULL, NULL);
		glfwSetWindowUserPointer(window, static_cast<void *>(this));
	}
	Window::~Window()
	{ }
}

