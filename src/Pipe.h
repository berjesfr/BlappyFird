#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameObject.h"

class Pipe: public GameObject {

public:
	Pipe(bool upsideDown, glm::vec2 position);
	virtual void Draw(Renderer& renderer);
	void Move(float dt, int& score);
	void ResetPipe(float heightOffset);
private:
	bool m_Scored = false;
	float m_InitialHeight = 0.0f;
	bool m_Upsidedown = false;
};