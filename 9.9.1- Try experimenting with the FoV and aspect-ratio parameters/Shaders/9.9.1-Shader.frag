#version 330 core

in vec2 textCords;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;

uniform float mixValue;

out vec4 gl_Color;

void main()
{
	gl_Color = mix(texture(firstTexture, textCords), texture(secondTexture, textCords), mixValue);	
}