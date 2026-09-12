#version 330 core  

in vec2 textureCoords;
out vec4 fragColor;

uniform vec4 textColor;
uniform sampler2D textTexture;

void main() {
	fragColor = vec4(textColor.rgb, textColor.a * texture(textTexture, textureCoords).r);
}