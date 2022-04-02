#version 330 core

layout (location = 0) in vec3 L_position;
layout (location = 1) in vec3 L_color;
layout (location = 2) in vec2 L_textureCoordinates;

uniform mat4 transform;

out vec2 textureCoordinates;

void main()
{
	gl_Position = transform * vec4(L_position, 1.0f);
	textureCoordinates = vec2(L_textureCoordinates.x, 1.0f - L_textureCoordinates.y);
}