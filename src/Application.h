#pragma once

#include "util/Window.h"
#include "util/Renderer.h"

class Application
{
public:
	Application();
	void Start();

private:
	void Stop();
	void Setup();
	void AppLoop();
	void Handle_Input();
	void Update();
	void Display();

	bool program_running = false;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

private:
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	

	float lastX = window.Get_Width() / 2.0f;
	float lastY = window.Get_Height() / 2.0f;
	bool firstMouse = true;


private:
	Window window;
	Renderer renderer{window};

	static Application* instance;

	Keyboard& keyboard = renderer.scenemgr.ctrlmgr.keyboard;
	Camera& camera = renderer.scenemgr.ctrlmgr.camera;
};