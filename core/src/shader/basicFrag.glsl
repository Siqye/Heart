#version 330 core
layout (location = 0) out vec4 color;

in DATA {
	vec4 color;
	vec4 position;
	vec2 tc;
} fs_in;

uniform vec2 ligth_pos;
uniform sampler2D tex;

void main()
{
	float intensity = 0.3 / length(fs_in.position.xy + ligth_pos);
	color = fs_in.color * intensity;
	color += texture(tex, fs_in.tc);
}