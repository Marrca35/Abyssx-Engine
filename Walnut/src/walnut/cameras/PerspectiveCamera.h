#pragma once

#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace walnut {
	class PerspectiveCamera {
	public:
		PerspectiveCamera(float fov, float aspect, float znear, float zfar);

	#pragma region Setters

		void SetProjection(float fov, float aspect, float znear, float zfar);
		void SetPosition(const glm::vec3 &position) { m_Position = position; RecalculateViewMatrix(); }
		void SetFront(glm::vec3 front) { m_Front = front; RecalculateViewMatrix(); }
		void SetUp(glm::vec3 up) { m_Up = up; RecalculateViewMatrix(); }
		void SetSpeed(float speed) { m_Speed = speed; RecalculateViewMatrix(); }

	#pragma endregion Setters

	#pragma region Getters

		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec3 GetFront() const { return m_Front; }
		glm::vec3 GetUp() const { return m_Up; }

		float GetSpeed() const { return m_Speed; }

		glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	
	#pragma endregion Getters

	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Front = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };

		float m_Speed = 0.5f;
	};

	class PerspectiveCameraController {
	public:
		PerspectiveCameraController(float fov = 60.0f, float aspectDividend = 16.0f, float aspectDivisor = 9.0f, float viewDistance = 95.0f, float mouseSensitivityX = 15.1f, float mouseSensitivityY = 15.1f, float speed = 12.5f, float yaw = -90.0f, float pitch = 0.0f);

	#pragma region Update Functions

		virtual void Update(float delta);
		virtual void MouseMoved(double xpos, double ypos);
		virtual void MouseScrolled(double xoffset, double yoffset);
		void KeyPressed(int key);
		void KeyReleased(int key);

	#pragma endregion Update Functions

	#pragma region Setters

		void SetMouseSensitivityX(float mouseSensitivityX) { m_MouseSensitivityX = mouseSensitivityX; }
		void SetMouseSensitivityY(float mouseSensitivityY) { m_MouseSensitivityY = mouseSensitivityY; }

		void SetCameraSpeed(float speed) { m_CameraSpeed = speed; }
		void SetCameraFOV(float fov) { m_CameraFOV = fov; }
		void SetCameraViewDistance(float distance) { m_CameraViewDistance = distance; }

		void SetCameraAspectRatioDividend(float dividend) { m_CameraAspectRatioDividend = dividend; }
		void SetCameraAspectRatioDivisor(float divisor) { m_CameraAspectRatioDivisor = divisor; }
		void SetCameraAspectRatio(float dividend, float divisor) { m_CameraAspectRatioDividend = dividend; m_CameraAspectRatioDivisor = divisor; }

	#pragma endregion Setters

	#pragma region Getters

		inline float GetMouseSensitivityX() const { return m_MouseSensitivityX; }
		inline float GetMouseSensitivityY() const { return m_MouseSensitivityY; }

		inline float GetCameraSpeed() const { return m_CameraSpeed; }
		inline float GetCameraFOV() const { return m_CameraFOV; }
		inline float GetCameraViewDistance() const { return m_CameraViewDistance; }

		inline float GetCameraAspectRatioDividend() const { return m_CameraAspectRatioDividend; }
		inline float GetCameraAspectRatioDivisor() const { return m_CameraAspectRatioDivisor; }
		inline float GetCameraAspectRatio() const { return m_CameraAspectRatioDividend / m_CameraAspectRatioDivisor; }

		PerspectiveCamera GetCamera() const { return m_Camera; }

	#pragma endregion Getters

	private:
		PerspectiveCamera m_Camera;

		float m_MouseSensitivityX, m_MouseSensitivityY, m_LastMouseX, m_LastMouseY, m_CameraPitch, m_CameraYaw, m_CameraSpeed, m_CameraFOV, m_CameraViewDistance, m_CameraAspectRatioDividend, m_CameraAspectRatioDivisor;
		std::unordered_map<int, bool> keys;
	};
}

