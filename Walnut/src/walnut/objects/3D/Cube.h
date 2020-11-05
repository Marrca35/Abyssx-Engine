#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace walnut {
	class Cube {
	public:
		Cube(const glm::vec3 &transform = glm::vec3(0.0f), const glm::vec3 &scale = glm::vec3(1.0), const glm::vec4 &rotation = glm::vec4(0.0f, 0.0f, 0.0f, 90.0f));

		inline void SetX(float x) { m_Transform.x = x; }
		inline void SetY(float y) { m_Transform.y = y; }
		inline void SetZ(float z) { m_Transform.z = z; }
		inline void SetTransform(const glm::vec3 &transform) { m_Transform = transform; }
		
		inline void SetWidth(float width) { m_Scale.x = width; }
		inline void SetHeight(float height) { m_Scale.y = height; }
		inline void SetLength(float length) { m_Scale.z = length; }
		inline void SetScale(const glm::vec3 &scale) { m_Scale = scale; }

		inline void SetYaw(float yaw) { m_Rotation.x = yaw; }
		inline void SetPitch(float pitch) { m_Rotation.y = pitch; }
		inline void SetRoll(float roll) { m_Rotation.z = roll; }
		inline void SetAngle(float angle) { m_Rotation.w = angle; }
		inline void SetRotation(const glm::vec4 &rotation) { m_Rotation = rotation; }

		inline glm::vec3 GetTransform() const { return m_Transform; }
		inline glm::vec3 GetScale() const { return m_Scale; }

		glm::mat4 GetModel() const;

	private:
		glm::vec3 m_Transform, m_Scale;
		glm::vec4 m_Rotation;
	};
}

