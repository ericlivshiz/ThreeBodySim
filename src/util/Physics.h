#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Physics
{
public:
	// use the velocity to change the position (simple test of movement)
	void testMove(glm::vec3& position, glm::vec3& velocity, float& dt);
};