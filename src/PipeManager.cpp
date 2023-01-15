#include "PipeManager.h"

PipeManager::PipeManager(unsigned int width, unsigned int height)
{
	m_PipeList[0].InitPipes({400.f, -150.0f}, {400.f, 400.0f}, width, height);
	m_PipeList[1].InitPipes({700.f, -150.0f}, {700.f, 400.0f}, width, height);
	m_PipeList[2].InitPipes({1000.f, -150.0f}, {1000.f, 400.0f}, width, height);
}

void PipeManager::DrawPipes(Renderer& renderer)
{
	for (int i = 0; i < 3; i++) {
		m_PipeList[i].pipeDown->Draw(renderer);
		m_PipeList[i].pipeUp->Draw(renderer);
	}
}

void PipeManager::MovePipes(float dt, irrklang::ISoundEngine& soundEngine)
{
	for (int i = 0; i < 3; i++) {
		int previousScore = this->score;
		m_PipeList[i].pipeDown->Move(dt, this->score);
		m_PipeList[i].pipeUp->Move(dt, this->score);
		if (this->score > previousScore) {
			soundEngine.play2D("./sounds/point.ogg");
		}
		if (m_PipeList[i].pipeDown->m_Position.x + m_PipeList[i].pipeDown->m_Size.x <= 0.0f) {
			float heightOffset = (rand() % 201) - 100;
			m_PipeList[i].pipeDown->ResetPipe(heightOffset);
			m_PipeList[i].pipeUp->ResetPipe(heightOffset);
		}
	}
}

bool PipeManager::CheckCollisions(Birb& player)
{
	for (int i = 0; i < 3; i++) {
		bool collisionXPipe1 = player.m_Position.x <= m_PipeList[i].pipeDown->m_Position.x + m_PipeList[i].pipeDown->m_Size.x && player.m_Position.x + player.m_Size.x >= m_PipeList[i].pipeDown->m_Position.x;
		bool collisionXPipe2 = player.m_Position.x <= m_PipeList[i].pipeUp->m_Position.x + m_PipeList[i].pipeUp->m_Size.x && player.m_Position.x + player.m_Size.x >= m_PipeList[i].pipeUp->m_Position.x;

		bool collisionYPipe1 = player.m_Position.y <= m_PipeList[i].pipeDown->m_Position.y + m_PipeList[i].pipeDown->m_Size.y && player.m_Position.y + player.m_Size.y >= m_PipeList[i].pipeDown->m_Position.y;
		bool collisionYPipe2 = player.m_Position.y <= m_PipeList[i].pipeUp->m_Position.y + m_PipeList[i].pipeUp->m_Size.y && player.m_Position.y + player.m_Size.y >= m_PipeList[i].pipeUp->m_Position.y;
		
		if ((collisionXPipe1 && collisionYPipe1) || (collisionXPipe2 && collisionYPipe2)) {
			return true;
		}
	}
	return false;
}