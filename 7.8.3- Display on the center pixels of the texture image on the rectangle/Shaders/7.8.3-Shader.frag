#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;

void main()
{
	vec2 cord = vec2(1.0f-TexCoord.x, TexCoord.y);
	color = mix(texture(firstTexture, cord), texture(secondTexture, cord), 0.5f);
}