#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 ml_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);

out DATA {
    vec4 color;
    vec4 position;
    vec2 tc;
} vs_out;

void main()
{
    vs_out.color = color;
    vs_out.position = position;
    vs_out.tc = tc;
    gl_Position = pr_matrix * ml_matrix * vw_matrix * position;
}