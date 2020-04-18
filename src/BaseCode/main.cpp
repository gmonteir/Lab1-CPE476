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

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	// Our shader program
	std::shared_ptr<Program> prog;
	std::shared_ptr<Program> skyProg;
	std::shared_ptr<Program> specProg;

	// Shape to be used (from  file) - modify to support multiple
	std::shared_ptr<Shape> terrain;
	std::shared_ptr<Shape> cube;

	// Textures
	shared_ptr<Texture> texture0;
	shared_ptr<Texture> texture1;
	shared_ptr<Texture> texture2;
	unsigned int cubeMapTexture;

	// Skybox faces
	vector<std::string> faces {
		"bluecloud_rt.jpg",
		"bluecloud_lf.jpg",
		"bluecloud_up.jpg",
		"bluecloud_dn.jpg",
		"bluecloud_bk.jpg",
		"bluecloud_ft.jpg"
	};

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

		skyProg = make_shared<Program>();
		skyProg->setVerbose(true);
		skyProg->setShaderNames(resourceDirectory + "/cube_vert.glsl", resourceDirectory + "/cube_frag.glsl");
		skyProg->init();
		skyProg->addUniform("P");
		skyProg->addUniform("V");
		skyProg->addUniform("M");
		skyProg->addUniform("skybox");
		skyProg->addAttribute("vertPos");
		skyProg->addAttribute("vertNor");

		specProg = make_shared<Program>();
		specProg->setVerbose(true);
		specProg->setShaderNames(resourceDirectory + "/simple_vert.glsl", resourceDirectory + "/simple_frag.glsl");
		specProg->init();
		specProg->addUniform("P");
		specProg->addUniform("V");
		specProg->addUniform("M");
		specProg->addUniform("MatAmb");
		specProg->addUniform("MatDif");
		specProg->addUniform("MatSpec");
		specProg->addUniform("shine");
		specProg->addUniform("lightPos");
		specProg->addUniform("eye");
		specProg->addAttribute("vertPos");
		specProg->addAttribute("vertNor");
		specProg->addAttribute("vertTex");
	}

	void initTex(const std::string& resourceDirectory)
	{
		texture2 = make_shared<Texture>();
		texture2->setFilename(resourceDirectory + "/grass.jpg");
		texture2->init();
		texture2->setUnit(2);
		texture2->setWrapModes(GL_REPEAT, GL_REPEAT);
	}

	void initGeom(const std::string& resourceDirectory)
	{

		//EXAMPLE set up to read one shape from one obj file - convert to read several
		// Initialize mesh
		// Load geometry
 		// Some obj files contain material information.We'll ignore them for this assignment.
 		vector<tinyobj::shape_t> TOshapes;
 		vector<tinyobj::material_t> objMaterials;
 		string errStr;
		
		//load in the mesh and make the shape(s)
		bool rc = tinyobj::LoadObj(TOshapes, objMaterials, errStr, (resourceDirectory + "/cube.obj").c_str());
		if (!rc) {
			cerr << errStr << endl;
		}
		else {
			cube = make_shared<Shape>();
			cube->createShape(TOshapes[0]);
			cube->measure();
			cube->init();
		}

		rc = tinyobj::LoadObj(TOshapes, objMaterials, errStr, (resourceDirectory + "/plane.obj").c_str());
		if (!rc) {
			cerr << errStr << endl;
		}
		else {
			terrain = make_shared<Shape>();
			terrain->createShape(TOshapes[0]);
			terrain->tileCoords(8.0);
			terrain->measure();
			terrain->init();
		}

		cubeMapTexture = createSky(resourceDirectory + "/skybox/", faces);
	}

	void setModel(std::shared_ptr<Program> prog, std::shared_ptr<MatrixStack>M) {
		glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
    }

	unsigned int createSky(string dir, vector<string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(false);
		for (GLuint i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load((dir+faces[i]).c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				cout << "failed to load: " << (dir+faces[i]).c_str() << endl;
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		cout << " creating cube map any errors : " << glGetError() << endl;
		return textureID;
	}
	
	void render() {
		// Get current frame buffer size.
		int width, height;
		glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
		glViewport(0, 0, width, height);

		// Clear framebuffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use the matrix stack for Lab 6
		float aspect = width/(float)height;

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

		// Draw skybox
		skyProg->bind();
		glUniformMatrix4fv(skyProg->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
		glDepthFunc(GL_LEQUAL);
		glUniformMatrix4fv(skyProg->getUniform("V"), 1, GL_FALSE, value_ptr(lookAt(eye, center, up)));

		Model->pushMatrix();
			Model->loadIdentity();
			Model->translate(eye);
			Model->scale(vec3(110, 110, 110));

			glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
			setModel(skyProg, Model);
			cube->draw(skyProg);
		Model->popMatrix();

		glDepthFunc(GL_LESS);
		skyProg->unbind();
		
		prog->bind();
		glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
		glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, value_ptr(lookAt(eye, center, up)));
		glUniform3f(prog->getUniform("eyePos"), eye.x, eye.y, eye.z);

		// draw stuff
		Model->pushMatrix();
			Model->loadIdentity();

			// draw ground
			Model->pushMatrix();
				Model->scale(vec3(50, 1, 50));
				Model->translate(vec3(0, -1, 0));
				texture2->bind(prog->getUniform("Texture0"));
				setModel(prog, Model);
				terrain->draw(prog);
				texture2->unbind();
			Model->popMatrix();
		prog->unbind();
		Projection->popMatrix();
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
