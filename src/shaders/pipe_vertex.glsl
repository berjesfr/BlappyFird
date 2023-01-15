#version 450 core

layout (location = 0) in vec4 aPos;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform bool upsideDown;

void main() {
	gl_Position = projection * model * vec4(aPos.xy, 0.0, 1.0);
	if (upsideDown) {
		TexCoords = -aPos.zw;
	} else {
		TexCoords = aPos.zw;
	}
}