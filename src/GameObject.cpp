#include "GameObject.h"


GameObject::GameObject()
	: m_Position({0.f, 0.f}), m_Size({1.f, 1.f}), m_Rotation(0.0f), m_Velocity({0.0f, 10.0f})
{

}
GameObject::GameObject(const char* texturePath, const char* vertexPath, const char* fragmentPath, glm::vec2 position, glm::vec2 size, float rotation)
	: m_Position(position), m_Size(size), m_Rotation(rotation), m_Velocity({0.0f, -600.0f})
{
	m_Shader = new Shader(vertexPath, fragmentPath);
	m_Texture = new Texture2D();
	m_Texture->SetupTexture(texturePath);
}

void GameObject::Draw(Renderer& renderer)
{
	renderer.Draw(*m_Shader, *m_Texture, m_Position, m_Size, m_Rotation);
}