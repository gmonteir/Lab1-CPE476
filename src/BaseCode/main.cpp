/*
 * Program 3 base code - includes modifications to shape and initGeom in preparation to load
 * multi shape objects 
 * CPE 471 Cal Poly Z. Wood + S. Sueda + I. Dunn
 */

#include <iostream>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <glad/glad.h>

#include "GLSL.h"
#include "Program.h"
#include "Shape.h"
#include "Texture.h"
#include "MatrixStack.h"
#include "WindowManager.h"
#include "stb_image.h"
#include "../Controllers/Shapes.h"
#include "../Controllers/Textures.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Entities/Player.h"
#include "../Controllers/RenderController.h"
#include "../Entities/Terrain.h"

#define PI 3.141592

using namespace std;
using namespace glm;

class Application : public EventCallbacks
{

public:

	float theta = 0;
	float phi = 0;
	float radius = 1;
	float x, y, z;
	double clickX, clickY;

	vec3 center;
	vec3 up = vec3(0, 1, 0);
	vec3 eye = vec3(0, 0.5, 0);
	vec3 forward;
	const vec3 speed = vec3(0.5, 0.5, 0.5);

	int lastX = 0;
	int lastY = 0;

	long frames = 0;
	float time;

	WindowManager * windowManager = nullptr;
	Textures tex;
	Shapes shapes;

	TransformController tc;
	MovementController mc;
	CollisionController cc;
	RenderController rc;

	// Our shader program
	std::shared_ptr<Program> prog;

	//example data that might be useful when trying to compute bounds on multi-shape
	vec3 gMin;

	bool mouseDown = false;

	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			eye += speed * forward;
			eye.y = 0;
			center += speed * forward;
		}
		if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			eye -= speed * forward;
			eye.y = 0;
			center -= speed * forward;
		}
		if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			eye += speed * cross(up, forward);
			center += speed * cross(up, forward);
		}
		if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			eye -= speed * cross(up, forward);
			center -= speed * cross(up, forward);
		}
		if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}
		if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
	}

	void scrollCallback(GLFWwindow* window, double deltaX, double deltaY)
	{
		
	}

	void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		double deltaX = xpos - lastX;
		double deltaY = ypos - lastY;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		theta += deltaX / 500;
		phi += -deltaY / 500;

		if (phi > 1.5)
		{
			phi = 1.5;
		}
		else if (phi < -1.5)
		{
			phi = -1.5;
		}

		lastX += deltaX;
		lastY += deltaY;
	}

	void mouseCallback(GLFWwindow *window, int button, int action, int mods)
	{
		double posX, posY;
		if (action == GLFW_PRESS)
		{
			mouseDown = true;
			glfwGetCursorPos(window, &posX, &posY);
			cout << "Pos X " << posX << " Pos Y " << posY << endl;
		}

		if (action == GLFW_RELEASE)
		{
			mouseDown = false;
		}
	}

	void resizeCallback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void init(const std::string& resourceDirectory)
	{
		GLSL::checkVersion();

		// Set background color.
		glClearColor(0.0f, 0.0f, 0.8f, 0.25f);
		// Enable z-buffer test.
		glEnable(GL_DEPTH_TEST);

		// Initialize the GLSL program.
		prog = make_shared<Program>();
		prog->setVerbose(true);
		prog->setShaderNames(resourceDirectory + "/tex_vert.glsl", resourceDirectory + "/tex_frag0.glsl");
		prog->init();
		prog->addUniform("P");
		prog->addUniform("V");
		prog->addUniform("M");
		prog->addUniform("Texture0");
		prog->addUniform("eyePos");
		prog->addAttribute("vertPos");
		prog->addAttribute("vertNor");
		prog->addAttribute("vertTex");		

	}

	void initTex(const std::string& resourceDirectory)
	{		
		tex.addTexture(resourceDirectory + "/grass.jpg", "grass");
	}

	void initGeom(const std::string& resourceDirectory)
	{
		shapes.addShape(resourceDirectory + "/cube.obj", "cube");
		shapes.addShape(resourceDirectory + "/terrain.obj", "terrain");

		Player player = Player(eye, 10);
		Terrain terrain = Terrain(vec3(0, -3, 0), shapes.getShape("terrain"), prog, tex.getTexture("grass"));
	}
	
	void render() {
		// Get current frame buffer size.
		int width, height;
		glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
		glViewport(0, 0, width, height);

		// Clear framebuffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use the matrix stack for Lab 6
		float aspect = width/ (float)height;

		time = frames / 60.0f;

		x = radius*cos(phi)*cos(theta);
		y = radius*sin(phi);
		z = radius*cos(phi)*sin(theta);
		center = eye + vec3(x, y, z);
		forward = normalize(center - eye);

		// Create the matrix stacks - please leave these alone for now
		auto Projection = make_shared<MatrixStack>();
		auto Model = make_shared<MatrixStack>();

		// Apply perspective projection.
		Projection->pushMatrix();
		Projection->perspective(45.0f, aspect, 0.01f, 10000.0f);



	}
};

int main(int argc, char *argv[])
{
	// Where the resources are loaded from
	std::string resourceDir = "../resources";

	if (argc >= 2)
	{
		resourceDir = argv[1];
	}

	Application *application = new Application();

	// Your main will always include a similar set up to establish your window
	// and GL context, etc.

	WindowManager *windowManager = new WindowManager();
	windowManager->init(640, 480);
	windowManager->setEventCallbacks(application);
	application->windowManager = windowManager;

	// This is the code that will likely change program to program as you
	// may need to initialize or set up different data and state

	application->init(resourceDir);
	application->initGeom(resourceDir);
	application->initTex(resourceDir);

	// Loop until the user closes the window.
	while (! glfwWindowShouldClose(windowManager->getHandle()))
	{
		// Render scene.
		application->render();

		// Swap front and back buffers.
		glfwSwapBuffers(windowManager->getHandle());
		// Poll for and process events.
		glfwPollEvents();
		
		application->frames++;
	}

	// Quit program.
	windowManager->shutdown();
	return 0;
}
