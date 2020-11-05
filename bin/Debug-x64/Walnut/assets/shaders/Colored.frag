#version 460 core

layout (location = 0) out vec4 Color;

struct Material {
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 _FragPosition;
in vec3 _Normal;
in vec2 _TexCoord;

uniform vec3 view_position;

uniform Material material;
uniform Light light;
uniform sampler2D material_diffuse;

void main()
{
	vec3 normal = normalize(_Normal);
	vec3 lightDirection = normalize(light.position - _FragPosition);
	float diff = max(dot(normal, lightDirection), 0.0);

	vec3 viewDirection = normalize(view_position - _FragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material_diffuse, _TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material_diffuse, _TexCoord));
	vec3 specular = light.specular * (spec * material.specular);

	Color = vec4(ambient + diffuse + specular, 1.0);
}