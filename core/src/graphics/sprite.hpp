#pragma once
#include "../maths/maths.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include <vector>
#include <glew.h>

namespace heartCore { namespace graphics {

	struct VertexData {
		maths::vec3 vertex;
		maths::vec2 tc;
		float tid;
		unsigned int color;
	};

	class Sprite {
	private:
		inline void setTC() {
			m_texCoords.push_back(maths::vec2(0, 0));
			m_texCoords.push_back(maths::vec2(0, 1));
			m_texCoords.push_back(maths::vec2(1, 1));
			m_texCoords.push_back(maths::vec2(1, 0));	
		}
	protected:
		Sprite() : m_texture(nullptr) { setTC(); }

		maths::vec2 m_size;
		maths::vec4 m_color;
		std::vector<maths::vec2> m_texCoords;
		maths::vec3 m_position;
		Texture* m_texture;
	public:
		Sprite(double x, double y, double width, double height, maths::vec4 color) 
			:	m_position(maths::vec3(x,y,0)), m_size(maths::vec2(width,height)), m_color(color),
			m_texture(nullptr)
		{ setTC(); }


		Sprite(double x, double y, double width, double height, Texture* texture)
			: m_position(maths::vec3(x, y, 0)), m_size(maths::vec2(width, height)), m_color(maths::vec4(1,0,1,1)), 
			m_texture(texture)
		{ setTC(); }

		virtual void submit(Renderer* renderer) { renderer->submit(this); }

		inline const maths::vec2& getSize() const { return m_size; }
		inline const maths::vec3& getPosition() const { return m_position; }
		inline const maths::vec4& getColor() const { return m_color; }
		inline const std::vector<maths::vec2>& getTC() const { return m_texCoords; }
		inline const GLuint getTID() const { return m_texture == nullptr ? 0 : m_texture->getTID(); }
	};
} }