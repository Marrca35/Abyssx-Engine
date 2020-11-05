#pragma once

void GLFWFrambufferSizeCallback(GLFWwindow *window, int width, int height);
void GLFWScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
void GLFWMousePosCallback(GLFWwindow *window, double xpos, double ypos);
void GLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void GLFWErrorCallback(int error, const char *description);

