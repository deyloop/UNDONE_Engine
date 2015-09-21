/******************************************************************************
Project	:	UNDONE Engine
File	:	SystemComponent.h
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

#ifndef UNDONE_SYSTEMCOMPONENT_H_
#define UNDONE_SYSTEMCOMPONENT_H_

#include "UNDONE_Engine_declr.h"//For the export declaration.
#include "InputEvent.h"			//for despatching events.

namespace UNDONE_ENGINE {
	class IWindowEventHandeller {
	public:
		virtual void OnCreate( ) = 0;
		virtual void OnPaint( ) = 0;
		virtual void OnMinimized( ) = 0;
		virtual void OnMaximized(int newWidth, int newHieght) = 0;
		virtual void OnResize(int newWidth, int newHieght) = 0;
		virtual void OnDestroy( ) = 0;
	};

	enum WindowStyle {
		WSS_OVERLAPPINGWINDOW = 0,
		WSS_FULLSCREENWINDOW
	};

	enum PixelType {
		RGBA = 0x2029,
		COLORINDEX = 0x202C
	};

	enum AccelerationType {
		NO_ACCELERATION = 0x2025,
		GENERIC_ACCELERATION = 0x2025,
		FULL_ACCELERATION = 0x2027
	};

	enum SwapMethod {
		SWAP_EXCHANGE = 0x2028,
		SWAP_COPY = 0x2029,
		SWAP_UNDEFINED = 0x202A
	};

	struct PixelFormatParameters {
		bool				bDraw_to_Window;
		bool				bSupport_OpenGL;
		bool				bDouble_Buffer;
		bool				bTransparency;
		PixelType			ePixel_Type;
		AccelerationType	eAcceleration;
		SwapMethod			eSwap_Method;
		int					iColor_Bits;
		int					iDepth_Bits;
		int					iStencil_Bits;
	};

	enum GL_Context_Profile {
		CONTEXT_CORE_PROFILE = 0x00000001,
		CONTEXT_COMPATIBILITY_PROFILE = 0x00000002,
		CONTEXT_PROFILE_MASK = 0x9126
	};

	struct ContextCreationPrameters {
		int					iMajor_Version;
		int					iMinor_Version;
		GL_Context_Profile	eProfile;
	};

	struct DisplayMode {
		unsigned char* DeviceName;
		unsigned long BitsPerPel;
		unsigned long PelsWidth;
		unsigned long PelsHeight;
		unsigned long DisplayFrequency;
	};

	typedef  unsigned int WindowHandle;
	typedef  unsigned int WindowPlacementPtr;
	typedef  unsigned int OpenGLContext;
	typedef	 unsigned int DeviceContext;

	/*-----------------------------------------------------------------------------
	Interface for OS specific function wrapper which abstracts the OS functions.
	----------------------------------------------------------------------------*/
	class SystemComponent {
	public:
		UNDONE_API static SystemComponent* GetInstance( );

		virtual bool CreateGLContext(WindowHandle handle,
									 PixelFormatParameters PixelParams,
									 ContextCreationPrameters ContextParams,
									 OpenGLContext& OGLContext,
									 DeviceContext& DevContext) = 0;
		virtual void GetDeviceDisplayMode(char* DeviceName, DisplayMode& devMode) = 0;
		virtual bool SetDeviceDisplayMode(char* DeviceName, DisplayMode newMode, bool tellSys = false) = 0;
		virtual void Swipe_Buffers(DeviceContext context) = 0;
		virtual void ReleaseGLContext(OpenGLContext context) = 0;

		virtual int GetInputEvent(InputEvent* pEvent) = 0;
		virtual void ShowMessage(char* message, char* tittle) = 0;
		virtual void Post_Quit_Mesage(int returncode) = 0;
		virtual void NewFrame() = 0;

		virtual WindowHandle CreateNewWindow(char* title, WindowStyle style,
											 int width, int hieght,
											 IWindowEventHandeller* pEventHandeller
											 ) = 0;
		virtual void AdjustWindow(WindowHandle handle, int width, int hieght) = 0;
		virtual void ShowWindow_(WindowHandle handle) = 0;
		virtual void UpdateWindow_(WindowHandle handle) = 0;
		virtual WindowPlacementPtr GetWindowPlacement_(WindowHandle handle) = 0;
		virtual void SetWindowPlacement_(WindowHandle handle,
										 WindowPlacementPtr winplcemnet) = 0;
		virtual void UpdateWindowPlacement(WindowHandle handle,
										   WindowPlacementPtr* pWndPlcment) = 0;
		virtual void SetWindowStyle(WindowHandle handle, WindowStyle style) = 0;

		virtual __int64 GetSystemTickRate( ) = 0;
		virtual __int64 GetCurrentTickCount( ) = 0;

		virtual void FrameInput( ) = 0;

		virtual unsigned GetSystemDirectory_(char* buffer, int size ) = 0;

	private:
		static SystemComponent* pInstance;
	};
}
/*-----------------------------------------------------------------------------
Definition of the main function.
-----------------------------------------------------------------------------*/
#define main DAC_main
int main( );

#endif