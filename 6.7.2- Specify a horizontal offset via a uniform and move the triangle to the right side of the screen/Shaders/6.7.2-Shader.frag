#version 330 core

in vec4 pos;

out vec4 color;

void main()
{
	color = pos + 0.25f;	
}