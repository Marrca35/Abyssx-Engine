#pragma once

#include <glm/glm.hpp>

#include "../util/Texture2D.h"

namespace walnut {
	class Material {
	public:
		Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess);

	#pragma region Setters

		void SetAmbient(const glm::vec3 &ambient) { m_Ambient = ambient; }
		void SetDiffuse(const glm::vec3 &diffuse) { m_Diffuse = diffuse; }
		void SetSpecular(const glm::vec3 &specular) { m_Specular = specular; }

	#pragma endregion Setters

	#pragma region Getters

		inline glm::vec3 GetAmbient() const { return m_Ambient; }
		inline glm::vec3 GetDiffuse() const { return m_Diffuse; }
		inline glm::vec3 GetSpecular() const { return m_Specular; }

	#pragma endregion Getters

	private:
		Texture2D m_Diffuse;
		glm::vec3 m_Specular;

		float m_Shininess;
	};

}


