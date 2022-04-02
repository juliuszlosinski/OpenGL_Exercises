#version 330 core

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec3 l_color;
layout (location = 2) in vec2 l_textCords;

out vec2 textCords;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(l_position, 1.0f);
	textCords = vec2(l_textCords.x, 1.0f - l_textCords.y);
}