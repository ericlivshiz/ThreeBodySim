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

		for (int i = 0; i < ThreeBody.size(); i++)
		{
			ThreeBody[i].Setup(texturePaths[i]);
		}
	}

public:

	std::vector<Sphere> ThreeBody;

	std::vector<const char* > texturePaths =
	{
		"src/img/blueplasma.jpg",
		"src/img/redhotflames.jpg",
		"src/img/solarTexture.jpg"
	};

	Sphere sphere;
	Sphere sphere2;
	Sphere sphere3;
};