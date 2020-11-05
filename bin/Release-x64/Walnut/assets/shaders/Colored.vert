#version 460 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

out vec3 _FragPosition;
out vec3 _Normal;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position = projection * model * vec4(Position, 1.0);
	_FragPosition = vec3(model * vec4(Position, 1.0));
	_Normal = mat3(transpose(inverse(model))) * Normal;
}
