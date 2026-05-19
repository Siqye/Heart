#version 330 core
out vec4 fragColor;

in vec4 colour;

void main()
{
	fragColor = colour;
}