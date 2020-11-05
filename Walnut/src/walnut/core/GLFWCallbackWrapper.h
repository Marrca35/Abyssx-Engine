#pragma once

#include <memory>
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "../Window.h"

#include "KeyEventListener.h"

namespace walnut {
	class EventDispatcher {
	public:
		static void MousePositionCallback(GLFWwindow *window, double xpos, double ypos);
		static void MouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
		static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
		static void MouseEnteredCallback(GLFWwindow *window, int entered);

		static void KeyCallback(GLFWwindow *window, int key, int action, int scancode, int mods);

		static int AddKeyEventListener(KeyEventListener *l);
		static bool RemoveKeyEventListener(int id);
	private:
		static std::unordered_map<int, KeyEventListener *> s_keyEventListeners;
		static int s_keyEventListenerID;
	private:
		EventDispatcher() = delete;
		EventDispatcher(const EventDispatcher &) = delete;
		EventDispatcher(EventDispatcher &&) = delete;
		~EventDispatcher() = delete;
		void operator=(EventDispatcher const &) = delete;
	};
}
