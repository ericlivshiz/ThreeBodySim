#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "../SceneMgr.h"
#include "../GUI.h"

class Renderer
{
public:
	Renderer(Window& window);

	void PreRender();
	void Render();
	void PostRender();

	void ToggleWireFrame();

public:
	SceneMgr scenemgr;

private:
	void RenderSphere();
	void RenderThreeBody();
	bool CanToggleWireFrame();

private:
	Window& window;
	bool frame_state = 0; // 0 -> WireFrameOff. 1 -> WireFrameOn
	double last_toggle_time = 0.0;

	Camera& camera = scenemgr.ctrlmgr.camera;
	Sphere& sphere = scenemgr.objmgr.sphere;
	std::vector<Sphere>& ThreeBody = scenemgr.objmgr.ThreeBody;

};