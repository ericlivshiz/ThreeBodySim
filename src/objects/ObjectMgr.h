#pragma once

#include "Sphere.h"
#include "Skybox.h"

#define SHOULD_LOAD_THREE_BODY 1

class ObjectMgr
{
public:
	void SetupObjects()
	{
		ThreeBody.push_back(sphere);
		ThreeBody.push_back(sphere2);
		ThreeBody.push_back(sphere3);

		float xPos = -10.0f;

		for (int i = 0; i < ThreeBody.size(); i++)
		{
			ThreeBody[i].Setup(texturePaths[i]);
			ThreeBody[i].position.x = xPos;

			xPos += 10.0f;
		}
	}

public:

	std::vector<Sphere> ThreeBody;

	std::vector<const char* > texturePaths =
	{
		"src/img/blueplasma.jpg",
		"src/img/redhotflames.jpg",
		"src/img/starrynighttexture.jpg"
	};

	Sphere sphere;
	Sphere sphere2;
	Sphere sphere3;

	// since a skybox is a cube, it gets instantiated here, but the scene mgr deals with it.
	Skybox skybox;
	
};