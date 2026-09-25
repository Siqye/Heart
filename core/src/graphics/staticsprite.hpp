#pragma once
#include "../maths/maths.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include <vector>
#include <glew.h>

namespace heartCore {
	namespace graphics {

		struct VertexData {
			maths::vec3 vertex;
			maths::vec2 tc;
			float tid;
			unsigned int color;
		};

		class StaticSprite {
		protected:
			inline void setTC() {
				m_texCoords.push_back(maths::vec2(0, 0));
				m_texCoords.push_back(maths::vec2(0, 1));
				m_texCoords.push_back(maths::vec2(1, 1));
				m_texCoords.push_back(maths::vec2(1, 0));
			}

			maths::vec3 m_size;
			maths::vec4 m_color;
			std::vector<maths::vec2> m_texCoords;
			maths::vec3 m_position;
			Texture* m_texture;
		public:
			StaticSprite() : m_texture(nullptr) { setTC(); }
			StaticSprite(maths::vec3 position, maths::vec3 size, maths::vec4 color)
				: m_position(position), m_size(size), m_color(color), m_texture(nullptr)
			{setTC();}

			StaticSprite(maths::vec3 position, maths::vec3 size, Texture* texture)
				: m_position(position), m_size(size), m_color(maths::vec4(1, 1, 1, 1)),
				m_texture(texture)
			{setTC();}

			inline ~StaticSprite() 
			{
				delete m_texture;
			}

			virtual void submit(Renderer* renderer) const { renderer->submit(this); }

			inline const maths::vec3& getSize() const { return m_size; }
			inline const maths::vec3& getPosition() const { return m_position; }
			inline const maths::vec4& getColor() const { return m_color; }
			inline const std::vector<maths::vec2>& getTC() const { return m_texCoords; }
			inline const GLuint getTID() const { return m_texture == nullptr ? 0 : m_texture->getTID(); }
		};
	}
}