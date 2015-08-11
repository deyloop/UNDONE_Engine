/******************************************************************************
Project	:	UNDONE Engine
File	:	SceneStack.h
Author	:	Anurup Dey

				Copyright (C) 2015  Anurup Dey

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

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