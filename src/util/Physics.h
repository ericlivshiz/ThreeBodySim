#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

const double G = 0.07;

class Physics
{
public:
	static void UpdatePosition(glm::vec3& position, glm::vec3 velocity, float dt);
	static void UpdateVelocity(glm::vec3& velocity, glm::vec3 force, float mass, float dt);
	static void CalculateGravitationalForce(glm::vec3& force, glm::vec3 p1, glm::vec3 p2, float m1, float m2);
};