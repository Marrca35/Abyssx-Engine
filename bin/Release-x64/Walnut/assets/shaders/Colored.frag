#version 460 core

layout (location = 0) out vec4 Color;

struct Material {
	vec3 ambient;
	vec3 diffuse;
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

uniform vec3 view_position;

uniform Material material;
uniform Light light;

void main()
{
	vec3 normal = normalize(_Normal);
	vec3 lightDirection = normalize(light.position - _FragPosition);
	float diff = max(dot(normal, lightDirection), 0.0);

	vec3 viewDirection = normalize(view_position - _FragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	vec3 ambient = light.ambient * material.ambient;
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = (ambient + diffuse + specular);
	Color = vec4(result, 1.0);
}