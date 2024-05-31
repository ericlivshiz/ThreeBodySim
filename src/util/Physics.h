#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

const float G = 9.8;

class Physics
{
public:
	// use the velocity to change the position (simple test of movement)
	void testMove(glm::vec3& position, glm::vec3& velocity, float& dt);
	glm::vec3 computeGForce(glm::vec3& p1, glm::vec3& p2, float& m1, float& m2);
};