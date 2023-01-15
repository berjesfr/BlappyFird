#version 450 core
layout (location = 0) in vec4 aPos;

out vec2 textureCoords;

uniform mat4 model;
uniform mat4 projection;

void main() {
	gl_Position =  projection * model * vec4(aPos.xy, 0.0, 1.0);
	textureCoords = aPos.zw;
}