#define DEFUALT 1

#if DEFUALT

#include "src/utils/timer.hpp"
#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"
#include "src/graphics/sprite.hpp"
#include "src/graphics/renderer.hpp"
#include "src/graphics/texture.hpp"
#include "src/graphics/layers/group.hpp"
#include "src/graphics/layers/levellayer.hpp"
#include "src/graphics/label.hpp"


using namespace heartCore;
using namespace graphics;

int main() 
{

	Window window(800, 600, "Allah velik!");
	
	Shader shader("src/shader/basic.vert", "src/shader/basic.frag");

    /* Texture* textures[] = {
		new Texture("test/test1.png"),
		new Texture("test/test2.png"),
		new Texture("test/test3.png"),
		new Texture("test/test4.png"),
		new Texture("test/test5.png")
	};*/

	LevelLayer layer;

	/*for (float x = 0; x < 4; x += 0.3f) { for (float y = 0; y < 3; y += 0.3f) {
		layer.add(Sprite(x, y, 0.25, 0.25, textures[rand() % 5]));
	} }*/
    Label string = Label("A",1,1, maths::vec4(1,1,1,1), "fonts/Arvo-Regular.ttf");

    layer.add(string);

    
	int texIDs[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };

	shader.bind();
	shader.setUniformMat4f("pr_matrix", maths::mat4::orthographic(0,4,3,0,1,0));
	shader.setUniform1iv("textures", 32, texIDs);
	Renderer renderer;

	Timer timer;
	int fps = 0;

	double x, y;
	while (window.close()) {
		window.clear();

		window.getMousePosition(x, y);
		shader.setUniform2f("ligth_pos", maths::vec2(
			-x * 4.0f / 800.0f,
			-3.0f + y * 3.0f / 600.0f
		));

		fps++;
		if (timer.elapsed() >= 1.0) {
			std::cout << fps << std::endl;
			timer.reset();
			fps = 0;
		}

		layer.render(&renderer);

		window.update();
	}

	return 0;
}

#else 

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_GLCOREARB

//#include <glew.h>
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <string>

const char* VERTEX_SHADER = "#version 410 core\n in vec4 in_Position;\n out vec2 texCoords;\n void main(void) {\n gl_Position = vec4(in_Position.xy, 0, 1);\ntexCoords = in_Position.zw;}\n";

const char* FRAGMENT_SHADER = "#version 410 core\n precision highp float;\n uniform sampler2D tex;\n uniform vec4 color;\n in vec2 texCoords;\n out vec4 fragColor;\n void main(void) {\n fragColor = vec4(1, 1, 1, texture(tex, texCoords).r) * color;\n }\n";

void render_text(const std::string& str, FT_Face face, float x, float y, float sx, float sy) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    const FT_GlyphSlot glyph = face->glyph;

    for (char c : str) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
            continue;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
            glyph->bitmap.width, glyph->bitmap.rows,
            0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

        const float vx = x + glyph->bitmap_left * sx;
        const float vy = y + glyph->bitmap_top * sy;
        const float w = glyph->bitmap.width * sx;
        const float h = glyph->bitmap.rows * sy;

        struct {
            float x, y, s, t;
        } data[6] = {
            {vx    , vy    , 0, 0},
            {vx    , vy - h, 0, 1},
            {vx + w, vy    , 1, 0},
            {vx + w, vy    , 1, 0},
            {vx    , vy - h, 0, 1},
            {vx + w, vy - h, 1, 1}
        };

        glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), data, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (glyph->advance.x >> 6) * sx;
        y += (glyph->advance.y >> 6) * sy;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}
int main() {
    GLuint texture{ 0 }, sampler{ 0 };
    GLuint vbo{ 0 }, vao{ 0 };
    GLuint vs{ 0 }, fs{ 0 }, program{ 0 };
    FT_Library ft_lib{ nullptr };
    FT_Face face{ nullptr };

    auto cleanup = [&]() {
        FT_Done_Face(face);
        FT_Done_FreeType(ft_lib);
        glDeleteTextures(1, &texture);
        glDeleteSamplers(1, &sampler);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);
        };

    // Initialize and load our freetype face
    if (FT_Init_FreeType(&ft_lib) != 0) {
        std::cerr << "Couldn't initialize FreeType library\n";
        cleanup();
        return 1;
    }

    const char* fontPath = "fonts/Arvo-Regular.ttf";

    if (FT_New_Face(ft_lib, fontPath, 0, &face) != 0) {
        std::cerr << "Unable to load myfont.ttf\n";
        cleanup();
        return 1;
    }

    // Create a GLFW window
    if (glfwInit() != GL_TRUE) {
        std::cerr << "Couldn't load GLFW library\n";
        cleanup();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int WIDTH = 640;
    const int HEIGHT = 480;
    const double SCALEX = 2.0 / WIDTH;
    const double SCALEY = 2.0 / HEIGHT;

    auto window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Text Rendering", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, WIDTH, HEIGHT);

    // Initialize our texture and VBOs
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenTextures(1, &texture);
    glGenSamplers(1, &sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Initialize shader
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &VERTEX_SHADER, 0);
    glCompileShader(vs);

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &FRAGMENT_SHADER, 0);
    glCompileShader(fs);

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    // Set some initialize GL state
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1, 0.2, 0.4, 0);

    // Get shader uniforms
    glUseProgram(program);
    glBindAttribLocation(program, 0, "in_Position");
    GLuint texUniform = glGetUniformLocation(program, "tex");
    GLuint colorUniform = glGetUniformLocation(program, "color");

    while (glfwWindowShouldClose(window) != GL_TRUE) {
        glfwMakeContextCurrent(window);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind stuff
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindSampler(0, sampler);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glUseProgram(program);
        glUniform4f(colorUniform, 1, 1, 1, 1);
        glUniform1i(texUniform, 0);

        FT_Set_Pixel_Sizes(face, 0, 50);
        render_text("Hello World!", face, -0.5, 0, SCALEX, SCALEY);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup();
    return 0;
}
#endif