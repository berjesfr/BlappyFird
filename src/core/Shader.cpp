#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {


	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vertexShaderSource = vertexCode.c_str();

	const char* fragmentShaderSource = fragmentCode.c_str();


	unsigned int vertexShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShaderID;
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShaderID);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderID);

	int vertexSuccess;
	char vertexInfoLog[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexSuccess);
	if (!vertexSuccess) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, vertexInfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertexInfoLog << std::endl;
	}

	int fragmentSuccess;
	char fragmentInfoLog[512];
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fragmentSuccess);
	if (!fragmentSuccess) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, fragmentInfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentInfoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);

	int programSuccess;
	char programInfoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &programSuccess);
	if (!programSuccess) {
		glGetProgramInfoLog(ID, 512, NULL, programInfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << programInfoLog << std::endl;
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::Use() {
	glUseProgram(ID);
}

void Shader::SetMatrix4(glm::mat4& matrix, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetInteger(unsigned int value, const char* name)
{
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetFloat(float value, const char* name)
{
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

