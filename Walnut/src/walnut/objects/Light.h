#pragma once

#include <glm/glm.hpp>

namespace walnut {
	class Light {
	public:
		Light(const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);

		void SetX(float x) { m_Position.x = x; }
		void SetY(float y) { m_Position.y = y; }
		void SetZ(float z) { m_Position.z = z; }
		void SetPosition(const glm::vec3 &pos) { m_Position = pos; }

		void SetAmbient(const glm::vec3 &ambient) { m_Ambient = ambient; }
		void SetDiffuse(const glm::vec3 &diffuse) { m_Diffuse = diffuse; }
		void SetSpecular(const glm::vec3 &specular) { m_Specular = m_Specular; }

		inline glm::vec3 GetPosition() const { return m_Position; }
		
		inline glm::vec3 GetAmbient() const { return m_Ambient; }
		inline glm::vec3 GetDiffuse() const { return m_Diffuse; }
		inline glm::vec3 GetSpecular() const { return m_Specular; }

	private:
		glm::vec3 m_Position;

		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
	};

}


