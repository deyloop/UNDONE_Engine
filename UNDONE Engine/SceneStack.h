/******************************************************************************
Project	:	UNDONE Engine
File	:	SceneStack.h
Author	:	Anurup Dey
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