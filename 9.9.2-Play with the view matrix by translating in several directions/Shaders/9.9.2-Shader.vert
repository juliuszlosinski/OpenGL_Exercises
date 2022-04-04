#version 330 core

layout (location = 0) in vec3 L_position;
layout (location = 1) in vec2 L_textCords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 textCords;

void main()
{
	gl_Position =  projection * view * model* vec4(L_position, 1.0f);
	textCords = vec2(L_textCords.x, 1.0f - L_textCords.y);
}