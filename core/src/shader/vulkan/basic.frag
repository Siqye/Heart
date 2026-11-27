#version 450
layout(location = 0) in vec4 v_position;
layout(location = 1) in vec2 v_tc;
layout(location = 2) in float v_tid;
layout(location = 3) in vec4 v_color;

layout(set = 0, binding = 1) uniform sampler2D textures[32];

layout(location = 0) out vec4 color;

void main() {
  vec4 texColor = v_color;
  if (v_tid > 0.0) {
	int tid = int(v_tid - 0.5);
	texColor = v_color * texture(textures[tid], v_tc);
  }
  color = texColor;
}
