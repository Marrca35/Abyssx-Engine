#include "GLFWCallbackWrapper.h"

#include <iostream>

namespace walnut {
	int EventDispatcher::s_keyEventListenerID = 0;
	std::unordered_map<int, KeyEventListener *> EventDispatcher::s_keyEventListeners;

	void EventDispatcher::MousePositionCallback(GLFWwindow *window, double xpos, double ypos)
	{

	}
	void EventDispatcher::MouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
	{ }
	void EventDispatcher::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{ }
	void EventDispatcher::MouseEnteredCallback(GLFWwindow *window, int entered)
	{ }
	void EventDispatcher::KeyCallback(GLFWwindow *window, int key, int action, int scancode, int mods)
	{
		if (!s_keyEventListeners.size() || key == GLFW_KEY_UNKNOWN)
			return;
		switch (action)
		{
			case GLFW_PRESS:
				for (int i = 0; i < s_keyEventListeners.size(); ++i)
					s_keyEventListeners[i]->OnKeyPressed({ key, scancode, mods });
				break;
			case GLFW_RELEASE:
				for (int i = 0; i < s_keyEventListeners.size(); ++i)
					s_keyEventListeners[i]->OnKeyReleased({ key, scancode, mods });
				break;
			default:
				break;
		}
	}

	int EventDispatcher::AddKeyEventListener(KeyEventListener *l)
	{
		s_keyEventListeners[++s_keyEventListenerID] = l;
		return s_keyEventListenerID;
	}
	bool EventDispatcher::RemoveKeyEventListener(int id)
	{
		if (s_keyEventListeners.find(id) != s_keyEventListeners.end())
		{
			s_keyEventListeners.erase(id);
			return true;
		}
		return false;
	}
}