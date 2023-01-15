#include "Game.h"

irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

Game::Game()
{

}

void Game::Init(unsigned int width, unsigned int height)
{
	m_Width = width;
	m_Height = height;
	state = GameState::GAME_MENU;
	renderer = new Renderer();
	birb = new Birb();
	background = new GameObject("./src/assets/background-night.png", "./src/shaders/background_vertex.glsl", "./src/shaders/background_fragment.glsl", {0.f, 0.f}, {800.f, 600.f}, 0.0f);
	ground = new GameObject("./src/assets/base.png", "./src/shaders/background_vertex.glsl", "./src/shaders/background_fragment.glsl", {0.f, 0.f}, {800.f, 100.f}, 0.0f);
	background->SetupProjection(width, height);
	ground->SetupProjection(width, height);
	birb->SetupProjection(width, height);

	pipeManager = new PipeManager(width, height);
	textShader = new Shader("./src/shaders/font_vertex.glsl", "./src/shaders/font_fragment.glsl");
	textRenderer = new Text();
	menu = new Menu();
}

void Game::Update(float dt, float time)
{
	if (state == GameState::GAME_RUNNING) {
		if (keys[GLFW_KEY_SPACE] && !keysProcessed[GLFW_KEY_SPACE]) {
			birb->Fly(dt, true);
			keysProcessed[GLFW_KEY_SPACE] = true;
			engine->play2D("sounds/wing.ogg");
		} else {
			birb->Fly(dt, false);
		}
		pipeManager->MovePipes(dt, *engine);
		if (pipeManager->CheckCollisions(*birb)) {
			engine->play2D("sounds/hit.ogg");
			engine->play2D("sounds/die.ogg");
			state = GameState::GAME_END;
		}
	}
	if (state == GameState::GAME_MENU) {
		if (keys[GLFW_KEY_SPACE] && !keysProcessed[GLFW_KEY_SPACE]) {
			keysProcessed[GLFW_KEY_SPACE] = true;
			state = GameState::GAME_RUNNING;
		}
	}
	if (state == GameState::GAME_END) {
		if (keys[GLFW_KEY_SPACE] && !keysProcessed[GLFW_KEY_SPACE]) {
			keysProcessed[GLFW_KEY_SPACE] = true;
			ResetGame();
		}
	}
}

void Game::Draw(float dt)
{
	background->Draw(*renderer);
	pipeManager->DrawPipes(*renderer);
	ground->Draw(*renderer);
	birb->Draw(*renderer);
	if (state == GameState::GAME_MENU) {
		menu->Draw(*textRenderer, glfwGetTime());
	} else if (state == GameState::GAME_RUNNING) {
		textRenderer->RenderText2("Score: " + std::to_string(pipeManager->score/2), *textShader, 10.f, 560.f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	} else {
		textRenderer->RenderText("Press SPACEBAR to restart or ESCAPE to exit", *textShader, 120.f, 320.f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		textRenderer->RenderText2("Your score: " + std::to_string(pipeManager->score / 2), *textShader, 320.f, 120.f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	}
}

void Game::ResetGame()
{
	delete birb; 
	delete pipeManager;
	birb = new Birb();
	pipeManager = new PipeManager(m_Width, m_Height);
	birb->SetupProjection(m_Width, m_Height);
	state = GameState::GAME_RUNNING;
}