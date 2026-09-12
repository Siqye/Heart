#version 330 core 

layout(location = 0) in vec4 vertex;

out vec2 textureCoords;

void main()
{
	gl_Position = vec4(vertex.xy, 0.0, 1.0);
	textureCoords = vec2(vertex[2], vertex[3]);
}