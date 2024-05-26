#include "Renderer.h"

Renderer::Renderer(Window& window)
	:
	window{ window }
{
}

void Renderer::PreRender()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render()
{
	gui.Render();

	Sphere& sphere = scenemgr.objmgr.sphere;

	if (SHOULD_LOAD_SPHERE)
	{
		RenderSphere();
	}

	if (SHOULD_LOAD_THREE_BODY)
	{
		RenderThreeBody();
	}
}

void Renderer::PostRender()
{
	glfwSwapBuffers(window.Get_Window());
	glfwPollEvents();
}

void Renderer::ToggleWireFrame()
{
	if (CanToggleWireFrame()) {
		// Toggle wireframe state
		if (!frame_state) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			frame_state = true;
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			frame_state = false;
		}

		// Update last toggle time
		last_toggle_time = glfwGetTime();
	}
}

bool Renderer::CanToggleWireFrame() {
	// Get current time
	double current_time = glfwGetTime();

	// Calculate time difference since last toggle
	double elapsed_time = current_time - last_toggle_time;

	// Check if enough time has passed (500 milliseconds)
	return elapsed_time >= 0.5; // 0.5 seconds = 500 milliseconds
}

void Renderer::ToggleMouseMode()
{
	if (CanToggleMouse())
	{
		if (mouse_visible)
		{
			glfwSetInputMode(window.Get_Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			mouse_visible = false;
		}

		else if (!mouse_visible)
		{
			glfwSetInputMode(window.Get_Window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouse_visible = true;
		}

		last_toggle_time_m = glfwGetTime();
	}
}

bool Renderer::CanToggleMouse()
{
	// Get current time
	double current_time = glfwGetTime();

	// Calculate time difference since last toggle
	double elapsed_time = current_time - last_toggle_time_m;

	// Check if enough time has passed (500 milliseconds)
	return elapsed_time >= 0.5; // 0.5 seconds = 500 milliseconds
}

void Renderer::RenderSphere()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sphere.texture1);

	sphere.shader.use();

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)window.Get_AspectRatio(), 0.1f, 500.0f);
	sphere.shader.setMat4("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	sphere.shader.setMat4("view", view);

	glBindVertexArray(sphere.sphereVAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, sphere.position);
	sphere.shader.setMat4("model", model);

	glDrawElements(GL_TRIANGLE_STRIP, sphere.indexCount, GL_UNSIGNED_INT, 0);
}

void Renderer::RenderThreeBody()
{
	for (auto& body : ThreeBody)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, body.texture1);

		body.shader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)window.Get_AspectRatio(), 0.1f, 500.0f);
		body.shader.setMat4("projection", projection);

		glm::mat4 view = camera.GetViewMatrix();
		body.shader.setMat4("view", view);

		glBindVertexArray(body.sphereVAO);
		glm::mat4 model = glm::mat4(1.0f);

		// Update the x-coordinate of the model matrix
		model = glm::translate(model, glm::vec3(body.position));

		body.shader.setMat4("model", model);

		glDrawElements(GL_TRIANGLE_STRIP, body.indexCount, GL_UNSIGNED_INT, 0);
	}
}