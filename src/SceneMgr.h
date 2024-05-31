#pragma once

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

public:
	ObjectMgr objmgr;
	ControlMgr ctrlmgr;
};