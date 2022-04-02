#version 330 core

in vec2 textureCoordinates;

out vec4 gl_Color;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;
uniform float mixValue;

void main()
{
	gl_Color = mix(texture(firstTexture, textureCoordinates), texture(secondTexture, textureCoordinates), mixValue);
}