#include "GUI.h"

GUI::GUI(GLFWwindow* window)
	:
	window{ window }
{

}

void GUI::Setup()
{
	glfwSetErrorCallback(glfw_error_callback);
	SetContext();
	SetBackends();
}

void GUI::Start()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Editor Menu!");
}

void GUI::End()
{
	ImGui::End();
}

void GUI::Render()
{
	Start();

	windowHeader();
	simulationHeader();

	ImGui::End();

	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::windowHeader()
{
	if (ImGui::CollapsingHeader("Window"))
	{
		ImGui::Text("Window Background Color");
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
	}
}

void GUI::simulationHeader()
{
	if (ImGui::CollapsingHeader("Simulation"))
	{
		static int simulation_settings;
		ImGui::Text("Simualtion Settings");

		ImGui::RadioButton("Start", &simulation_settings, 1); // 1 -> start sim
		ImGui::RadioButton("Stop", &simulation_settings, 2); // 2 -> stop sim
		ImGui::RadioButton("Restart", &simulation_settings, 3); // 3 -> restart sim
	}
}

void GUI::glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void GUI::SetContext()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui::StyleColorsDark();

}

void GUI::SetBackends()
{
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}