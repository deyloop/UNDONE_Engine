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
using namespace UNDONE_ENGINE;

/*-----------------------------------------------------------------------------
The interface for the object to be using the Window class.
-----------------------------------------------------------------------------*/
class IWindowUser	{
public:
	virtual void OnMinimized()				= 0;
	virtual void OnResize(int newHieght,
						   int newWidth,
						   int oldHieght,
						   int oldWidth)	= 0;
};


/*-----------------------------------------------------------------------------
Summary: This is the header for the Windows window wrapper.
-----------------------------------------------------------------------------*/
class Window	: IWindowEventHandeller{
public:
	Window();
	void			Initialize(char* title, 
							   IWindowUser* winUser,
							   int width, int height,
							   bool windowed = true);

	void			ToggleFullscreen();

	WindowHandle	GetHandle()								{ return m_hWnd; }

	virtual void OnCreate();
	virtual void OnPaint();
	virtual void OnMinimized();
	virtual void OnMaximized(int newWidth, int newHieght);
	virtual void OnResize(int newWidth, int newHieght);
	virtual void OnDestroy();

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
#endif
