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
	renderer.gui.Setup();

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

	keyboard.ProcessKeyInput(window.Get_Window());

	if (keyboard.ESC_PRESS)
	{
		program_running = false;
	}

	// and a certain button lock time has passed..
	if (keyboard.L_CTRL_PRESS)
	{
		renderer.ToggleMouseMode();
	}

	if (keyboard.L_SHIFT_PRESS)
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
	bool& movePermission = renderer.gui.move_permission;
	bool& startTwoBody = renderer.gui.start_two_body;
	std::vector<Sphere>& ThreeBody = renderer.scenemgr.objmgr.ThreeBody;

	if (startTwoBody)
	{
		Physics physics;
		glm::vec3& p1 = ThreeBody[0].position;
		glm::vec3& p2 = ThreeBody[1].position;
		float& m1 = ThreeBody[0].mass;
		float& m2 = ThreeBody[1].mass;

		glm::vec3 forceOn1 = physics.computeGForce(p1, p2, m1, m2);
		glm::vec3 forceOn2 = physics.computeGForce(p2, p1, m2, m1);

		float scaledDt = 300;
		ThreeBody[0].velocity += ((forceOn1 / m1) * deltaTime) / scaledDt;
		ThreeBody[1].velocity += ((forceOn2 / m2) * deltaTime) / scaledDt;

		ThreeBody[0].Move(deltaTime);
		ThreeBody[1].Move(deltaTime);
	}

	if (movePermission)
	{

		for (auto& body : ThreeBody)
		{
			body.Move(deltaTime);
		}
	}
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

		instance->camera.ProcessMouseMovement(xoffset, yoffset, true);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (instance)
	{
		instance->camera.ProcessMouseScroll(static_cast<float>(yoffset));
	}
}

