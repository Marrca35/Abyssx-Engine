#version 460 core

layout (location = 0) out vec4 o_color;

in vec3 p_texCoords;

uniform samplerCube skybox;

void main()
{
	o_color = texture(skybox, p_texCoords);
}