#include "animatedspite.hpp"

namespace heartCore { namespace graphics {
	AnimatedSprite::AnimatedSprite(double x, double y, double width, double height, Texture * texture, int count, std::vector<maths::vec2> coordsMin, std::vector<maths::vec2> coordsMax)
		: StaticSprite(maths::vec2(x, y), maths::vec2(width, height), texture), 
		m_spritesCoordsMin(coordsMin), m_spritesCoordsMax(coordsMax), m_spriteCount(count), m_spriteIndex(0)
	{
		m_texCoords.clear();

		m_pixelWidth = m_texture->getWidth();
		m_pixelHeight = m_texture->getHeight();

		maths::vec2 currentTC_min = m_spritesCoordsMin[m_spriteIndex];
		maths::vec2 currentTC_max = m_spritesCoordsMax[m_spriteIndex];

		m_texCoords.push_back(maths::vec2(currentTC_min.x / m_pixelWidth, currentTC_min.y / m_pixelHeight));
		m_texCoords.push_back(maths::vec2(currentTC_min.x / m_pixelWidth, currentTC_max.y / m_pixelHeight));
		m_texCoords.push_back(maths::vec2(currentTC_max.x / m_pixelWidth, currentTC_max.x / m_pixelHeight));
		m_texCoords.push_back(maths::vec2(currentTC_max.x / m_pixelWidth, currentTC_min.y / m_pixelHeight));
	}

	void AnimatedSprite::nextSprite() {
		m_spriteIndex++;

		if (m_spriteIndex == m_spriteCount)
			m_spriteIndex = 0;

		m_texCoords.clear();

		maths::vec2 currentTC_min = m_spritesCoordsMin[m_spriteIndex];
		maths::vec2 currentTC_max = m_spritesCoordsMax[m_spriteIndex];

		m_texCoords.push_back(maths::vec2(currentTC_min.x / m_pixelWidth, currentTC_min.y / m_pixelHeight));
		m_texCoords.push_back(maths::vec2(currentTC_min.x / m_pixelWidth, currentTC_max.y / m_pixelHeight));
		m_texCoords.push_back(maths::vec2(currentTC_max.x / m_pixelWidth, currentTC_max.x / m_pixelHeight));
		m_texCoords.push_back(maths::vec2(currentTC_max.x / m_pixelWidth, currentTC_min.y / m_pixelHeight));
	}

} }