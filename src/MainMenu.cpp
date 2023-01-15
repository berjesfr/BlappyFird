#include "MainMenu.h"


Menu::Menu()
{
	titleTextShader = new Shader("./src/shaders/title_text_vertex.glsl", "./src/shaders/menu_text_fragment.glsl");
	textShader = new Shader("./src/shaders/menu_text_vertex.glsl", "./src/shaders/menu_text_fragment.glsl");
}

void Menu::Draw(Text& textRenderer, float elapsedTime)
{
	titleTextShader->Use();
	titleTextShader->SetFloat(elapsedTime, "uTime");
	textRenderer.RenderText("Blappy Fird", *titleTextShader, 200.f, 400.f, 3.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	textRenderer.RenderText("Press SPACEBAR to start or ESCAPE to exit", *textShader, 120.f, 320.f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}