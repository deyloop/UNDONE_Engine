/******************************************************************************
Project	:	UNDONE Engine
File	:	SceneStack.cpp
Author	:	Anurup Dey

		Copyright (C) 2015 Anurup Dey 
		<anu.rup.dey98@gmail.com>

	This file is part of UNDONE-Engine.

	UNDONE-Engine can not be copied and/or distributed without the express
	permission of Anurup Dey. Unauthorized copying of this file, via any
	medium is strictly prohibited.

	Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "SceneStack.h"
#include "Scene.h"

namespace UNDONE_ENGINE {
	void SceneStack::Push_Scene(Scene* pScene) {
		Scene_stack.push_back(pScene);
	}

	void SceneStack::Pop_State( ) {
		Scene_stack.pop_back( );
	}
}