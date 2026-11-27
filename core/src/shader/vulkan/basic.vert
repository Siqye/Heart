#version 450
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tc;
layout(location = 2) in float tid;
layout(location = 3) in vec4 color;

layout(set = 0, binding = 0) uniform Camera {
  mat4 projection;
  mat4 view;
} camera;

layout(push_constant) uniform Model {
  mat4 model;
} pc;

layout(location = 0) out vec4 v_position;
layout(location = 1) out vec2 v_tc;
layout(location = 2) out float v_tid;
layout(location = 3) out vec4 v_color;

void main() {
  gl_Position = camera.projection * camera.view * pc.model * position;
  v_position = position;
  v_tc = tc;
  v_tid = tid;
  v_color = color;
}
