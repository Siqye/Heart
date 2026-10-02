#define OPENAL_TEST
#if defined(OPENAL_TEST)

#include <al.h>
#include <alc.h>
#include "src/utils/wav_file_reader.hpp"
#include <stdio.h>

using namespace heartCore;

int main() {
	ALCdevice* device; // device pointer
	ALCcontext* context; // context like in windows
	ALboolean b_EAX_support; // EAX 2.0
	ALuint buffer;
	ALuint source;
	ALboolean loop = true;
	ALenum error;


	device = alcOpenDevice(NULL); // defualt device
	if (!device) { // error check
		printf("Failed to open device\n");
		return -1;
	}
	// default context procedure
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) { 
		printf("Failed to make context current\n");
		return -1;
	}

	b_EAX_support = alIsExtensionPresent("EAX2.0"); // check if eax supports

	alGetError(); // clear error buffer

	loadWAVFile("sound.wav", buffer, source, loop);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		alDeleteBuffers(0, &buffer);
		
		return -1;
	}

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