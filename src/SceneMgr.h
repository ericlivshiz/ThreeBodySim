#pragma once

#include "objects/ObjectMgr.h"
#include "controls/ControlMgr.h"

class SceneMgr
{
public:
	void SetupScene()
	{
		objmgr.SetupObjects();
	}

public:
	ObjectMgr objmgr;
	ControlMgr ctrlmgr;
};