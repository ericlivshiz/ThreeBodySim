#pragma once

#include "util/Physics.h"
#include "objects/ObjectMgr.h"
#include "controls/ControlMgr.h"

class SceneMgr
{
public:
	void SetupScene()
	{
		objmgr.SetupObjects();
		objmgr.skybox.Create_Cubemap();
	}

    void UpdateScene(bool moveperm, int p_count, float dt)
    {
        if (moveperm)
        {
            // Reset forces
            for (int i = 0; i < p_count; i++)
            {
                ThreeBody[i].feltForce = glm::vec3(0.0f);
            }

            // Calculate gravitational forces
            for (int i = 0; i < p_count - 1; i++)
            {
                for (int j = i + 1; j < p_count; j++)
                {
                    glm::vec3& p1 = ThreeBody[i].position;
                    glm::vec3& p2 = ThreeBody[j].position;

                    glm::vec3& f1 = ThreeBody[i].feltForce;
                    glm::vec3& f2 = ThreeBody[j].feltForce;

                    float& m1 = ThreeBody[i].mass;
                    float& m2 = ThreeBody[j].mass;

                    glm::vec3 force;
                    Physics::CalculateGravitationalForce(force, p1, p2, m1, m2);

                    // Apply equal and opposite forces
                    f1 += force;
                    f2 -= force;
                }
            }

            // Update velocities and positions in a single loop
            for (int i = 0; i < p_count; i++)
            {
                glm::vec3& v = ThreeBody[i].velocity;
                glm::vec3& p = ThreeBody[i].position;
                glm::vec3& f = ThreeBody[i].feltForce;
                float& m = ThreeBody[i].mass;
                Physics::UpdateVelocity(v, f, m, dt);
                Physics::UpdatePosition(p, v, dt);
            }
        }
    }


public:
	ObjectMgr objmgr;
	ControlMgr ctrlmgr;
	std::vector<Sphere>& ThreeBody = objmgr.ThreeBody;
};