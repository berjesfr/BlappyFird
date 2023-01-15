#version 450 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D tex;

void main() {
	vec4 color = texture(tex, TexCoords);
	if (color.a < 0.2) {
		discard;
	}
	FragColor = color;
}
