/******************************************************************************
Project	:	UNDONE Engine
File	:	UnFramework.h
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

#ifndef _UN_FRAMEWORK_H_
#define _UN_FRAMEWORK_H_

#include "UNDONE_Engine_declr.h"
#include "unEngineInterfaces.h"
#include <vector> //going to cause some trouble
using std::vector;

namespace UNDONE_ENGINE{
	class unObjectBuffer;
};

/*-----------------------------------------------------------------------------
Interface for the Application Component. The application component is an object
which defines and handles application specific tasks like loading and specifying
game objects, thier interaction and games logic, etc.
-----------------------------------------------------------------------------*/
class IApp{
public:
	virtual void LoadScene( ) = 0;
	virtual void Update(/*parameters to be decided*/) = 0;
};

namespace UNDONE_ENGINE{

	class Scene;
	struct InputContext;

	/*-------------------------------------------------------------------------
	This is the interface for the main framework. The framework is the primary
	interface for the application to access the functionailty of the Engine.
	-------------------------------------------------------------------------*/
	class UnFramework{
	public:
		virtual ~UnFramework(){};

		virtual bool Initialise(char* config_file)	= 0;

		virtual void Release()											= 0;
		virtual void Run()												= 0;
		virtual void ToggleFullscreen()									= 0;

		virtual const int   GetScreenHieght() const						= 0;
		virtual const int   GetScreenWidth() const						= 0;
		virtual const float GetElapsedTime() const						= 0;
		virtual const float GetFPS() const								= 0;
	
		virtual void ChangeScene(Scene* pScene)							= 0;
		virtual void AddScene	(Scene* pScene)							= 0;
		virtual void RemoveScene(Scene* pScene)							= 0;
		virtual void LoadScene	(Scene* pScene)							= 0;
		virtual void UnloadScene(Scene* pscene)							= 0;
	
		
		unInput*         Input;
		unGraphics*      Graphics;
		unObjectBuffer*  Objectbuffer;

	};

	
}
#endif