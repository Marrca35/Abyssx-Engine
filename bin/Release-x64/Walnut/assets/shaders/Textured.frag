#version 460 core

layout (location = 0) out vec4 Color;

struct Material {
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

in vec2 _TexCoord;
in float _TexIndex;

uniform sampler2D u_Textures[8];

void main()
{
	if (_TexIndex >= 0)
	{
		Color = texture2D(u_Textures[int(_TexIndex + 0.5)], _TexCoord);
		return;
	}
	Color = vec4(0.5, 0.2, 0.8, 1.0);
}