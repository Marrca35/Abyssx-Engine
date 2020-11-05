#include "PerspectiveCamera.h"

#include <algorithm>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace walnut {
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float znear, float zfar)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, znear, zfar)), m_ViewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)))
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void PerspectiveCamera::SetProjection(float fov, float aspect, float znear, float zfar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, znear, zfar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void PerspectiveCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectDividend, float aspectDivisor, float viewDistance, float mouseSensitivityX, float mouseSensitivityY, float speed, float yaw, float pitch)
		: m_Camera(fov, aspectDividend / aspectDivisor, 0.1f, viewDistance), m_CameraFOV(fov), m_CameraAspectRatioDividend(aspectDividend), m_CameraAspectRatioDivisor(aspectDivisor), m_CameraViewDistance(viewDistance), m_CameraSpeed(speed), m_CameraYaw(yaw), m_CameraPitch(pitch), m_LastMouseX(0.0f), m_LastMouseY(0.0), m_MouseSensitivityX(mouseSensitivityX), m_MouseSensitivityY(mouseSensitivityY)
	{ }
	void PerspectiveCameraController::Update(float delta)
	{
		m_Camera.SetFront(glm::normalize(glm::vec3(cos(glm::radians(m_CameraYaw)) * cos(glm::radians(m_CameraPitch)), sin(glm::radians(m_CameraPitch)), sin(glm::radians(m_CameraYaw)) * cos(glm::radians(m_CameraPitch))) * delta));
		m_Camera.SetSpeed(m_CameraSpeed * delta);
		m_Camera.SetProjection(m_CameraFOV, m_CameraAspectRatioDividend / m_CameraAspectRatioDivisor, 0.1f, m_CameraViewDistance);
		for (int i = 0; i < GLFW_KEY_LAST; ++i)
		{
			if (!keys[i])
				continue;
			switch (i)
			{
				case GLFW_KEY_W:
					m_Camera.SetPosition(m_Camera.GetPosition() + (m_Camera.GetSpeed() * m_Camera.GetFront()));
					break;
				case GLFW_KEY_S:
					m_Camera.SetPosition(m_Camera.GetPosition() - (m_Camera.GetSpeed() * m_Camera.GetFront()));
					break;
				case GLFW_KEY_A:
					m_Camera.SetPosition(m_Camera.GetPosition() - glm::normalize(glm::cross(m_Camera.GetFront(), m_Camera.GetUp())) * m_Camera.GetSpeed());
					break;
				case GLFW_KEY_D:
					m_Camera.SetPosition(m_Camera.GetPosition() + glm::normalize(glm::cross(m_Camera.GetFront(), m_Camera.GetUp())) * m_Camera.GetSpeed());
					break;
				case GLFW_KEY_0:
					m_Camera.SetPosition(glm::vec3(0.0f));
					break;
				case GLFW_KEY_SPACE:
					m_Camera.SetPosition(m_Camera.GetPosition() + (m_Camera.GetSpeed() * m_Camera.GetUp()));
					break;
				case GLFW_KEY_LEFT_SHIFT:
					m_Camera.SetPosition(m_Camera.GetPosition() - (m_Camera.GetSpeed() * m_Camera.GetUp()));
					break;
				case GLFW_KEY_E:
					m_Camera.SetUp(glm::vec3(1.0f, 0.0f, 0.0f));
					break;
				case GLFW_KEY_Q:
					m_Camera.SetUp(glm::vec3(0.0f, 1.0f, 0.0f));
					break;
				case GLFW_KEY_R:
					m_Camera.SetUp(glm::vec3(0.0f, 0.0f, 1.0f));
					break;
			}
		}
	}

	void PerspectiveCameraController::MouseMoved(double xpos, double ypos)
	{
		m_CameraYaw += ((xpos - m_LastMouseX) * (m_MouseSensitivityX / 100.0f));
		m_CameraPitch += ((m_LastMouseY - ypos) * (m_MouseSensitivityY / 100.0f));
		m_LastMouseX = xpos;
		m_LastMouseY = ypos;
		m_CameraPitch = std::min(m_CameraPitch, 89.9f);
		m_CameraPitch = std::max(m_CameraPitch, -89.9f);
	}

	void PerspectiveCameraController::MouseScrolled(double xoffset, double yoffset)
	{
		m_CameraFOV -= yoffset;
		m_CameraFOV = std::min(m_CameraFOV, 110.0f);
		m_CameraFOV = std::max(m_CameraFOV, 60.0f);
	}

	void PerspectiveCameraController::KeyPressed(int key)
	{
		keys[key] = true;
	}
	void PerspectiveCameraController::KeyReleased(int key)
	{
		keys[key] = false;
	}
}

