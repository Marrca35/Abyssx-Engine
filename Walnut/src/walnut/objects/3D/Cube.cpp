#include "Cube.h"

namespace walnut {
	Cube::Cube(const glm::vec3& transform, const glm::vec3& scale, const glm::vec4 &rotation)
		: m_Transform(transform), m_Scale(scale), m_Rotation(rotation)
	{ }

	glm::mat4 Cube::GetModel() const
	{
		return glm::scale(glm::translate(glm::mat4(1.0f), m_Transform), m_Scale);
		//return (m_Rotation != glm::vec4(0.0f)) ? glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f), m_Transform), m_Scale), glm::radians(m_Rotation.w), glm::vec3(m_Rotation)) : glm::scale(glm::translate(glm::mat4(1.0f), m_Transform), m_Scale);
	}
}

