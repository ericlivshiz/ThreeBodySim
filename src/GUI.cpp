#include "GUI.h"

GUI::GUI(GLFWwindow* window, SceneMgr& scenemgr)
	:
	window{ window },
	scenemgr{scenemgr}
{
}

void GUI::Setup()
{
	glfwSetErrorCallback(glfw_error_callback);
	SetContext();
	SetBackends();

	startPositions.push_back(spheres[0].position);
	startPositions.push_back(spheres[1].position);
	startPositions.push_back(spheres[2].position);
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
	planetsHeader();
	settingsHeader();
	simulationHeader();
	showPerformance();

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

void GUI::planetsHeader()
{
	static int planet_count;

	if (ImGui::CollapsingHeader("Planets"))
	{
		ImGui::Text("Choose Planet Amount");
		
		ImGui::RadioButton("1", &planet_count, 1);
		ImGui::RadioButton("2", &planet_count, 2);
		ImGui::RadioButton("3", &planet_count, 3);
	}

	this->planet_count = planet_count;
}

void GUI::settingsHeader()
{
	if (ImGui::CollapsingHeader("Settings"))
	{
		static int testing;

		ImGui::Text("Working on this!");

		ImGui::RadioButton("Edit Body 1", &testing, 1);
		ImGui::RadioButton("Edit Body 2", &testing, 2);
		ImGui::RadioButton("Edit Body 3", &testing, 3);

		if (testing != NULL)
		{
			glm::vec3& pos = spheres[testing - 1].position;

			ImGui::Begin("Sphere Editor");

			ImGui::Text("Edit Position: ");

			ImGui::SliderFloat("pos x", &pos.x, -10.0f, 10.0f);
			ImGui::SliderFloat("pos y", &pos.y, -10.0f, 10.0f);
			ImGui::SliderFloat("pos z", &pos.z, -10.0f, 10.0f);

			ImGui::End();
		}
	}
}

void GUI::simulationHeader()
{
	if (ImGui::CollapsingHeader("Simulation"))
	{
		static int simulation_settings;
		ImGui::Text("Simualtion Settings");

		ImGui::RadioButton("Start",   &simulation_settings, 1); // 1 -> start sim
		ImGui::RadioButton("Stop",    &simulation_settings, 2); // 2 -> stop sim
		ImGui::RadioButton("Restart", &simulation_settings, 3); // 3 -> restart sim
	}
}

void GUI::showPerformance()
{
	ImGui::Begin("Performance");
	ImGui::Text("Frame time: %f ms", io.DeltaTime * 1000.0f);
	float fps = 1 / io.DeltaTime;
	ImGui::Text("FPS %f", fps);
	ImGui::End();
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