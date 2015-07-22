/******************************************************************************
Project	:	UNDONE Engine
File	:	SceneStack.h
Author	:	Anurup Dey

Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>

This file is part of UNDONE-Engine.

UNDONE-Engine can not be copied and/or distributed without the express
permission of Anurup Dey. Unauthorized copying of this file, via any
medium is strictly prohibited.

Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef SCENESTACK_H
#define SCENESTACK_H

#include <vector>
using std::vector;

namespace UNDONE_ENGINE {
	class Scene;
	/*-------------------------------------------------------------------------
	This struct represents and encapsulates the stack of Scenes.
	------------------------------------------------------------------------*/
	struct SceneStack {
		void Push_Scene(Scene* pScene);
		void Pop_State( );
	private:
		vector<Scene*> Scene_stack;
	};
}
#endif