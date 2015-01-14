/******************************************************************************
File	:	WindowsSystemComponent.h
Author	:	Anurup Dey
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
	class UNDONE_API WindowsSystemComponent : public SystemComponent {
	public:

		~WindowsSystemComponent( ) { Release( ); }

		static WindowsSystemComponent* GetWindowsInstance( );

		bool Initialise(HINSTANCE hInstance, string ApplicationName);
		void Release( );

		HINSTANCE	getHInstance( ) { return m_appInstance; }

		int GetInputEvent(InputEvent* pEvent);

		bool CreateGLContext(WindowHandle handle,
							 PixelFormatParameters PixelParams,
							 ContextCreationPrameters ContextParams,
							 OpenGLContext& OGLContext,
							 DeviceContext& DevContext);
		void GetDeviceDisplayMode(char* DeviceName, DisplayMode& devMode);
		bool SetDeviceDisplayMode(char* DeviceName, DisplayMode newMode);
		void Swipe_Buffers(DeviceContext context);
		void ReleaseGLContext(OpenGLContext context);

		void ShowMessage(char* message, char* tittle);
		void Post_Quit_Mesage(int returncode) { PostQuitMessage(returncode); }

		virtual WindowHandle CreateNewWindow(char* title,WindowStyle style,
											 int width, int hieght,
											 IWindowEventHandeller* pEventHandeller
											 );
		virtual void AdjustWindow(WindowHandle handle,int width, int hieght);
		virtual void ShowWindow_(WindowHandle handle);
		virtual void UpdateWindow_(WindowHandle handle);
		virtual WindowPlacementPtr GetWindowPlacement_(WindowHandle handle);
		virtual void SetWindowPlacement_(WindowHandle handle,
										 WindowPlacementPtr winplcemnet);
		virtual void UpdateWindowPlacement(WindowHandle handle,
										   WindowPlacementPtr* pWndPlcment);
		virtual void SetWindowStyle(WindowHandle handle, WindowStyle style);

		virtual inline __int64 GetSystemTickRate( ) {
			__int64 rate;
			QueryPerformanceFrequency((LARGE_INTEGER *)&rate);
			return rate;
		};
		virtual inline __int64 GetCurrentTickCount( ) {
			__int64 count;
			QueryPerformanceCounter((LARGE_INTEGER *)&count);
			return count;
		};

		virtual void HandleWindowEvents( );	//Depreciated.

		static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT msg,
											  WPARAM wParam,
											  LPARAM lParam);
	private:
		WindowsSystemComponent( );
		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg,
								 WPARAM wParam,
								 LPARAM lParam);
		bool InitializeGLEW( );

		HINSTANCE m_appInstance;
		HANDLE    m_hMutex;
		HDC		  m_hDeviceContext;
		HGLRC	  m_hRenderContext;

		bool	  CheckMutex(string Appname);
		void	  RegisterWindowClass( );

		bool	  m_ClassRegistered;
		bool	  m_DevicesRegistered;
		bool	  m_GLEWInitialized;

		WindowDataBase m_WindowDB;
		static WindowsSystemComponent* pWindowsInstance;
	};
};
#endif
#endif