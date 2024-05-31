#include "Physics.h"

void Physics::testMove(glm::vec3& position, glm::vec3& velocity, float& dt)
{
	float scaledDt = dt / 300;
	position = (position + (velocity * scaledDt));
}

glm::vec3 Physics::computeGForce(glm::vec3& p1, glm::vec3& p2, float& m1, float& m2)
{
	glm::vec3 r = p1 - p2;
	float distance = glm::length(r);
	glm::vec3 forceDir = glm::normalize(r);
	float forceMag = (G * m1 * m2) / (distance * distance);
	return forceMag * forceDir;
}