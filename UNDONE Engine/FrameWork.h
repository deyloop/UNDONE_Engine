/******************************************************************************
File	:	FrameWork.h
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

#ifndef _FrameWork_H_
#define _FrameWork_H_

//includes
#include "ISceneManager.h"
#include "IWindowUser.h"
#include "IGraphicsUser.h"
#include "UnFramework.h"
#include <vector>
using std::vector;

namespace UNDONE_ENGINE {
	class Scene;
	class Timer;
	class InputHandeller;
	struct InputContext;
	class ObjectBuffer;
	class GraphicsEngine;
	class Window;
	class SystemComponent;
	struct SceneStack;
	/*-----------------------------------------------------------------------------
	The Engine is resposible for nearly everything that hapens in this application.
	It Handles the window, tells all the components what to do at events and all
	that.
	-----------------------------------------------------------------------------*/
	class  FrameWork : public IWindowUser, public IGraphicsUser,
					   public ISceneManager, public UnFramework {
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

		const int   GetScreenHieght( ) const;
		const int   GetScreenWidth( ) const;
		const float GetElapsedTime( ) const;
		const float GetFPS( ) const;
		
		void ChangeScene(Scene* pScene);
		void AddScene	(Scene* pScene);
		void RemoveScene(Scene* pScene);
		void LoadScene	(Scene* pScene);
		void UnloadScene(Scene* pscene);

		virtual vector<InputContext>& GetInputContextListForEditing( );

	private:
		void				Pause(bool rendering, bool timer);
		static void			Load_scene_proc(FrameWork* pFramework, Scene* pScene);

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

		vector<Scene*>	m_SceneList;
		SceneStack*		m_pSceneStack;
	};
};
#endif