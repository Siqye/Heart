#define OPENAL_TEST
#if defined(OPENAL_TEST)

#include <al.h>
#include <alc.h>
#include "src/utils/wav_file_reader.hpp"
#include <chrono>
#include <iostream>
#include <thread>

using namespace heartCore;

int main() {
	ALCdevice* device = alcOpenDevice(nullptr);
	if (!device) {
		std::cerr << "Failed to open default OpenAL device\n";
		return -1;
	}

	ALCcontext* context = alcCreateContext(device, nullptr);
	if (!context || !alcMakeContextCurrent(context)) {
		std::cerr << "Failed to create OpenAL context\n";
		if (context)
			alcDestroyContext(context);
		alcCloseDevice(device);
		return -1;
	}

	WavFile wav;
	if (!loadWAVFile("sound.wav", wav)) {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context);
		alcCloseDevice(device);
		return -1;
	}

	ALenum format = 0;
	if (wav.channels == 1 && wav.bitsPerSample == 8)
		format = AL_FORMAT_MONO8;
	else if (wav.channels == 1 && wav.bitsPerSample == 16)
		format = AL_FORMAT_MONO16;
	else if (wav.channels == 2 && wav.bitsPerSample == 8)
		format = AL_FORMAT_STEREO8;
	else if (wav.channels == 2 && wav.bitsPerSample == 16)
		format = AL_FORMAT_STEREO16;

	ALuint buffer = 0;
	ALuint source = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, wav.data.data(), static_cast<ALsizei>(wav.data.size()),
		static_cast<ALsizei>(wav.sampleRate));
	alGenSources(1, &source);
	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(source, AL_LOOPING, AL_FALSE);
	alSourcei(source, AL_BUFFER, static_cast<ALint>(buffer));

	alSourcePlay(source);

	ALint state = AL_PLAYING;
	while (state == AL_PLAYING) {
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
	return 0;
}


#else

#include "src/utils/timer.hpp"
#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"
#include "src/graphics/sprite.hpp"
#include "src/graphics/texture.hpp"
#include "src/graphics/layers/group.hpp"
#include "src/graphics/layers/levellayer.hpp"
#include "src/graphics/renderer2d.hpp"
#include "src/graphics/label.hpp"
#include "src/graphics/fontmanager.hpp"

using namespace heartCore;
using namespace graphics;

int main()
{
	Window window(800, 600, "Heart");

	Shader shader("src/shader/basic.vert", "src/shader/basic.frag");

	Texture* textures[] = {
		new Texture("test/test1.png"),
		new Texture("test/test2.png"),
		new Texture("test/test3.png"),
		new Texture("test/test4.png"),
		new Texture("test/test5.png")
	};

	int texIDs[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };

	shader.bind();
	shader.setUniform1iv("textures", 32, texIDs);

	FontManager fm("test\\fonts");

	LevelLayer layer(&shader);

	for (float x = 0; x < 4; x += 0.3f) {
		for (float y = 0; y < 3; y += 0.3f) {
			layer.add(new Sprite(x, y, 0.25, 0.25, textures[rand() % 5]));
		}
	}
	Timer timer;
	int fps = 0;
	std::string labelFPS = "0 fps";

	maths::vec4 textColor = maths::vec4(1, 1, 1, 1);
	Label labelfps(labelFPS, 3, 0.3f, 2.3f, textColor, fm.getFontbyID(0));
	Label* lfps = &labelfps;

	layer.add(lfps);

	double x, y;
	while (window.close()) {
		window.clear();

		window.getMousePosition(x, y);
		shader.bind();
		shader.setUniform2f("ligth_pos", maths::vec2(
			-x * 4.0f / 800.0f,
			-3.0f + y * 3.0f / 600.0f
		));

		layer.render();

		labelfps = Label(labelFPS, 3, 0.3f, 2.3f, textColor, fm.getFontbyID(0));

		window.update();

		fps++;
		if (timer.elapsed() >= 1.0) {
			labelFPS = std::to_string(fps);
			labelFPS += " fps";
			timer.reset();
			fps = 0;
		}
	}
	return 0;
}

#endif