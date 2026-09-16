#include "renderer.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include <string>

namespace heartCore { 	namespace graphics {

	Renderer::Renderer() {
		m_transformStack.push_back(maths::mat4::identity());
		m_transformBack = &m_transformStack.back();

		m_indexCount = 0;

		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::vertex));
		glVertexAttribPointer(TEXTURE_COORD_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tc));
		glVertexAttribPointer(TEXTURE_ID_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tid));
		glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_INT, GL_TRUE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));
		glEnableVertexAttribArray(VERTEX_INDEX); glEnableVertexAttribArray(TEXTURE_COORD_INDEX); 
		glEnableVertexAttribArray(TEXTURE_ID_INDEX); glEnableVertexAttribArray(COLOR_INDEX);


		GLushort indecies[INDICIES_SIZE];

		int o = 0;
		for (int i = 0; i < INDICIES_SIZE; i+=6, o+=4) {
			indecies[i]   = o;
			indecies[i+1] = o+1;
			indecies[i+2] = o+2;

			indecies[i+3] = o+2;
			indecies[i+4] = o+3;
			indecies[i+5] =	o;
		}

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICIES_SIZE * sizeof(GLushort), indecies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Renderer::~Renderer() {}

	void Renderer::submit(const Sprite* sprite) {
		const maths::vec3& position = sprite->getPosition();
		const maths::vec4& col = sprite->getColor();
		const maths::vec2& size = sprite->getSize();
		const std::vector<maths::vec2>& tc = sprite->getTC();
		const GLuint texID = sprite->getTID();

		unsigned int color = 0;
		float textureSlot = 0.0f;

		if (texID > 0) {
			bool found = false;
			for (int i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == texID) {
					textureSlot = (float)(i+1);
					found = true;
					break;
				}
			}
			if (!found) {
				if (m_textureSlots.size() >= 32) {
					end();
					draw();
					begin();
				}
				m_textureSlots.push_back(texID);
				textureSlot = (float)(m_textureSlots.size());
			}
		}
		else {
			int r = col.x * 255;
			int g = col.y * 255;
			int b = col.z * 255;
			int a = col.w * 255;

			color = a << 24 | b << 16 | g << 8 | r;
		}
		m_dataBuffer->vertex = *m_transformBack * position;
		m_dataBuffer->tc = tc[0];
		m_dataBuffer->tid = textureSlot;
		m_dataBuffer->color = color;
		m_dataBuffer++;

		m_dataBuffer->vertex = *m_transformBack * maths::vec3(position.x, position.y + size.y, position.z);
		m_dataBuffer->tc = tc[1];
		m_dataBuffer->tid = textureSlot;
		m_dataBuffer->color = color;
		m_dataBuffer++;

		m_dataBuffer->vertex = *m_transformBack * maths::vec3(position.x + size.x, position.y + size.y, position.z);
		m_dataBuffer->tc = tc[2];
		m_dataBuffer->tid = textureSlot;
		m_dataBuffer->color = color;
		m_dataBuffer++;

		m_dataBuffer->vertex = *m_transformBack * maths::vec3(position.x + size.x, position.y, position.z);
		m_dataBuffer->tc = tc[3];
		m_dataBuffer->tid = textureSlot;
		m_dataBuffer->color = color;
		m_dataBuffer++;

		m_indexCount += 6;
	}

	void Renderer::begin() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		m_dataBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	void Renderer::draw() {
		for (int i = 0; i < m_textureSlots.size();i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
		}

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_indexCount = 0;
	}
	void Renderer::end() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::push(const maths::mat4& matrix, bool override) {

		if (override) m_transformStack.push_back(matrix);

		else m_transformStack.push_back(m_transformStack.back() * matrix);

		m_transformBack = &m_transformStack.back();
	}
	void Renderer::pop() {
		if (m_transformStack.size() > 1) m_transformStack.pop_back();

		m_transformBack = &m_transformStack.back();
	}
	void Renderer::drawText(const std::string text, Texture fontTex, texture_font_t* font, maths::vec3 position, maths::vec4 col) {
		maths::vec2 scale = maths::vec2(1,2);

		float x = position.x;

		int r = col.x * 255;
		int g = col.y * 255;
		int b = col.z * 255;
		int a = col.w * 255;

		unsigned int color = a << 24 | b << 16 | g << 8 | r;


		float ts = 0.0f;
		for (int i = 0; i < text.length(); i++)
		{
			
			bool found = false;
			for (int i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == fontTex.getTID())
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_textureSlots.size() >= 10000)
				{
					end();
					draw();
					begin();
				}
				m_textureSlots.push_back(fontTex.getTID());
				ts = (float)(m_textureSlots.size());
			}

			char c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(font, &c);
			if (glyph)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
					x += kerning / scale.x;
				}

				float x0 = x + glyph->offset_x / scale.x;
				float y0 = position.y + glyph->offset_y / scale.y;
				float x1 = x0 + glyph->width / scale.x;
				float y1 = y0 - glyph->height / scale.y;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				m_dataBuffer->vertex = *m_transformBack * maths::vec3(x0, y0, 0);
				m_dataBuffer->tc = maths::vec2(u0, v0);
				m_dataBuffer->tid = ts;
				m_dataBuffer->color = color;
				m_dataBuffer++;

				m_dataBuffer->vertex = *m_transformBack * maths::vec3(x0, y1, 0);
				m_dataBuffer->tc = maths::vec2(u0, v1);
				m_dataBuffer->tid = ts;
				m_dataBuffer->color = color;
				m_dataBuffer++;

				m_dataBuffer->vertex = *m_transformBack * maths::vec3(x1, y1, 0);
				m_dataBuffer->tc = maths::vec2(u1, v1);
				m_dataBuffer->tid = ts;
				m_dataBuffer->color = color;
				m_dataBuffer++;

				m_dataBuffer->vertex = *m_transformBack * maths::vec3(x1, y0, 0);
				m_dataBuffer->tc = maths::vec2(u1, v0);
				m_dataBuffer->tid = ts;
				m_dataBuffer->color = color;
				m_dataBuffer++;

				m_indexCount += 6;

				x += glyph->advance_x / scale.x;
			}
		}
	}
} }