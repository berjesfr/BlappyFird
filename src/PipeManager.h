#pragma once

#include <iostream>
#include <tuple>
#include <irrklang/irrKlang.h>
#include <vector>
#include "Pipe.h"
#include "Birb.h"


struct PipePair
{
	Pipe* pipeDown;
	Pipe* pipeUp;

	PipePair()
	{
	}
	~PipePair()
	{
		delete pipeDown;
		delete pipeUp;
	}
	void InitPipes(glm::vec2 positionDown, glm::vec2 positionUp, unsigned int width, unsigned int height)
	{
		pipeDown = new Pipe(false, positionDown);
		pipeUp = new Pipe(true, positionUp);
		pipeDown->SetupProjection(width, height);
		pipeUp->SetupProjection(width, height);
	}
};

class PipeManager
{
public:
	int score = 0;
public:
	PipeManager(unsigned int width, unsigned int height);
	~PipeManager() = default;
	void DrawPipes(Renderer& renderer);
	void MovePipes(float dt, irrklang::ISoundEngine& soundEngine);
	bool CheckCollisions(Birb& player);
private:
	PipePair m_PipeList[3];
};