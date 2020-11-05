#version 460 core

layout (location = 0) in vec3 i_position;

out vec3 p_texCoords;

uniform mat4 projection;
uniform mat4 model;

vec2 texCoords[4] = {
	vec2(0.0, 0.0),
	vec2(1.0, 0.0),
	vec2(1.0, 1.0),
	vec2(0.0, 1.0)
};

void main()
{
	gl_Position = projection * vec4(i_position, 1.0);
	p_texCoords = i_position;
}