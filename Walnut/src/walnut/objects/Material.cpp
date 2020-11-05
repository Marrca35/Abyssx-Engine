#include "Material.h"

namespace walnut {
	Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess)
		: m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess)
	{

	}
}

