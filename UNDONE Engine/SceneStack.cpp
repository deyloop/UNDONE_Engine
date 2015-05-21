/******************************************************************************
Project	:	UNDONE Engine
File	:	SceneStack.cpp
Author	:	Anurup Dey
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