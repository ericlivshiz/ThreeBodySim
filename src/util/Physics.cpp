#include "Physics.h"

void Physics::UpdatePosition(glm::vec3& position, glm::vec3 velocity, float dt)
{
	position = (position + (velocity * dt));
}

void Physics::UpdateVelocity(glm::vec3& velocity, glm::vec3 force, float mass, float dt)
{
	velocity += (force / mass) * dt;
}

void Physics::CalculateGravitationalForce(glm::vec3& force, glm::vec3 p1, glm::vec3 p2, float m1, float m2)
{
    glm::vec3 r = p2 - p1;
    float distance = glm::length(r);
    glm::vec3 forceDir = glm::normalize(r);
    float forceMag = (G * m1 * m2) / (distance * distance);
    force = forceDir * forceMag;
}


// https://github.com/carl-vbn/opengl-gravity-simulator/blob/main/src/universe/universe.cpp
//void Universe::updateBodies(double deltaTime) {
//	// Step 1: update all velocities
//	for (unsigned int i = 0; i < bodies.size(); i++) {
//		MassBody* body = bodies.at(i);
//
//		if (body->affectedByGravity) {
//			glm::vec3 totalGravitationalForce = glm::vec3(0);
//
//			// Loop through all bodies in the universe to calculate their gravitational pull on the object (TODO: Ignore very far away objects for better performance)
//			for (unsigned int j = 0; j < bodies.size(); j++) {
//				if (i == j) continue; // No need to calculate the gravitational pull of a body on itself as it will always be 0.
//				MassBody* otherBody = bodies.at(j);
//
//				if (!otherBody->affectsOthers) continue; // Ignore this one
//
//				float force = gConstant * body->mass * otherBody->mass / std::pow(glm::distance(body->position, otherBody->position), 2);
//				glm::vec3 forceDirection = glm::normalize(otherBody->position - body->position);
//
//				totalGravitationalForce += forceDirection * force;
//			}
//
//			// Update the velocity of the object by adding the acceleration, which is the force divided by the object's mass. (and multiply it all by deltaTime)
//			bodies.at(i)->velocity += totalGravitationalForce / body->mass * (float)deltaTime;
//		}
//	}
//
//	// Step 2: update all positions
//	for (unsigned int i = 0; i < bodies.size(); i++) {
//		MassBody* body = bodies.at(i);
//		body->position += body->velocity * (float)deltaTime;
//	}
//}