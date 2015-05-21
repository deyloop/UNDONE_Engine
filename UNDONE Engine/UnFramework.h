/******************************************************************************
Project	:	UNDONE Engine
File	:	UnFramework.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UN_FRAMEWORK_H_
#define _UN_FRAMEWORK_H_

#include "UNDONE_Engine_declr.h"
#include <vector> //going to cause some trouble
using std::vector;

namespace UNDONE_ENGINE{
	class UnObjectBuffer;
};

/*-----------------------------------------------------------------------------
Interface for the Application Component. The application component is an object
which defines and handles application specific tasks like loading and specifying
game objects, thier interaction and games logic, etc.
-----------------------------------------------------------------------------*/
class UNDONE_API IApp{
public:
	virtual void LoadScene(UNDONE_ENGINE::UnObjectBuffer* pObjectBuffer/*context acceptors etc*/) = 0;
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

		virtual bool Initialise(char* title,
								int width, int height, bool windowed=true)	= 0;

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
	
		virtual vector<InputContext>& GetInputContextListForEditing()	= 0;
	};

	
}
#endif