/******************************************************************************
File	:	FrameWork.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _FrameWork_H_
#define _FrameWork_H_

//includes
#include "UNDONE_Engine_declr.h"		//For the api declaration.
#include "SystemComponent.h"			//header for the System Interface.
#include "Window.h"						//header for the Window class
#include "GraphicsEngine.h"				//header for the graphics engine 
#include "DObjectBuffer.h"				//For gameObject storage.
//#include "ObjectBuffer.h"				//Sort of like a factory object
#include "InputHandeller.h"				//Makes handling input easy
#include "Timer.h"						//For keeping the time.

/*-----------------------------------------------------------------------------
Interface for the Application Component. The application component is an object 
which defines and handles application specific tasks like loading and specifying
game objects, thier interaction and games logic, etc.
-----------------------------------------------------------------------------*/
class UNDONE_API IApp{
public:
	virtual void LoadScene(UNDONE_ENGINE::DObjectBuffer* pObjectBuffer/*context acceptors etc*/) = 0;
	virtual void Update(/*parameters to be decided*/)							 = 0;
};

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	The Engine is resposible for nearly everything that hapens in this application.
	It Handles the window, tells all the components what to do at events and all
	that.
	-----------------------------------------------------------------------------*/
	class  FrameWork : public IWindowUser, public IFrameWork {
	public:
		UNDONE_API FrameWork(IApp* pApp);
		UNDONE_API ~FrameWork( ) { Release( ); }

		UNDONE_API bool Initialise(char* title,
						int width, int height, bool windowed = true);

		UNDONE_API void Release( );
		UNDONE_API void Run( );
		UNDONE_API void ToggleFullscreen( );
		virtual void OnMinimized( );
		virtual void OnResize(int newHieght,
							  int newWidth,
							  int oldHieght,
							  int oldWidth);

		void  OnCreateContext( ) { };
		UNDONE_API const int   GetScreenHieght( ) const;
		UNDONE_API const int   GetScreenWidth( ) const;
		UNDONE_API const float GetElapsedTime( ) const;
		UNDONE_API const float GetFPS( ) const;

		UNDONE_API virtual vector<InputContext>& GetInputContextListForEditing( );

	private:
		void				Pause(bool rendering, bool timer);

		IApp*				m_pApplication;
		Window*				m_pUserWindow;
		SystemComponent*	m_pSystemComponent;
		GraphicsEngine*		m_pGraphicsEngine;
		DObjectBuffer*		m_pObjectBuffer;
		InputHandeller*		m_pInputHandeller;
		Timer*				m_pTimer;

		bool			m_running;

		bool            m_active;

		bool            m_renderingPaused;
		bool            m_timerPaused;
		int             m_renderingPauseCount;
		int             m_timerPauseCount;
		bool            m_closing;
	};
};
#endif