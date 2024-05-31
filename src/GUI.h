#pragma once

#include "SceneMgr.h"

#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_glfw.h"
#include "../dependencies/imgui/imgui_impl_opengl3.h"

#include "util/Window.h"

class GUI
{
public:
	GUI(GLFWwindow* window, SceneMgr& scenemgr);

	void Setup();
	void Render();
	void Start();
	void End();

	// ui components
public:
	void windowHeader();
	void planetsHeader();
	void objSettingsHeader();
	void settingsHeader();
	void simulationHeader();
	void showPerformance();

	int planet_count = 3;
	bool move_permission = false;
	bool start_two_body = false;
	bool use_skybox = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


private:
	static void glfw_error_callback(int error, const char* description);
	void SetContext();
	void SetBackends();

	const char* glsl_version = "#version 130";
	ImGuiIO io;

	GLFWwindow* window;
	SceneMgr& scenemgr;

	std::vector<Sphere>& spheres = scenemgr.objmgr.ThreeBody;

	std::vector<glm::vec3> restartPositions;
	glm::vec3 tempVelocity;
};