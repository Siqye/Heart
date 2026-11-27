#version 450
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

layout(set = 0, binding = 0) uniform Camera {
  mat4 projection;
  mat4 view;
} camera;

layout(push_constant) uniform Model {
  mat4 model;
} pc;

layout(location = 0) out vec4 v_position;
layout(location = 1) out vec4 v_color;

void main() {
  gl_Position = camera.projection * camera.view * pc.model * position;
  v_position = position;
  v_color = color;
}
