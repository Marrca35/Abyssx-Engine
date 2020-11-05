#version 450 core

layout (location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main()
{
	int texIndex = int(v_TexIndex);
	if (texIndex >= 1)
	{
		o_Color = texture(u_Textures[texIndex], v_TexCoord);
	}
	else
	{
		o_Color = v_Color;
	}
}