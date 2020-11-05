#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace walnut {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled)
		: m_AspectRatio(aspectRatio), m_CameraRotationEnabled(rotationEnabled), m_Camera(-m_AspectRatio - m_CameraZoomLevel, m_AspectRatio - m_CameraZoomLevel, -m_CameraZoomLevel, m_CameraZoomLevel)
	{ }

	void OrthographicCameraController::Update(float delta)
	{
		m_Camera.SetProjection(-m_AspectRatio - m_CameraZoomLevel, m_AspectRatio - m_CameraZoomLevel, -m_CameraZoomLevel, m_CameraZoomLevel);
		if (m_CameraRotationEnabled)
		{
			m_Camera.SetRotation(m_CameraRotation * delta);
			if (keys[GLFW_KEY_Q])
			{
				m_CameraRotation += m_CameraRotationSpeed;
			}
			if (keys[GLFW_KEY_E])
			{
				m_CameraRotation -= m_CameraRotationEnabled;
			}
		}
	}

	void OrthographicCameraController::KeyPressed(int key)
	{
		keys[key] = true;
	}

	void OrthographicCameraController::KeyReleased(int key)
	{
		keys[key] = false;
	}

}

