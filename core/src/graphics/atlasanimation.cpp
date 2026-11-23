#include "atlasanimation.hpp"

namespace heartCore { namespace graphics {
	using namespace API;
	AtlasAnimation::AtlasAnimation(std::vector<maths::vec2> framesStart, std::shared_ptr<Texture> atlas, int offsetX, int offsetY, unsigned long long duration_ms, bool looping)
		: Animation(duration_ms, looping), m_frameCount(framesStart.size()), m_finished(false),
		m_pixelWidth(atlas->getWidth()), m_pixelHeight(atlas->getHeight()), m_texture(atlas), 
		m_offsetX(offsetX), m_offsetY(offsetY)
	{

		if (framesStart.empty())
			LOG_WARNING("Atlas has no start points!");

		for (int i = 0; i < m_frameCount;i++) {
			m_framesTC.push_back({ 
				maths::vec2(framesStart[i].x / m_pixelWidth, framesStart[i].y / m_pixelHeight),
				maths::vec2(framesStart[i].x / m_pixelWidth, (framesStart[i].y + m_offsetY) / m_pixelHeight),
				maths::vec2((framesStart[i].x + m_offsetX) / m_pixelWidth, (framesStart[i].y + m_offsetY) / m_pixelHeight),
				maths::vec2((framesStart[i].x + m_offsetX) / m_pixelWidth, framesStart[i].y / m_pixelHeight)
			});
		}
	}

	void AtlasAnimation::play() {
		if (!m_isPlaying) {
			m_isPlaying = true;
			m_finished = false;
			m_deltaTimer.start();
		}
	}

	void AtlasAnimation::pause() {
		if (m_isPlaying) {
			m_isPlaying = false;
		}
	}

	void AtlasAnimation::reset() {
		m_isPlaying = false;
		m_finished = false;
		m_currentFrameIndex = -1;
		m_deltaTimer.reset();
	}

	void AtlasAnimation::nextSprite(std::shared_ptr<StaticSprite> sprite) {
		if (m_framesTC.empty()) {
			reset();
			return;
		}

		++m_currentFrameIndex;

		if (m_currentFrameIndex >= m_frameCount) {
			if (!m_looping) {
				m_finished = true;
				reset();
				m_finished = true;
				return;
			}

			m_currentFrameIndex = 0;
		}

		sprite->setTexture(m_texture);
		sprite->setTC(m_framesTC[m_currentFrameIndex]);

	}

	void AtlasAnimation::update(std::shared_ptr<StaticSprite> sprite) {
		if (!m_isPlaying || m_framesTC.empty() || m_duration == 0)
			return;

		if (m_deltaTimer.count<std::chrono::milliseconds>() >= m_duration) {
			m_deltaTimer.reset();
			m_deltaTimer.start();
			nextSprite(std::move(sprite));
		}
	}

} }