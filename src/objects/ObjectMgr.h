#pragma once

#include "Sphere.h"

#define SHOULD_LOAD_SPHERE     0
#define SHOULD_LOAD_THREE_BODY 1

class ObjectMgr
{
public:
	void SetupObjects()
	{
		ThreeBody.push_back(sphere);
		ThreeBody.push_back(sphere2);
		ThreeBody.push_back(sphere3);

		for (auto& body : ThreeBody)
		{
			body.Setup();
		}
	}

public:

	std::vector<Sphere> ThreeBody;

	Sphere sphere;
	Sphere sphere2;
	Sphere sphere3;
};