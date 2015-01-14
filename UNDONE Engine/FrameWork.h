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
#include "ObjectBuffer.h"				//Sort of like a factory object
#include "InputHandeller.h"				//Makes handling input easy
#include "Timer.h"						//For keeping the time.

/*-----------------------------------------------------------------------------
Interface for the Application Component. The application component is an object 
which defines and handles application specific tasks like loading and specifying
game objects, thier interaction and games logic, etc.
-----------------------------------------------------------------------------*/
class UNDONE_API IApp{
public:
	virtual void LoadScene(ObjectBuffer* pObjectBuffer/*context acceptors etc*/) = 0;
	virtual void Update(/*parameters to be decided*/)							 = 0;
};

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	The Engine is resposible for nearly everything that hapens in this application.
	It Handles the window, tells all the components what to do at events and all
	that.
	-----------------------------------------------------------------------------*/
	class UNDONE_API FrameWork : public IWindowUser, public IFrameWork {
	public:
		FrameWork(IApp* pApp);
		~FrameWork( ) { Release( ); }

		bool Initialise(char* title,
						int width, int height, bool windowed = true);

		void Release( );
		void Run( );
		void ToggleFullscreen( );
		virtual void OnMinimized( );
		virtual void OnResize(int newHieght,
							  int newWidth,
							  int oldHieght,
							  int oldWidth);

		void  OnCreateContext( ) { };
		const int   GetScreenHieght( ) const;
		const int   GetScreenWidth( ) const;
		const float GetElapsedTime( ) const;
		const float GetFPS( ) const;

		virtual vector<InputContext>& GetInputContextListForEditing( );

	private:
		void				Pause(bool rendering, bool timer);

		IApp*				m_pApplication;
		Window*				m_pUserWindow;
		SystemComponent*	m_pSystemComponent;
		GraphicsEngine*		m_pGraphicsEngine;
		ObjectBuffer*		m_pObjectBuffer;
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