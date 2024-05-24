#pragma once

#include "Sphere.h"

#define SHOULD_LOAD_SPHERE     1
#define SHOULD_LOAD_THREE_BODY 0

class ObjectMgr
{
public:
	void SetupObjects()
	{
		if (SHOULD_LOAD_SPHERE)
			sphere.Setup();

		if (SHOULD_LOAD_THREE_BODY)
			sphere.SetupThreeBody();
	}

public:
	Sphere sphere;
};