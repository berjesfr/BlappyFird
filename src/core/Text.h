#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string_view>
#include <iostream>
#include "Shader.h"
#include FT_FREETYPE_H

struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	uint32_t Advance;
};
class Text {

public:
	Text();
	~Text();
	void LoadCharacters();
	void SetupBuffers();
	void RenderText(std::string_view text, Shader& shader, float x, float y, float scale, glm::vec3 color);
	void RenderText2(std::string_view text, Shader& shader, float x, float y, float scale, glm::vec3 color);

private:
	GLuint m_VAO, m_VBO;
	std::map<char, Character> m_Characters;
	std::map<char, Character> m_CharactersSecondary;
};