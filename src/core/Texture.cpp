#include "Texture.h"

Texture2D::Texture2D()
	: m_Tex(0)
{}

void Texture2D::SetupTexture(std::string_view texturePath)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_Tex);
	glTextureParameteri(m_Tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_Tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(m_Tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_Tex, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width, height, nrChannels;
	unsigned char* dataTex = stbi_load(texturePath.data(), &width, &height, &nrChannels, 0);

	if (dataTex) {
		GLenum format = 0;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		glTextureStorage2D(m_Tex, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(m_Tex, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, dataTex);
	} else {
		std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(dataTex);
}

void Texture2D::BindUnit() const
{
	glBindTextureUnit(1, m_Tex);
}