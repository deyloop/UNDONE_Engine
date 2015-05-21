/******************************************************************************
File	:	Window.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_
//inculudes
#include "SystemComponent.h"


namespace UNDONE_ENGINE {
	class IWindowUser;


	/*-----------------------------------------------------------------------------
	Summary: This is the header for the Windows window wrapper.
	-----------------------------------------------------------------------------*/
	class Window : IWindowEventHandeller {
	public:
		Window( );
		void			Initialize(char* title,
								   IWindowUser* winUser,
								   int width, int height,
								   bool windowed = true);

		void			ToggleFullscreen( );

		WindowHandle	GetHandle( ) { return m_hWnd; }

		virtual void OnCreate( );
		virtual void OnPaint( );
		virtual void OnMinimized( );
		virtual void OnMaximized(int newWidth, int newHieght);
		virtual void OnResize(int newWidth, int newHieght);
		virtual void OnDestroy( );

		int			m_width;
		int			m_hieght;
		int			m_fullscreenwidth;
		int			m_fullscreenheight;
		bool		m_windowed;

	private:

		WindowHandle		m_hWnd;
		IWindowUser*		m_User;
		SystemComponent*	m_pSystem;



		WindowPlacementPtr	m_placement;
		char*				m_title;
	};
}
#endif
