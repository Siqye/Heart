#version 330 core
layout (location = 0) out vec4 color;

in DATA {
	vec4 color;
	vec4 position;
	vec2 tc;
} fs_in;

uniform sampler2D tex;

void main()
{
	color = fs_in.color;
	color = texture(tex, fs_in.tc);
}