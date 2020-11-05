#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in float a_TexCoord;
layout (location = 2) in float a_TexIndex;

out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

uniform vec2 u_TexCoords[4];

vec2 texCoords[4] = {
	vec2(0.0, 0.0),
	vec2(1.0, 0.0),
	vec2(1.0, 1.0),
	vec2(0.0, 1.0)
};

void main()
{
	v_TexCoord = texCoords[int(a_TexCoord)];
	v_TexIndex = a_TexIndex;

	gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
}
