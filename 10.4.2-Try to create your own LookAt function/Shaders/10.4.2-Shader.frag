#version 330 core

in vec2 textCords;

uniform sampler2D firstTexture;

out vec4 gl_Color;

void main()
{
	gl_Color = texture(firstTexture, textCords);
}