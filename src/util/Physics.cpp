#include "Physics.h"

void Physics::testMove(glm::vec3& position, glm::vec3& velocity, float& dt)
{
	float scaledDt = dt / 300;
	position = (position + (velocity * scaledDt));
}