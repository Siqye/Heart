#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tc;
layout(location = 2) in float tid;
layout(location = 3) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 ml_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);

out DATA {
  vec4 position;
  vec2 tc;
  float tid;
  vec4 color;
}
vs_out;

void main() {
  gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
  vs_out.position = position;
  vs_out.tc = tc;
  vs_out.tid = tid;
  vs_out.color = color;
}