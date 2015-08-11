/******************************************************************************
File	:	FrameWork.h
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