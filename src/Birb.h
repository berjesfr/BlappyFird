#pragma once
#include "GameObject.h"
#include "core/Texture.h"

class Birb : public GameObject {

public:
	Birb();
	void Fly(float dt, bool isFlying = false);
	virtual void Draw(Renderer& renderer);
private:
	float m_FlyTime = 0.0f;
	float m_ElapsedTime = 0.0f;
	float m_Acceleration = 0.0f;
};