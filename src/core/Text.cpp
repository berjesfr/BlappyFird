#include "Text.h"


Text::Text()
{
	LoadCharacters();
	SetupBuffers();
}

Text::~Text()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
	for (int i = 0; i < m_Characters.size(); i++) {
		glDeleteTextures(1, &m_Characters[i].TextureID);
	}
}

void Text::LoadCharacters()
{
	FT_Library ft;
	FT_Face face;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	if (FT_New_Face(ft, ".\\fonts\\FlappyBirdy.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	FT_GlyphSlot slot = face->glyph; // <-- This is new
	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		FT_Render_Glyph(slot, FT_RENDER_MODE_SDF); // <-- And this is new
		GLuint tex;
		glCreateTextures(GL_TEXTURE_2D, 1, &tex);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureStorage2D(tex, 1, GL_RGBA8, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		glTextureSubImage2D(tex, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		Character character = {
			tex,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		m_Characters.insert(std::pair<char, Character>(c, character));
	}

	if (FT_New_Face(ft, ".\\fonts\\corbel.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	slot = face->glyph;
	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		FT_Render_Glyph(slot, FT_RENDER_MODE_SDF);
		GLuint tex;
		glCreateTextures(GL_TEXTURE_2D, 1, &tex);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureStorage2D(tex, 1, GL_RGBA8, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		glTextureSubImage2D(tex, 0, 0, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		Character character = {
			tex,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		m_CharactersSecondary.insert(std::pair<char, Character>(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void Text::SetupBuffers()
{
	glCreateVertexArrays(1, &m_VAO);
	glCreateBuffers(1, &m_VBO);

	glNamedBufferData(m_VBO, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexArrayAttrib(m_VAO, 0);
	glVertexArrayAttribBinding(m_VAO, 0, 0);
	glVertexArrayAttribFormat(m_VAO, 0, 4, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, 4 * sizeof(float));
}

void Text::RenderText(std::string_view text, Shader& shader, float x, float y, float scale, glm::vec3 color) 
{
	shader.Use();
	glBindVertexArray(m_VAO);
	glm::mat4 projection = glm::ortho(0.0f, 800.f, 0.f, 600.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	
	std::string_view::const_iterator c;
	for (c = text.begin(); c < text.end(); c++) {
		Character ch = m_Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTextureUnit(0, ch.TextureID);
		glUniform1i(glGetUniformLocation(shader.ID, "tex"), 0);
		glNamedBufferSubData(m_VBO, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
}

void Text::RenderText2(std::string_view text, Shader& shader, float x, float y, float scale, glm::vec3 color)
{
	shader.Use();
	glBindVertexArray(m_VAO);
	glm::mat4 projection = glm::ortho(0.0f, 800.f, 0.f, 600.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	std::string_view::const_iterator c;
	for (c = text.begin(); c < text.end(); c++) {
		Character ch = m_CharactersSecondary[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTextureUnit(0, ch.TextureID);
		glUniform1i(glGetUniformLocation(shader.ID, "tex"), 0);
		glNamedBufferSubData(m_VBO, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
}