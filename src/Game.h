#pragma once
#include <vector>
#include <string>
#include <irrklang/irrKlang.h>

#include "core/Text.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Birb.h"
#include "Pipe.h"
#include "PipeManager.h"
#include "MainMenu.h"

enum class GameState
{
	GAME_MENU,
	GAME_RUNNING,
	GAME_END
};

class Game
{
public:
	bool keys[1024];
	bool keysProcessed[1024];
	GameState state;
	Birb* birb;
	PipeManager* pipeManager;
	GameObject* background;
	GameObject* ground;
	Renderer* renderer;
	Text* textRenderer;
	Shader* textShader;
	Menu* menu;

public:
	Game();
	~Game() { delete renderer; delete birb; delete pipeManager; delete background; delete ground; }
	void Init(unsigned int width, unsigned int height);
	void Update(float dt, float time);
	void Draw(float dt);
	void ResetGame();

private:
	unsigned int m_Width;
	unsigned int m_Height;
};