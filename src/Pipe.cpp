#include "Pipe.h"

Pipe::Pipe(bool upsideDown, glm::vec2 position)
	: GameObject("./src/assets/pipe-red.png", "./src/shaders/pipe_vertex.glsl", "./src/shaders/pipe_fragment.glsl",
		position, glm::vec2(60.0f, 400.0f), 0.f), m_Upsidedown(upsideDown)
{
	m_Velocity = glm::vec2({-200.f, 0.0f});
	m_InitialHeight = m_Position.y;
}

void Pipe::Draw(Renderer& renderer) 
{
	m_Shader->Use();
	m_Shader->SetInteger(m_Upsidedown, "upsideDown");
	renderer.Draw(*m_Shader, *m_Texture, m_Position, m_Size, m_Rotation);
}

void Pipe::Move(float dt, int& score)
{
	m_Position += m_Velocity * dt;
	if (m_Position.x + m_Size.x <= 40.0f && !m_Scored) {
		m_Scored = true;
		score += 1;
	}
}

void Pipe::ResetPipe(float heightOffset)
{
	m_Scored = false;
	m_Position.x = 800.0f;
	m_Position.y = m_InitialHeight + heightOffset;
}