#pragma once
#include <glad/glad.h> 

#include "Renderer.h"
#include "core/Shader.h"

class GameObject
{
public:
	Shader* m_Shader = nullptr;
	Texture2D* m_Texture = nullptr;
	glm::vec2 m_Position, m_Size, m_Velocity;
	float m_Rotation;
public:
	GameObject();
	GameObject(const char* texturePath, const char* vertexPath, const char* fragmentPath, glm::vec2 position, glm::vec2 size, float rotation);
	~GameObject() { delete m_Shader; delete m_Texture; }
	void SetupProjection(unsigned int width, unsigned int height)
	{
		m_Shader->Use();
		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
		m_Shader->SetMatrix4(projection, "projection");
	}
	virtual void Draw(Renderer& renderer);
};
