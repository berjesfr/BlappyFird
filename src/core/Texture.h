#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string_view>
#include <iostream>
class Texture2D
{
public:
	Texture2D();
	~Texture2D() { glDeleteTextures(1, &m_Tex); }
	void SetupTexture(std::string_view texturePath);
	void BindUnit() const;
private:
	unsigned int m_Tex;
};