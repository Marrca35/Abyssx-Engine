#version 460 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in float TexCoordIndex;

out vec3 _FragPosition;
out vec3 _Normal;
out vec2 _TexCoord;

uniform mat4 projection;
uniform mat4 models[100];

vec2 texCoords[4] = {
	vec2(0.0, 0.0),
	vec2(1.0, 0.0),
	vec2(1.0, 1.0),
	vec2(0.0, 1.0)
};

void main()
{
	gl_Position = projection * models[gl_InstanceID] * vec4(Position, 1.0);
	_FragPosition = vec3(models[gl_InstanceID] * vec4(Position, 1.0));
	_Normal = mat3(transpose(inverse(models[gl_InstanceID]))) * Normal;
	_TexCoord = texCoords[int(TexCoordIndex + 0.5)];
}
