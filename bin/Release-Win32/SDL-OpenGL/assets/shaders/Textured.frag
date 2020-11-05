#version 460 core

layout (location = 0) out vec4 o_Color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main()
{
	if (v_TexIndex >= 0)
	{
		o_Color = texture2D(u_Textures[int(v_TexIndex)], v_TexCoord);
		return;
	}
	o_Color = vec4(0.5, 0.2, 0.8, 1.0);
}