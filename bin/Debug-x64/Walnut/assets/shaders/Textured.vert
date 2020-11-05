#version 460 core

layout (location = 0) in vec3 Position;
layout (location = 1) in float TexCoordIndex;
layout (location = 2) in float TexIndex;

out vec2 _TexCoord;
out float _TexIndex;

uniform mat4 projection;
uniform mat4 model;

uniform vec2 u_TexCoords[4];

vec2 texCoords[4] = {
	vec2(0.0, 0.0),
	vec2(1.0, 0.0),
	vec2(1.0, 1.0),
	vec2(0.0, 1.0)
};

void main()
{
	_TexCoord = texCoords[int(TexCoordIndex + 0.5)];
	_TexIndex = TexIndex;

	gl_Position = projection * model * vec4(Position, 1.0);
}
