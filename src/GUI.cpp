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
	objSettingsHeader();
	simulationHeader();
	settingsHeader();
	showPerformance();

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::windowHeader()
{
	if (ImGui::CollapsingHeader("Window"))
	{
		ImGui::Text("Window Background Color");
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		ImGui::Checkbox("skybox", &use_skybox);
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

void GUI::objSettingsHeader()
{
	if (ImGui::CollapsingHeader("Object Settings"))
	{
		static int testing;

		ImGui::Text("Working on this!");

		ImGui::RadioButton("Edit Body 1", &testing, 1);
		ImGui::RadioButton("Edit Body 2", &testing, 2);
		ImGui::RadioButton("Edit Body 3", &testing, 3);

		if (testing != NULL)
		{
			glm::vec3& pos = spheres[testing - 1].position;
			glm::vec3& vel = spheres[testing - 1].velocity;
			glm::vec3& scale = spheres[testing - 1].scale;
			float& mass = spheres[testing - 1].mass;

			ImGui::Begin("Sphere Editor");

			ImGui::Text("Edit Position: ");

			ImGui::SliderFloat("pos x", &pos.x, -10.0f, 10.0f);
			ImGui::SliderFloat("pos y", &pos.y, -10.0f, 10.0f);
			ImGui::SliderFloat("pos z", &pos.z, -10.0f, 10.0f); 

			ImGui::InputFloat3("pos", &pos.x);

			ImGui::Text("Edit Velocity: ");
			ImGui::SliderFloat("vel x", &vel.x, -10.0f, 10.0f);
			ImGui::SliderFloat("vel y", &vel.y, -10.0f, 10.0f);
			ImGui::SliderFloat("vel z", &vel.z, -10.0f, 10.0f);

			ImGui::InputFloat3("vel", &vel.x);

			ImGui::Text("Edit Mass: ");
			ImGui::InputFloat("mass", &mass);

			ImGui::Text("Edit Size: ");

			ImGui::SliderFloat("Size x", &scale.x, 1.0f, 10.0f);
			ImGui::SliderFloat("Size y", &scale.y, 1.0f, 10.0f);
			ImGui::SliderFloat("Size z", &scale.z, 1.0f, 10.0f);

			ImGui::End();
		}
	}
}

void GUI::simulationHeader()
{
	if (ImGui::CollapsingHeader("Simulation"))
	{
		static int simulation_settings;
		ImGui::Text("Simulation Settings");

		ImGui::RadioButton("Start Custom",   &simulation_settings, 1); // 1 -> start sim
		ImGui::RadioButton("Stop",    &simulation_settings, 2); // 2 -> stop sim
		ImGui::RadioButton("Restart", &simulation_settings, 3); // 3 -> restart sim

		// save positions before moving and load them up on restart
		if (simulation_settings == 1)
		{
			for (auto& body : spheres)
			{
				restartPositions.push_back(body.position);
				restartVel.push_back(body.velocity);
			}
			move_permission = true;
		}

		if (simulation_settings == 2)
		{
			move_permission = false;
		}

		if (simulation_settings == 3)
		{
			for (int i = 0; i < spheres.size(); i++)
			{
				spheres[i].position = restartPositions[i];
				spheres[i].velocity = restartVel[i];
				spheres[i].feltForce = glm::vec3(0.0f);
			}
		}
	}
}

void GUI::settingsHeader()
{
	float& movement_speed = scenemgr.ctrlmgr.camera.MovementSpeed;
	float& mouse_speed = scenemgr.ctrlmgr.camera.MouseSensitivity;
	ImGui::Text("Control Settings: ");

	ImGui::SliderFloat("Movement Speed", &movement_speed, 1.0f, 10.0f);
	ImGui::SliderFloat("Mouse Sensitivity", &mouse_speed, 1.0f, 5.0f);
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