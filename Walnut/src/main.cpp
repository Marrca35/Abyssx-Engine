#include <iostream>
#include <exception>
#include <fstream>
#include <Windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_win32.h>

#include "main.h"

#include "walnut/util/Shader.h"
#include "walnut/util/Texture2D.h"
#include "walnut/util/VertexArray.h"
#include "walnut/util/Buffers.h"

#include "walnut/cameras/OrthographicCamera.h"
#include "walnut/cameras/PerspectiveCamera.h"

#include "walnut/objects/3D/Cube.h"

static bool running = false, captureMouse = true;

static int screen_width = 1280, screen_height = 720;

static std::ofstream out;

static walnut::PerspectiveCameraController cameraController(90.0f, 16.0f, 9.0f, 2048.0f, 5.0f, 5.0f);
static walnut::OrthographicCamera camera(-(16.0f / 9.0f) * 1.0f, (16.0f / 9.0f) * 1.0f, -1.0f, 1.0f);

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam)
{
	std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") << " type = 0x" << type << ", severity = 0x" << severity << ", message = " << message << std::endl;
}

int main(int argc, char *argv[])
{
	GLFWwindow *window;
	out.open("session.log");

	if (!glfwInit())
	{
		out << "FATAL ERROR: GLFW initialization failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	window = glfwCreateWindow(screen_width, screen_height, "Hello, World!", /*glfwGetPrimaryMonitor()*/nullptr, nullptr);
	if (!window)
	{
		out << "FATAL ERROR: GLFW window creation failed: " << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwGetWindowSize(window, &screen_width, &screen_height);
	{
		const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(window, (vidmode->width - screen_width) / 2, (vidmode->height - screen_height) / 2);
	}
	glfwShowWindow(window);

	glfwSetScrollCallback(window, GLFWScrollCallback);
	glfwSetCursorPosCallback(window, GLFWMousePosCallback);
	glfwSetKeyCallback(window, GLFWKeyCallback);
	glfwSetFramebufferSizeCallback(window, GLFWFrambufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		out << "FATAL ERROR: GLAD initialization failed!" << std::endl;
		return -1;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	{
		GLfloat quadVertices[] =
		{
			-0.5f, -0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  1.0f,
			 0.5f,  0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  2.0f,
			-0.5f,  0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  3.0f
		};

		GLfloat coloredVertices[] =
		{
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  2.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  3.0f,

			-0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  2.0f,
			-0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  3.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  2.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  3.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  3.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  3.0f,
		};

		glm::u32vec3 indices[] =
		{
			{1, 0, 2}, {3, 2, 0}, // -z
			{4, 5, 6}, {6, 7, 4}, // +z
			{8, 9, 10}, {10, 11, 8}, // -x
			{13, 12, 14}, {15, 14, 12}, // +x
			{16, 17, 18}, {18, 19, 16}, // -y
			{21, 20, 22}, {23, 22, 20}, // +y
		};
		
		glm::u32vec3 qi[] =
		{
			{0, 1, 2}, {2, 3, 0}
		};

		walnut::gl::VertexArray coloredVA;
		walnut::gl::VertexBuffer coloredVB(coloredVertices, sizeof(coloredVertices));
		walnut::gl::VertexBufferLayout coloredVBL;
		coloredVBL.Push(walnut::gl::push_t::Float, 3, sizeof(float) * 7);
		coloredVBL.Push(walnut::gl::push_t::Float, 3, sizeof(float) * 7);
		coloredVBL.Push(walnut::gl::push_t::Float, 1, sizeof(float) * 7);
		coloredVA.AddBuffer(coloredVB, coloredVBL);
		walnut::gl::IndexBuffer coloredIB(indices, 36);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		walnut::gl::VertexArray quadVA;
		walnut::gl::VertexBuffer quadVB(quadVertices, sizeof(quadVertices));
		quadVA.AddBuffer(quadVB, coloredVBL);
		walnut::gl::IndexBuffer quadIB(qi, 6);

		auto coloredShader = walnut::gl::Shader::LoadFromFiles("assets/shaders/TexturedPositionalLighting.vert", "assets/shaders/TexturedPositionalLighting.frag");

		auto bird_frame_1 = walnut::gl::Texture2D::LoadFromFiles("assets/bird_frame-1.png");
		auto bird_frame_2 = walnut::gl::Texture2D::LoadFromFiles("assets/bird_frame-2.png");
		auto test = walnut::gl::Texture2D::LoadFromFiles("assets/test.png");
		auto test_2 = walnut::gl::Texture2D::LoadFromFiles("assets/test_2.png");
		auto test_3 = walnut::gl::Texture2D::LoadFromFiles("assets/crosshair.png");
		auto skybox_tex = walnut::gl::Texture2D::LoadFromFiles("assets/skybox_texture.jpg");
		auto box_metal = walnut::gl::Texture2D::LoadFromFiles("assets/container2.png");
		auto box_metal_specular = walnut::gl::Texture2D::LoadFromFiles("assets/container2_specular.png");
		auto wood = walnut::gl::Texture2D::LoadFromFiles("assets/wood.png");
		bird_frame_1->Bind(0);
		bird_frame_2->Bind(1);
		test->Bind(2);
		test_2->Bind(3);
		test_3->Bind(4);
		skybox_tex->Bind(5);
		box_metal->Bind(6);
		box_metal_specular->Bind(7);

		std::vector<walnut::Cube> cubes;
		cubes.push_back(walnut::Cube(glm::vec3(0.0f), glm::vec3(2048.0f)));
		cubes.push_back(walnut::Cube(glm::vec3(4.0f), glm::vec3(4.0f)));
		cubes.push_back(walnut::Cube(glm::vec3(8.0f), glm::vec3(8.0f)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glViewport(0, 0, screen_width, screen_height);

		glfwSetCursorPos(window, screen_width / 2.0, screen_height / 2.0);
		if (glfwRawMouseMotionSupported())
		{
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO(); (void) io;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");

		glm::vec3 lighting_color(0.5f, 0.5f, 0.5f);
		glm::vec3 lighting_dir(-0.2f, -1.0f, -0.3f);

		for (int i = 0; i < cubes.size(); ++i)
		{
			coloredShader->SetUniformMat4x4("models[" + std::to_string(i + 1) + "]", cubes[i].GetModel());
		}

		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::vec3 pointLightPositions[] = {
			glm::vec3( 0.7f,  0.2f,  2.0f),
			glm::vec3( 2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3( 0.0f,  0.0f, -3.0f)
		};
		
		for (int i = 0; i < 3; ++i)
		{
			coloredShader->SetUniform3("poi_lights[" + std::to_string(i) + "].position", pointLightPositions[i]);
			coloredShader->SetUniform1("poi_lights[" + std::to_string(i) + "].constant", 1.0f);
			coloredShader->SetUniform1("poi_lights[" + std::to_string(i) + "].linear",    0.09f);
			coloredShader->SetUniform1("poi_lights[" + std::to_string(i) + "].quadratic", 0.032f);
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		running = true;
		float delta = 0.0f;
		float last = 0.0f;
		while (running)
		{
			if (glfwWindowShouldClose(window))
			{
				running = false;
			}
			float current = glfwGetTime();
			delta = current - last;
			last = current;

			cameraController.Update(delta);

			coloredShader->SetUniformMat4x4("projection", cameraController.GetCamera().GetViewProjectionMatrix());
			coloredShader->SetUniform3("view_position", cameraController.GetCamera().GetPosition());

			glm::vec3 diffuse = glm::vec3(0.8f);
			coloredShader->SetUniform3("dir_light.direction", lighting_dir);
			coloredShader->SetUniform3("dir_light.ambient", diffuse * lighting_color);
			coloredShader->SetUniform3("dir_light.diffuse", diffuse);
			coloredShader->SetUniform3("dir_light.specular", glm::vec3(16.0f));
			coloredShader->SetUniform1("material.shininess", 32.0f);
			
			cubes[0].SetTransform(cameraController.GetCamera().GetPosition());

			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

			glUseProgram(coloredShader->GetID());
			glBindVertexArray(coloredVA.GetID());

			glCullFace(GL_BACK);
			//glDepthMask(GL_FALSE);
			coloredShader->SetUniform1("material.diffuse", 6);
			coloredShader->SetUniform1("material.specular", 7);
			glDrawElementsInstanced(GL_TRIANGLES, coloredIB.GetCount(), GL_UNSIGNED_INT, nullptr, cubes.size());

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Debug");
			ImGui::ColorEdit3("Lighting Color", &lighting_color.x);
			ImGui::SliderFloat3("Lighting Direction", &lighting_dir.x, -64, 64);
			ImVec2 pos = ImGui::GetWindowPos();
			ImGui::End();

			ImGui::Begin("Info");
			glm::vec3 ccp = cameraController.GetCamera().GetPosition();
			ImGui::LabelText("World Position", "X:%.02f, Y:%.02f, Z:%.02f", ccp.x, ccp.y, ccp.z);
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwHideWindow(window);
	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void GLFWFrambufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLFWScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	cameraController.MouseScrolled(xoffset, yoffset);
}

void GLFWMousePosCallback(GLFWwindow *window, double xpos, double ypos)
{
	if (captureMouse)
	{
		cameraController.MouseMoved(xpos, ypos);
	}
}

void GLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	//if (mods == (GLFW_MOD_SHIFT | GLFW_MOD_CONTROL) && key == GLFW_KEY_Q && action == GLFW_RELEASE)
	//{
		//glfwSetWindowShouldClose(window, GLFW_TRUE);
		//return;
	//}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		captureMouse = !captureMouse;
		if (!captureMouse)
		{
			glfwSetCursorPos(window, screen_width / 2, screen_height / 2);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
	if (action != GLFW_RELEASE)
	{
		cameraController.KeyPressed(key);
	}
	else
	{
		cameraController.KeyReleased(key);
	}
}

void GLFWErrorCallback(int error, const char *description)
{
	out << "[GLFW ERROR " << error << "]: " << description << std::endl;
	std::cerr << "[GLFW ERROR " << error << "]: " << description << std::endl;
}
INT WINAPI WinMain(
	_In_	 HINSTANCE hInst,
	_In_opt_ HINSTANCE hPrevInst,
	_In_	 LPSTR lpCmdLine,
	_In_	 INT nCmdShow)
{
	const int returnCode = main(__argc, __argv);
	out.open("session.log", std::ios::out | std::ios::app);
	out << "Application exited with return code (" << returnCode << ')' << std::endl;
	out.close();
	return returnCode;
}
