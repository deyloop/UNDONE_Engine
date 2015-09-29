/******************************************************************************
File	:	WindowsSystemComponent.h
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

#ifndef _WINSYSCOMP_H_
#define _WINSYSCOMP_H_

#ifdef _WIN32
#define _WINDOWS_OS_
	
//includes
#include <Windows.h>			//Win32 API header file.
#include <String>				//For strings.

#include "SystemComponent.h"	//System Component Interface which this class
								//will inherit.
#include <glew.h>				//The GL Extention Wrangler
#include <wglew.h>
#include <io.h>
#include <Fcntl.h>
#include <deque>
using namespace std;

#define _ClassName "XXXANURUPHEXClassXXX"	//the class name that will be registered.
#define NUMWINDOWS 1

#include "UNDONE_Engine_declr.h"

namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	A window entry is an entry representation into the WindowDatabase. Its stores 
	Window attributes like handle, pointer to event handeller, etc.
	-----------------------------------------------------------------------------*/
	struct WindowEntry {
		HWND					m_WindowsHandle;
		IWindowEventHandeller*	m_EventHandeller;
		HGLRC					m_GLRenderContext;
		HDC						m_DeviceContext;
	};

	/*----------------------------------------------------------------------------
	the Window handeler has the job of maintaing the details about all the windows
	created withing the application. It is only accessed by a WindowsSystemComponent
	instance.
	----------------------------------------------------------------------------*/
	struct WindowDataBase {
	public:
		WindowDataBase( );
		WindowHandle		AddWindow(HWND hWnd, IWindowEventHandeller* pEventHandeller);
		WindowPlacementPtr	AddWindowPlacement(WINDOWPLACEMENT wndplcmnt);

		WINDOWPLACEMENT*	GetWindowPlacement(WindowPlacementPtr wnplcmntptr);
		HWND				GetHWND(WindowHandle Handle);
		OpenGLContext		GetGLContext(WindowHandle Handle);
		HGLRC&				GetWindowsGLContext(WindowHandle Handle);

		HDC&				GetWindowsDeviceContext(WindowHandle Handle);

		DeviceContext		GetDeviceContext(WindowHandle Handle);

		IWindowEventHandeller*	GetEventHandeller(WindowHandle handle);
		IWindowEventHandeller*  GetEventHandeller(HWND handle);
		bool					SlotAvalable( );
        UINT                    GetNumWindows( ) { return num_Windows; }

	private:
		UINT			num_Windows;
		UINT			num_Placements;
		WindowEntry		Windows[NUMWINDOWS];
		WINDOWPLACEMENT WindowPlacements[NUMWINDOWS];
	};

	/*----------------------------------------------------------------------------
	Windows Operating System Specific System Component which provides the Win32
	specific functions in an abstracted way. This is a singleton class.
	-----------------------------------------------------------------------------*/
	class WindowsSystemComponent : public SystemComponent {
	public:

		~WindowsSystemComponent( ) { Release( ); }

		UNDONE_API static WindowsSystemComponent* GetWindowsInstance( );

		UNDONE_API bool Initialise(HINSTANCE hInstance, string ApplicationName);
		UNDONE_API void Release( );

		HINSTANCE	getHInstance( ) { return m_appInstance; }

		UNDONE_API int GetInputEvent(InputEvent* pEvent,__int64 given_time);

		UNDONE_API bool CreateGLContext(WindowHandle handle,
							 PixelFormatParameters PixelParams,
							 ContextCreationPrameters ContextParams,
							 OpenGLContext& OGLContext,
							 DeviceContext& DevContext);
		UNDONE_API void GetDeviceDisplayMode(char* DeviceName, DisplayMode& devMode);
		UNDONE_API bool SetDeviceDisplayMode(char* DeviceName, DisplayMode newMode, bool tellSys = false);
		UNDONE_API void Swipe_Buffers(DeviceContext context);
		UNDONE_API void ReleaseGLContext(OpenGLContext context);

		UNDONE_API void ShowMessage(char* message, char* tittle);
		void Post_Quit_Mesage(int returncode) { PostQuitMessage(returncode); }

		UNDONE_API WindowHandle CreateNewWindow(char* title, WindowStyle style,
											 int width, int hieght,
											 IWindowEventHandeller* pEventHandeller
											 );
		UNDONE_API void AdjustWindow(WindowHandle handle, int width, int hieght);
		UNDONE_API void ShowWindow_(WindowHandle handle);
		UNDONE_API void UpdateWindow_(WindowHandle handle);
		UNDONE_API WindowPlacementPtr GetWindowPlacement_(WindowHandle handle);
		UNDONE_API void SetWindowPlacement_(WindowHandle handle,
										 WindowPlacementPtr winplcemnet);
		UNDONE_API void UpdateWindowPlacement(WindowHandle handle,
										   WindowPlacementPtr* pWndPlcment);
		UNDONE_API void SetWindowStyle(WindowHandle handle, WindowStyle style);
        UNDONE_API void SetWindowTittle( WindowHandle window, const char* newTitle );
        UNDONE_API void setSwapInterval( int interval );

		inline __int64 GetSystemTickRate( ) {
			__int64 rate;
			QueryPerformanceFrequency((LARGE_INTEGER *)&rate);
			return rate;
		};
		inline __int64 GetCurrentTickCount( ) {
			__int64 count;
			QueryPerformanceCounter((LARGE_INTEGER *)&count);
			return count;
		};


		UNDONE_API void FrameInput( );
        UNDONE_API void NewInputFrame();

		unsigned GetSystemDirectory_(char* buffer, int size ) { return GetWindowsDirectory(buffer, size); }

		static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT msg,
											  WPARAM wParam,
											  LPARAM lParam);
	private:
		WindowsSystemComponent( );
		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
								 WPARAM wParam,
								 LPARAM lParam);
		bool InitializeGLEW( );
		void Reset_KeyBoard( );

		HINSTANCE m_appInstance;
		HANDLE    m_hMutex;
		HDC		  m_hDeviceContext;
		HGLRC	  m_hRenderContext;

		bool	  CheckMutex(string Appname);
		void	  RegisterWindowClass( );
		int       EvaluateKeyBaordInput(const RAWKEYBOARD& rawKB, InputEvent* pEvent);

		bool	  m_ClassRegistered;
		bool	  m_DevicesRegistered;
		bool	  m_GLEWInitialized;
		bool	  m_First_Input_loop;

		WindowDataBase m_WindowDB;
		static WindowsSystemComponent* pWindowsInstance;

		//input
		RAWINPUTDEVICE m_KeyBoard_Device;
		bool   Currentkeysync;
		POINTS ptPrevCursor;
		bool   first;
		bool   keyinit;
		bool   KeyPressed[256];
		bool   KeyPosted[256];
		std::deque<MSG> msgque;
	};
};
#endif
#endif