/******************************************************************************
File	:	Window.cpp
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
#include "Window.h"
#include "IWindowUser.h"

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	Summary: Default costructor.
	-----------------------------------------------------------------------------*/
	Window::Window( ) {
		m_hieght = 0;
		m_width = 0;
		m_fullscreenwidth = 0;
		m_fullscreenheight = 0;
		m_title = nullptr;
		m_windowed = true;
	}

	/*-----------------------------------------------------------------------------
	Summary: Window Intialiser. Sets user defined values and creates the window.
	Parameters:
	[IN]	*title	-the desired title for the window.
	[IN]	*hInstance	-a pointer to the Application Instance.
	[IN]	width	-the desired width for the window.
	[IN]	height	-the desired height for the window.
	[IN]	windowed-indicates the window mode. True for windowed, false for full-
	screen.
	-----------------------------------------------------------------------------*/
	void Window::Initialize(const char* title, IWindowUser* winUser,
							int width, int height, bool windowed) {
		m_pSystem = SystemComponent::GetInstance( );
		m_width = width;
		m_hieght = height;
		m_title = const_cast<char*>(title);
		m_windowed = windowed;
		m_User = winUser;

		m_hWnd = m_pSystem->CreateNewWindow(m_title,
											m_windowed ? WSS_OVERLAPPINGWINDOW : WSS_FULLSCREENWINDOW,
											m_width,
											m_hieght,
											this
											);

		//Adjust window to desired size.
		m_pSystem->AdjustWindow(m_hWnd, m_width, m_hieght);
		m_pSystem->ShowWindow_(m_hWnd);
		m_pSystem->UpdateWindow_(m_hWnd);

		//Save the Window position etc.
		m_placement = m_pSystem->GetWindowPlacement_(m_hWnd);
	}

	/*-----------------------------------------------------------------------------
	Summary: Toggles between Fullscreen and windowed modes.
	-----------------------------------------------------------------------------*/
	void Window::ToggleFullscreen( ) {
		m_windowed = !m_windowed;
		if (m_windowed) {
			//going to windowed mode
			m_pSystem->SetWindowStyle(m_hWnd, WSS_OVERLAPPINGWINDOW);
			m_pSystem->SetWindowPlacement_(m_hWnd, m_placement);
		} else {
			// Save current location/size
			m_placement = m_pSystem->GetWindowPlacement_(m_hWnd);

			// Going to fullscreen mode
			m_pSystem->SetWindowStyle(m_hWnd, WSS_FULLSCREENWINDOW);
			m_pSystem->AdjustWindow(m_hWnd, m_fullscreenwidth, m_fullscreenheight);
			m_pSystem->ShowWindow_(m_hWnd);
			m_pSystem->UpdateWindow_(m_hWnd);
		}
	}

	/*-----------------------------------------------------------------------------
	THis callback function is called by the system when the window is created.
	-----------------------------------------------------------------------------*/
	void Window::OnCreate( ) {

	}

	/*-----------------------------------------------------------------------------
	This callback function is called when the system wants the window to redraw its
	contents.
	-----------------------------------------------------------------------------*/
	void Window::OnPaint( ) {

	}

	/*-----------------------------------------------------------------------------
	This callback funstion is called when the window is minimized.
	-----------------------------------------------------------------------------*/
	void Window::OnMinimized( ) {
		if (m_User) {
			m_User->OnMinimized( );
		}
	}

	/*-----------------------------------------------------------------------------
	This callback function is called by the system when the window is maximixed.
	PArameters:
	[IN]	newWidth	-	the new width now.
	[IN]	newHight	-	the new hieght now.
	-----------------------------------------------------------------------------*/
	void Window::OnMaximized(int newWidth, int newHieght) {
		OnResize(newWidth, newHieght);
	}

	/*-----------------------------------------------------------------------------
	Called by the system when window is resized to other dimension.
	Parameters:
	[IN]	newWidth	-	the new width now.
	[IN]	newHight	-	the new hieght now.
	-----------------------------------------------------------------------------*/
	void Window::OnResize(int newWidth, int newHieght) {
		int oldH = m_hieght;
		int oldW = m_width;

		m_hieght = newHieght;
		m_width = newWidth;

		if (m_User) {
			m_User->OnResize(newHieght, newWidth, oldH, oldW);
		}

	}

	/*-----------------------------------------------------------------------------
	Called by the system when the window is destroyed.
	-----------------------------------------------------------------------------*/
	void Window::OnDestroy( ) {
		//tell the pressess to stop and 
		//that it's time to qiut.
		m_pSystem->Post_Quit_Mesage(0);
	}

}
///////////////////////////////////////////////////////////////////////////////


