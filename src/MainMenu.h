#pragma once

#include "GameObject.h"
#include "core/Text.h"


class Menu : public GameObject {


public:
	Shader* titleTextShader;
	Shader* textShader;
public:
	Menu();
	~Menu()
	{
		delete titleTextShader;
		delete textShader;
	}
	virtual void Draw(Text& textRenderer, float dt);
};