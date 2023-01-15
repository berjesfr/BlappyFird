#version 450 core

in vec2 textureCoords;
out vec4 fragmentColor;

uniform sampler2D tex;
//uniform int layer;

void main() {
	vec4 texColor = texture(tex, textureCoords);
	if(texColor.a < 0.5)
		discard;
	fragmentColor = texColor;
}