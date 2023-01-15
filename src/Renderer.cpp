#include "Renderer.h"

Renderer::Renderer()
{
	unsigned int VBO;
	float vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glCreateVertexArrays(1, &m_VAO);
	glCreateBuffers(1, &VBO);
	
	glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexArrayAttrib(m_VAO, 0);
	glVertexArrayAttribBinding(m_VAO, 0, 0);
	glVertexArrayAttribFormat(m_VAO, 0, 4, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayVertexBuffer(m_VAO, 0, VBO, 0, 4 * sizeof(float));

}

void Renderer::Draw(Shader& shader, Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotation)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	shader.Use();
	shader.SetMatrix4(model, "model");
	shader.SetInteger(1, "tex");
	texture.BindUnit();
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}