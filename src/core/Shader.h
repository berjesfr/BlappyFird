#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int ID;
	Shader() = default;
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader() {
		glDeleteProgram(ID);
	}
	void Use();
	void SetMatrix4(glm::mat4& matrix, const char* name);
	void SetInteger(unsigned int value, const char* name);
	void SetFloat(float value, const char* name);
};

#endif