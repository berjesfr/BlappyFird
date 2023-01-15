#include "Birb.h"


Birb::Birb()
	: GameObject("./src/assets/bluebird-midflap.png", "./src/shaders/birb_vertex.glsl", "./src/shaders/birb_fragment.glsl",
		glm::vec2(40.f, 300.f), glm::vec2(30.0f, 30.0f), 0.f)
{
}

void Birb::Draw(Renderer& renderer)
{
	renderer.Draw(*m_Shader, *m_Texture, m_Position, m_Size, m_Rotation);
}

void Birb::Fly(float dt, bool isFlying)
{
	m_FlyTime = isFlying && m_FlyTime <= 0.0f ? 0.2f : m_FlyTime;
	m_Acceleration += 10.f * m_ElapsedTime;
	if (m_Acceleration >= 500.f) {
		m_Acceleration = 500.f;
	}
	if (m_FlyTime > 0.0f) {
		m_ElapsedTime = 0.0f;
		m_Acceleration = 0.0f;
		m_FlyTime -= dt;
		this->m_Velocity = glm::vec2(0.0f, 400.f);
	} else {
		this->m_Velocity = glm::vec2(0.0f, -m_Acceleration);
	}
	m_ElapsedTime += dt;
	m_Rotation = m_Velocity.y * 0.04f;
	this->m_Position += this->m_Velocity * dt;
	if (this->m_Position.y >= 600.0f) {
		this->m_Position.y = 600.0f;
	}
	if (this->m_Position.y <= 100.0f) {
		this->m_Position.y = 100.0f;
	}
}