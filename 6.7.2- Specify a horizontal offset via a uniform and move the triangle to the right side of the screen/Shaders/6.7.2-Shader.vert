#version 330 core

layout (location = 0) in vec3 position;

uniform vec4 offset;

out vec4 pos;

void main()
{
	gl_Position = vec4(position, 1.0f) + offset;
	pos = gl_Position;
}