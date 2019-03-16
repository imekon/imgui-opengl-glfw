// ImGui - standalone example application for Glfw + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#define _USE_MATH_DEFINES
#include <math.h>

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Log.h"
#include "Shader.h"
#include "Mesh.h"
#include "Window.h"

using namespace std;

const float toRadians = (float)M_PI / 180.0f;

vector<Shader *> shaders;
vector<Mesh *> meshes;

const char *vertexShader = "shaders/shader.vert";
const char *fragmentShader = "shaders/shader.frag";

static void create_meshes()
{
	GLuint indices[] =
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		 0.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};

	auto mesh = new Mesh();
	mesh->createMesh(vertices, indices, 12, 12);
	meshes.push_back(mesh);
}

static void error_callback(int error, const char* description)
{
	stringstream stream;
	stream << description << endl;
	Log::log(stream.str().c_str());
}

void create_shaders()
{
	auto shader = new Shader();
	auto result = shader->createFromFiles(vertexShader, fragmentShader);
	if (result)
		shaders.push_back(shader);
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;

	Window window(800, 600);
	window.initialise();

	// Setup GLEW
	if (glewInit() != GLEW_OK)
		return -1;

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window.getWindow(), true);

    // Load Fonts
    // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	create_meshes();
	create_shaders();

	GLuint uniform_projection = 0, uniform_model = 0;

    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(32, 32, 32);

    // Main loop
    while (!window.getShouldClose())
    {
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();

        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Error: %s", Log::getMessage());
        }

        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_another_window)
        {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello");
            ImGui::End();
        }

        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_test_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&show_test_window);
        }

        // Rendering
		int width, height;
		window.getBufferSize();
		width = window.getBufferWidth();
		height = window.getBufferHeight();

		glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, width, height);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto shader = shaders[0];

		shader->useShader();
		uniform_model = shader->getModelLocation();
		uniform_projection = shader->getProjectionLocation();

		glm::mat4 projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

		for (auto mesh : meshes)
			mesh->renderMesh();

		glUseProgram(0);

        ImGui::Render();

		window.swapBuffers();
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}
