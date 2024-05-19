#pragma once

#include "Square.h"
#include "Cube.h"
#include "Sphere.h"

#define SHOULD_LOAD_SQUARE 0
#define SHOULD_LOAD_CUBE 1
#define SHOULD_LOAD_SPHERE 0

class ObjMgr
{
public:
	void SetupObjects()
	{
		if (SHOULD_LOAD_SQUARE)
			square.SetupSquare();

		if (SHOULD_LOAD_CUBE)
			cube.SetupCube();

		if (SHOULD_LOAD_SPHERE)
		{
			sphere.printSelf();
		}
			
	}

	Square square;
	Cube cube;
	Sphere sphere{1.0f, 36, 18, true, 2};

};