#version 450 core

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 projection;
uniform float uTime;

void main() {
	vec4 temp = vec4(vertex.xy, 0.0, 1.0);
	float displacement = 15.0 * sin(uTime + 2 * vertex.x);
	gl_Position = projection * vec4(temp.x, temp.y+displacement, temp.zw);
	TexCoords = vertex.zw;
}
