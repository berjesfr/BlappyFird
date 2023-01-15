#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Texture.h"
#include "core/Shader.h"
class Renderer
{
public:
public:
	Renderer();
	~Renderer() = default;
	void Draw(Shader& shader, Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotation);
private:
	unsigned int m_VAO;
};