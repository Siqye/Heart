#include "packetrenderer.hpp"
#include "staticsprite.hpp"
#include "texture.hpp"
#include <string>

namespace heartCore { 	namespace graphics {

	PacketRenderer::PacketRenderer() {
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
		glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));
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

	PacketRenderer::~PacketRenderer() {}

	void PacketRenderer::submit(const StaticSprite* sprite) {
		const maths::vec3& position = sprite->getPosition();
		const maths::vec4& col = sprite->getColor();
		const maths::vec3& size = sprite->getSize();
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

		int r = col.x * 255.0f;
		int g = col.y * 255.0f;
		int b = col.z * 255.0f;
		int a = col.w * 255.0f;

		color = a << 24 | b << 16 | g << 8 | r;
		
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

	void PacketRenderer::begin() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		m_dataBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void PacketRenderer::draw() {
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

	void PacketRenderer::end() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void PacketRenderer::submitText(std::string text, float scale, maths::vec3 position, maths::vec4 col, Font font) {
		texture_atlas_t* textAtlas = font.getAtlas();
		texture_font_t* textFont = font.getFont();
		
		bool found = false;
		float textureSlot = 0.0f;
		float x = position.x;
		float scaleX = WINDOW_WIDTH / scale;
		float scaleY = WINDOW_HEIGHT / scale;

		for (int i = 0; i < m_textureSlots.size(); i++)
		{
			if (m_textureSlots[i] == textAtlas->id) {
				textureSlot = (float)(i + 1);
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
			m_textureSlots.push_back(textAtlas->id);
			textureSlot = (float)(m_textureSlots.size());
		}

		int r = col.x * 255;
		int g = col.y * 255;
		int b = col.z * 255;
		int a = col.w * 255;

		unsigned int color = a << 24 | b << 16 | g << 8 | r;

		for (int i = 0; i < text.size();i++) {

			const char* c = &text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(textFont, c);
			loadChar(textAtlas);

			if (glyph != NULL) {
				if (i > 0) {
					float kerningX = texture_glyph_get_kerning(glyph, &text[i - 1]);
					x += kerningX / scaleX;
				}

				float x0 = x + glyph->offset_x / scaleX;
				float y0 = position.y - (glyph->height - glyph->offset_y) / scaleY; //+ //glyph->offset_y / scaleY;
				float x1 = x0 + glyph->width / scaleX;
				float y1 = y0 + glyph->height / scaleY;

				float s0 = glyph->s0;
				float t0 = glyph->t0;
				float s1 = glyph->s1;
				float t1 = glyph->t1;

				m_dataBuffer->vertex = *m_transformBack * maths::vec3(x0, y0, 0);
				m_dataBuffer->tc = maths::vec2(s0, t1);
				m_dataBuffer->tid = textureSlot;
				m_dataBuffer->color = color;
				m_dataBuffer++;

				m_dataBuffer->vertex = *m_transformBack * maths::vec3(x0, y1, 0);
				m_dataBuffer->tc = maths::vec2(s0, t0);
				m_dataBuffer->tid = textureSlot;
				m_dataBuffer->color = color;
				m_dataBuffer++;

				m_dataBuffer->vertex = *m_transformBack * maths::vec3(x1, y1, 0);
				m_dataBuffer->tc = maths::vec2(s1, t0);
				m_dataBuffer->tid = textureSlot;
				m_dataBuffer->color = color;
				m_dataBuffer++;

				m_dataBuffer->vertex = *m_transformBack * maths::vec3(x1, y0, 0);
				m_dataBuffer->tc = maths::vec2(s1, t1);
				m_dataBuffer->tid = textureSlot;
				m_dataBuffer->color = color;
				m_dataBuffer++;

				m_indexCount += 6;

				x += glyph->advance_x / scaleX;
			}
		}
	}
} }