#include "Application.h"

Application* Application::instance = nullptr;

Application::Application()
{
	instance = this;
}

void Application::Start()
{
	program_running = true;
	Setup();
}

void Application::Stop()
{
	program_running = false;
	glfwTerminate();
}

void Application::Setup()
{
	renderer.scenemgr.SetupScene();

	glfwSetCursorPosCallback(window.Get_Window(), mouse_callback);
	glfwSetScrollCallback(window.Get_Window(), scroll_callback);
	glfwSetInputMode(window.Get_Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	AppLoop();
}

void Application::AppLoop()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	while (program_running)
	{
		Handle_Input();
		Update();
		Display();
	}
}

void Application::Handle_Input()
{
	Keyboard& keyboard = renderer.scenemgr.ctrlmgr.keyboard;
	Camera& camera = renderer.scenemgr.ctrlmgr.camera;

	keyboard.ProcessKeyInput(window.Get_Window());

	if (keyboard.ESC_PRESS)
	{
		program_running = false;
	}

	// and a certain button lock time has passed..
	if (keyboard.L_CTRL_PRESS)
	{
		renderer.ToggleWireFrame();
	}

	if (keyboard.W_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keyboard.A_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keyboard.S_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keyboard.D_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void Application::Update()
{

}

void Application::Display()
{
	renderer.PreRender();
	renderer.Render();
	renderer.PostRender();
}

void Application::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (instance)
	{
		Camera& camera = instance->renderer.scenemgr.ctrlmgr.camera;

		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (instance->firstMouse)
		{
			instance->lastX = xpos;
			instance->lastY = ypos;
			instance->firstMouse = false;
		}

		float xoffset = xpos - instance->lastX;
		float yoffset = instance->lastY - ypos;

		instance->lastX = xpos;
		instance->lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset, true);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (instance)
	{
		Camera& camera = instance->renderer.scenemgr.ctrlmgr.camera;

		camera.ProcessMouseScroll(static_cast<float>(yoffset));
	}
}