#version 460 core
 
out vec4 Color;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 _FragPosition;
in vec3 _Normal;
in vec2 _TexCoord;

uniform vec3 view_position;

uniform Material material;

// lights
uniform DirectionalLight dir_light;
uniform PointLight poi_lights[4];

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewdir)
{
	vec3 lightdir = normalize(-light.direction);

    float diff = max(dot(normal, lightdir), 0.0);

    vec3 reflectdir = reflect(-lightdir, normal);
    float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, _TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, _TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, _TexCoord));
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewdir)
{
	vec3 lightdir = normalize(light.position - _FragPosition);

    float diff = max(dot(normal, lightdir), 0.0);

    vec3 reflectdir = reflect(-lightdir, normal);
    float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);

    float distance    = length(light.position - _FragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, _TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, _TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, _TexCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 normal = normalize(_Normal);
    vec3 view_dir = normalize(view_position - _FragPosition);

    vec3 result = CalculateDirectionalLight(dir_light, normal, view_dir);

    for (int i = 0; i < 3; ++i)
    {
        result += CalculatePointLight(poi_lights[i], normal, view_dir);
    }

	Color = vec4(result, 1.0);
}