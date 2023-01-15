#version 450 core

in vec2 TexCoords;
out vec4 Color;

uniform sampler2D tex;
uniform vec3 textColor;

void main(){
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, TexCoords).r);
	if (sampled.w < 0.5) {
		discard;
	}
	Color = sampled * vec4(textColor, 1.0);
}
