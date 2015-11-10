/******************************************************************************
File	:	WindowsSystemComponent.cpp
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

#include "WindowsSystemComponent.h"
#include <iostream>
#include <deque>

#ifdef _WINDOWS_OS_
namespace UNDONE_ENGINE {
	
	SystemComponent* SystemComponent::pInstance = nullptr;
	WindowsSystemComponent* WindowsSystemComponent::pWindowsInstance = nullptr;

	/*-----------------------------------------------------------------------------
	Defualt Constructor
	-----------------------------------------------------------------------------*/
	WindowsSystemComponent::WindowsSystemComponent( ) {
		m_appInstance = NULL;
		m_hMutex = NULL;
		m_ClassRegistered = false;
		m_DevicesRegistered = false;
		m_GLEWInitialized = false;

	}

	/*-----------------------------------------------------------------------------
	This fuction is used to get the instance of the singleton SystemComponent
	class. It creates an instance in the heap if the instance is not created already
	and the returns this instance pointer to the caller.
	-----------------------------------------------------------------------------*/
	SystemComponent* SystemComponent::GetInstance( ) {
		if (SystemComponent::pInstance==nullptr) {
			pInstance = WindowsSystemComponent::GetWindowsInstance( );
		}
		return pInstance;
	}

	/*-----------------------------------------------------------------------------
	This is the getter for the instance of the single ton WindowsSystemComponent.
	-----------------------------------------------------------------------------*/
	WindowsSystemComponent* WindowsSystemComponent::GetWindowsInstance( ) {
		if (pWindowsInstance==nullptr) {
			pWindowsInstance = new WindowsSystemComponent( );
		}
		return pWindowsInstance;
	}

	/*-----------------------------------------------------------------------------
	Sets the Windows System Components up.
	Parameters:
	[IN]	hInstance	-	the handle the the application instance.
	Returns: true on success, false otherwise.
	-----------------------------------------------------------------------------*/
	bool WindowsSystemComponent::Initialise(HINSTANCE hInstance, string ApplicationName) {
		m_appInstance = hInstance;

		//Check if the App already has an instance running.
		//if yes, the do not initialize.
		if (!CheckMutex(ApplicationName)) return false;

		first = true;
		keyinit = false;
		for (auto& key : KeyPressed) key = false;
		for (auto& key : KeyPosted) key = false;
		Currentkeysync = true;

		RegisterWindowClass( );

		return true;
	}

	/*-----------------------------------------------------------------------------
	Cleans up after the Component is destroyed. This is generally called when the
	Application exits. Put all the system cleanup code, like API release calls,
	here, so that memory can be freed.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::Release( ) {
		//I don't see much needing to happen.

	}
	/*-----------------------------------------------------------------------------
	Checks if the Application already has an instance running or not.
	Returns: true if no instance,
	false if there is an instance running.
	-----------------------------------------------------------------------------*/
	bool WindowsSystemComponent::CheckMutex(string Appname) {
		m_hMutex = CreateMutex(NULL, 1, Appname.c_str( ));
		if (GetLastError( )==ERROR_ALREADY_EXISTS) {
			MessageBox(NULL, "This application already runs!",
					   "Multiple Instances Found.",
					   MB_ICONINFORMATION|MB_OK);
			return false;
		}
		return true;
	}

	/*-----------------------------------------------------------------------------
	Registers the Window Class.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::RegisterWindowClass( ) {
		if (m_ClassRegistered) {
			//Already Registered
			return;
		}
		WNDCLASSEX windef;		//the object that holds the definition of our class
		//while window Class registration.
		memset(&windef, 0, sizeof(WNDCLASSEX));

		windef.cbSize = sizeof(WNDCLASSEX);
		windef.style = CS_DBLCLKS|CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
		windef.lpfnWndProc = (WNDPROC)WindowsSystemComponent::staticWndProc;
		windef.cbClsExtra = 0;
		windef.cbWndExtra = 0;
		windef.hInstance = m_appInstance;
		windef.hIcon = NULL;
		windef.hCursor = LoadCursor(NULL, IDC_ARROW);
		windef.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		windef.lpszMenuName = NULL;
		windef.lpszClassName = _ClassName;
		windef.hIconSm = NULL;//LoadIcon( hInstance, MAKEINTRESOURCE( IDI_CUNIT ) );

		//Register the Window Class.
		RegisterClassEx(&windef);
		m_ClassRegistered = true;
	}

	/*----------------------------------------------------------------------------
	Evaluates the rawKeyboard input and converts it into an INputEvent.
	Parameters:
	[IN]		rawKB	-	reference to the Raw keyboard data.
	[IN,OUT]	pEvent	-	pointer to the Input Event Object to which the 
							converted data will be stored.
	Returns: 
	0 for no interesting input
	1 for valid input
	-1 for error
	----------------------------------------------------------------------------*/
	int WindowsSystemComponent::EvaluateKeyBaordInput(const RAWKEYBOARD & rawKB, InputEvent * pEvent) {

		UINT virtualKey = rawKB.VKey;
		UINT scanCode   = rawKB.MakeCode;
		UINT flags      = rawKB.Flags;

		// a key can either produce a "make" or "break" scancode. this is used to differentiate between down-presses and releases
		const bool wasUp = ((flags & RI_KEY_BREAK) != 0);
		if (wasUp) pEvent->type = EVENT_KEYUP;
		else pEvent->type = EVENT_KEYDOWN;

		if (virtualKey == 255) {
			//discard 'fake keys' which are part of an 
			//escape sequence
			return 0;
		} else if (virtualKey == VK_SHIFT) {
			//correct left hand/right hand shift.
			virtualKey = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX);
		} else if (virtualKey == VK_NUMLOCK) {
			//correct pause/break and numlock silliness
			//and set extended bit.
			scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC) | 0x100;
		}

		//e0 and e1 are escape sequences used for certain special keys
		//such as PRINT and PAUSE/BREAK.
		const bool isE0 = ((flags & RI_KEY_E0) != 0);
		const bool isE1 = ((flags & RI_KEY_E1) != 0);

		if (isE1)
			//for escaped sequences, turn the virtual key code 
			//into the correct Scancode.
			//However, MapVertualKey is unable to map VK_PAUSE 
			//(its a known bug. We do that by hand.
			if (virtualKey == VK_PAUSE)
				scanCode = 0x45;
			else
				scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

		// getting a human-readable string
		UINT key = (scanCode << 16) | (isE0 << 24);
		GetKeyNameText((LONG)key, pEvent->key.KeyName, 20);

		switch (virtualKey) {
			// right-hand CONTROL and ALT have their e0 bit set
		case VK_CONTROL:
			if (isE0) {
				pEvent->key.keycode = KEY_RCTRL;
				return 1;
			} else {
				pEvent->key.keycode = KEY_LCTRL;
			}

		case VK_MENU:
			if (isE0) {
				pEvent->key.keycode = KEY_RALT;
				return 1;
			} else {
				pEvent->key.keycode = KEY_LALT;
				return 1;
			}

			// NUMPAD ENTER has its e0 bit set
		case VK_RETURN:
			if (isE0) {
				pEvent->key.keycode = KEY_NUM_ENTER;
				return 1;
			} else {
				pEvent->key.keycode = KEY_ENTER;
				return 1;
			}

			// the standard INSERT, DELETE, HOME, END, PRIOR and NEXT keys will always have their e0 bit set, but the
			// corresponding keys on the NUMPAD will not.
		case VK_INSERT:
			if (!isE0) {
				pEvent->key.keycode = KEY_NUM_0;
				return 1;
			} else {
				pEvent->key.keycode = KEY_INSERT;
				return 1;
			}

		case VK_DELETE:
			if (!isE0) {
				pEvent->key.keycode = KEY_NUM_DECIMAL;
				return 1;
			} else {
				pEvent->key.keycode = KEY_DELETE;
				return 1;
			}

		case VK_HOME:
			if (!isE0) {
				pEvent->key.keycode = KEY_NUM_7;
			} else {
				pEvent->key.keycode = KEY_HOME;
			}
			return 1;

		case VK_END:
			if (!isE0)
				pEvent->key.keycode = KEY_NUM_1;
			else
				pEvent->key.keycode = KEY_END;
			return 1;

		case VK_PRIOR:
			if (!isE0)
				pEvent->key.keycode = KEY_NUM_9;
			else
				pEvent->key.keycode = KEY_PAGEUP;
			return 1;

		case VK_NEXT:
			if (!isE0)
				pEvent->key.keycode = KEY_NUM_3;
			else
				pEvent->key.keycode = KEY_PAGEDOWN;
			return 1;

			// the standard arrow keys will always have their e0 bit set, but the
			// corresponding keys on the NUMPAD will not.
		case VK_LEFT:
			if (!isE0)
				pEvent->key.keycode = KEY_NUM_4;
			else
				pEvent->key.keycode = KEY_ARROW_LEFT;
			return 1;

		case VK_RIGHT:
			if (!isE0)
				pEvent->key.keycode = KEY_NUM_6;
			else
				pEvent->key.keycode = KEY_ARROW_RIGHT;
			return 1;

		case VK_UP:
			if (!isE0)
				pEvent->key.keycode = KEY_NUM_8;
			else
				pEvent->key.keycode = KEY_ARROW_UP;
			return 1;

		case VK_DOWN:
			if (!isE0)
				pEvent->key.keycode = KEY_NUM_2;
			else
				pEvent->key.keycode = KEY_ARROW_DOWN;
			return 1;

			// NUMPAD 5 doesn't have its e0 bit set
		case VK_CLEAR:
			if (!isE0)
				pEvent->key.keycode = KEY_NUM_5;
			else
				pEvent->key.keycode = KEY_CLEAR;
			return 1;

		case VK_ESCAPE:
			pEvent->key.keycode = KEY_ESCAPE;
			return 1;
			//Now for the Function keys

		case VK_F1:
			pEvent->key.keycode = KEY_F1;
			return 1;

		case VK_F2:
			pEvent->key.keycode = KEY_F2;
			return 1;

		case VK_F3:
			pEvent->key.keycode = KEY_F3;
			return 1;

		case VK_F4:
			pEvent->key.keycode = KEY_F4;
			return 1;

		case VK_F5:
			pEvent->key.keycode = KEY_F5;
			return 1;

		case VK_F6:
			pEvent->key.keycode = KEY_F6;
			return 1;

		case VK_F7:
			pEvent->key.keycode = KEY_F7;
			return 1;

		case VK_F8:
			pEvent->key.keycode = KEY_F8;
			return 1;

		case VK_F9:
			pEvent->key.keycode = KEY_F9;
			return 1;

		case VK_F10:
			pEvent->key.keycode = KEY_F10;
			return 1;

		case VK_F11:
			pEvent->key.keycode = KEY_F11;
			return 1;

		case VK_F12:
			pEvent->key.keycode = KEY_F12;
			return 1;
		case VK_SPACE:
			pEvent->key.keycode = KEY_SPACEBAR;
			return 1;
		case VK_LSHIFT:
			pEvent->key.keycode = KEY_LSHIFT;
			return 1;
		case VK_RSHIFT:
			pEvent->key.keycode = KEY_RSHIFT;
			return 1;
		case VK_NUMLOCK:
			pEvent->key.keycode = KEY_NUMLOCK;
			return 1;
		case VK_CAPITAL:
			pEvent->key.keycode = KEY_CAPSLOCK;
			return 1;
		case '\b':
			pEvent->key.keycode = KEY_BACKSPACE;
			return 1;
		case '\t':
			pEvent->key.keycode = KEY_TAB;
			return 1;
		case 'A':
			pEvent->key.keycode = KEY_A;
			return 1;
		case 'B':
			pEvent->key.keycode = KEY_B;
			return 1;
		case 'C':
			pEvent->key.keycode = KEY_C;
			return 1;
		case 'D':
			pEvent->key.keycode = KEY_D;
			return 1;
		case 'E':
			pEvent->key.keycode = KEY_E;
			return 1;
		case 'F':
			pEvent->key.keycode = KEY_F;
			return 1;
		case 'G':
			pEvent->key.keycode = KEY_G;
			return 1;
		case 'H':
			pEvent->key.keycode = KEY_H;
			return 1;
		case 'I':
			pEvent->key.keycode = KEY_I;
			return 1;
		case 'J':
			pEvent->key.keycode = KEY_J;
			return 1;
		case 'K':
			pEvent->key.keycode = KEY_K;
			return 1;
		case 'L':
			pEvent->key.keycode = KEY_L;
			return 1;
		case 'M':
			pEvent->key.keycode = KEY_M;
			return 1;
		case 'N':
			pEvent->key.keycode = KEY_N;
			return 1;
		case 'O':
			pEvent->key.keycode = KEY_O;
			return 1;
		case 'P':
			pEvent->key.keycode = KEY_P;
			return 1;
		case 'Q':
			pEvent->key.keycode = KEY_Q;
			return 1;
		case 'R':
			pEvent->key.keycode = KEY_R;
			return 1;
		case 'S':
			pEvent->key.keycode = KEY_S;
			return 1;
		case 'T':
			pEvent->key.keycode = KEY_T;
			return 1;
		case 'U':
			pEvent->key.keycode = KEY_U;
			return 1;
		case 'V':
			pEvent->key.keycode = KEY_V;
			return 1;
		case 'W':
			pEvent->key.keycode = KEY_W;
			return 1;
		case 'X':
			pEvent->key.keycode = KEY_X;
			return 1;
		case 'Y':
			pEvent->key.keycode = KEY_Y;
			return 1;
		case 'Z':
			pEvent->key.keycode = KEY_Z;
			return 1;
		case '1':
			pEvent->key.keycode = KEY_1;
			return 1;
		case '2':
			pEvent->key.keycode = KEY_2;
			return 1;
		case '3':
			pEvent->key.keycode = KEY_3;
			return 1;
		case '4':
			pEvent->key.keycode = KEY_4;
			return 1;
		case '5':
			pEvent->key.keycode = KEY_5;
			return 1;
		case '6':
			pEvent->key.keycode = KEY_6;
			return 1;
		case '7':
			pEvent->key.keycode = KEY_7;
			return 1;
		case '8':
			pEvent->key.keycode = KEY_8;
			return 1;
		case '9':
			pEvent->key.keycode = KEY_9;
			return 1;
		case '0':
			pEvent->key.keycode = KEY_0;
			return 1;
		case VK_OEM_COMMA:
			pEvent->key.keycode = KEY_COMMA;
			return 1;
		case VK_OEM_PERIOD:
			pEvent->key.keycode = KEY_PERIOD;
			return 1;
		case VK_OEM_MINUS:
			pEvent->key.keycode = KEY_MINUS;
			return 1;
		case VK_OEM_PLUS:
			pEvent->key.keycode = KEY_PLUS;
			return 1;
		case VK_SUBTRACT:
			pEvent->key.keycode = KEY_NUM_MINUS;
			return 1;
		case VK_ADD:
			pEvent->key.keycode = KEY_NUM_PLUS;
			return 1;
		case VK_MULTIPLY:
			pEvent->key.keycode = KEY_NUM_MULTIPLY;
			return 1;
		case VK_SEPARATOR:
			pEvent->key.keycode = KEY_QUESTIONMARK;
			return 1;
		case VK_DIVIDE:
			pEvent->key.keycode = KEY_NUM_DIVIDE;
			return 1;
		case VK_OEM_1://;: key
			pEvent->key.keycode = KEY_SEMICOLON;
			return 1;
		case VK_OEM_2://? key
			pEvent->key.keycode = KEY_QUESTIONMARK;
			return 1;
		case VK_OEM_3://~
			pEvent->key.keycode = KEY_TILDY;
			return 1;
		case VK_OEM_4://'[{' key
			pEvent->key.keycode = KEY_CURLYBRACE_OPEN;
			return 1;
		case VK_OEM_5://'\|' key
			pEvent->key.keycode = KEY_FORWARDSLASH;
			return 1;
		case VK_OEM_6://']}' key
			pEvent->key.keycode = KEY_CURLYBRACE_CLOSE;
			return 1;
		case VK_OEM_7://'single quote' key
			pEvent->key.keycode = KEY_QUOTE;
			return 1;
			//all keys covered.
		default:
			return -1;
		}

		

		return 0;

	}

	/*-----------------------------------------------------------------------------
	Creates a new window and store its attributes in the database.
	Parameters:
	[IN]	title			- A desired title for the Window
	[IN]	Style			- The style of the window.
	[IN]	width			- width of the window.
	[IN]	hieght			- hieght of the window.
	[IN]	pEventHadeller	- pointer to the event handeller of the window.
	Returns: The handle to the window if the window was created, else 0;
	------------------------------------------------------------------------------*/
	WindowHandle WindowsSystemComponent::CreateNewWindow(char* title,
														 WindowStyle style,
														 int width,
														 int hieght,
														 IWindowEventHandeller* pEventHandeller) {
		if (m_WindowDB.SlotAvalable( )) {
			//parse the style to Windows terms.
			DWORD dwStyle = 0;
			switch (style) {
				case WSS_OVERLAPPINGWINDOW:
					dwStyle = WS_OVERLAPPEDWINDOW|WS_VISIBLE;
					break;
				case WSS_FULLSCREENWINDOW:
					dwStyle = WS_SYSMENU|WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_VISIBLE;
			}
			//create it now.
			HWND hWnd = CreateWindow(_ClassName, title, dwStyle, 0, 0,
									 width, hieght, NULL, NULL,
									 m_appInstance, (LPVOID)this
									 );
			return m_WindowDB.AddWindow(hWnd, pEventHandeller);
		} else return 0;
	}

	/*-----------------------------------------------------------------------------
	Summary: Static event handeller. Routes messages to appropriate instance.
	Parameters:
	[IN]	hWnd	- unique handle to the window.
	[In]	message	- incoming message.
	...
	-----------------------------------------------------------------------------*/
	LRESULT CALLBACK WindowsSystemComponent::staticWndProc(HWND hWnd,
														   UINT msg,
														   WPARAM wParam,
														   LPARAM lParam) {

		static const WindowsSystemComponent* pinst = (WindowsSystemComponent*)SystemComponent::GetInstance( );
		if (msg==WM_CREATE) {
			if (FAILED(SetWindowLongPtr(hWnd,
				GWLP_USERDATA,
				(LONG)((CREATESTRUCT*)lParam)->lpCreateParams))) {
				MessageBox(hWnd,
						   "The 'this' pointer to the Window could not be put in.\n",
						   "ERROR",
						   0);
			}
		}

		WindowsSystemComponent *targetApp = (WindowsSystemComponent*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (targetApp == pinst) {
			return targetApp->WndProc(hWnd, msg, wParam, lParam);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	/*-----------------------------------------------------------------------------
	Resets the keyboard data.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::Reset_KeyBoard( ) {
		for (auto& key : KeyPressed) key = false;
		for (auto& key : KeyPosted) key = false;
		Currentkeysync = true;
	}

	/*-----------------------------------------------------------------------------
	Summary: Windows Event Handeller. Routes Appropriate windows messages to the
	window's event handeller.
	Parameters:
	[IN]	hWnd	-	handle to the window for which the message/event is for.
	[IN]	msg		-	the message type.
	[IN]	wParam	-	the message parameter.
	[IN]	lParam	-	the message parameter.
	------------------------------------------------------------------------------*/
	LRESULT CALLBACK WindowsSystemComponent::WndProc(HWND hWnd, UINT msg,
													 WPARAM wParam,
													 LPARAM lParam) {
		//evet handling goes here..
		//get the pointer to the window's event handeller.
		if (m_WindowDB.GetNumWindows( ) != 0) {
			IWindowEventHandeller* handeller = m_WindowDB.GetEventHandeller( hWnd );
			if (handeller) {
				switch (msg) {
					case WM_CREATE:
						handeller->OnCreate( );
						break;
					case WM_PAINT:
						handeller->OnPaint( );
						break;
					case WM_SIZE:
						Reset_KeyBoard( );
						switch (wParam) {
							case SIZE_MINIMIZED:
								handeller->OnMinimized( );
								break;
							case SIZE_MAXIMIZED:
								handeller->OnMaximized( LOWORD( lParam ), HIWORD( lParam ) );
								break;
							default:
								handeller->OnResize( LOWORD( lParam ), HIWORD( lParam ) );
								break;
						}
						break;
					case WM_KILLFOCUS:
						Reset_KeyBoard( );
						break;
					case WM_DESTROY:
						handeller->OnDestroy( );
						break;
				}
			}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	/*-----------------------------------------------------------------------------
	Summary:	Shows a simple message box on the screen.
	Parameters:
	[IN]	message	:	the message to be shown inside the message box.
	[IN]	tittle	:	the tittle of the message box.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::ShowMessage(char* message, char* tittle) {
		MessageBox(NULL, message, tittle, NULL);
	}

	/*-----------------------------------------------------------------------------
	Adjusts the window in question, so that the window performs as dezired.
	Params:
	[IN]	handle	:	handle of the window which we want to adjust.
	[IN]	width	:	desired width of the window.
	[IN]	hieght	:	desired hieght of the window.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::AdjustWindow(WindowHandle handle,
											  int width, int hieght) {
		//check for valid handle??

		HWND hWnd = m_WindowDB.GetHWND(handle);
		RECT rect = {0, 0, width, hieght};
		AdjustWindowRect(&rect, GetWindowLong(hWnd, GWL_STYLE), false);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, rect.right-rect.left,
					 rect.bottom-rect.top, SWP_NOZORDER|SWP_NOMOVE);
	}

	/*-----------------------------------------------------------------------------
	Initializes the GL contexts.
	Parameters:
	[IN] handle			-	 the platform independent handle to the window.
	[IN] PixelParams	-	the struct containing parameters to be passed to
	contruct a pixel format.
	[IN] ContextParams	-	the struct containg the parameters to be passed to
	create the context.
	[OUT] OGLContext	-	platform independent handle to the context created.
	[OUT] DevContext	-	platform independent handle to the device context.
	Returns:
	true on success, false on falure.
	-----------------------------------------------------------------------------*/
	bool WindowsSystemComponent::CreateGLContext(WindowHandle handle,
												 PixelFormatParameters PixelParams,
												 ContextCreationPrameters ContextParams,
												 OpenGLContext& OGLContext,
												 DeviceContext& DevContext,
												 unsigned num_contexts) {
		if (!InitializeGLEW( )) return false;

		//Get the window HWND handle
		HWND hWnd = m_WindowDB.GetHWND(handle);
		//Get pointers to the Device context and the Rendering context
		//So that they can be changed and whatever needes to be done with
		//them can be done.
		HDC&		winDeviceContext = m_WindowDB.GetWindowsDeviceContext(handle);
		HGLRC&		winGLContext = m_WindowDB.GetWindowsGLContext(handle);

		winDeviceContext = GetDC(hWnd);

		bool bError = false;
		PIXELFORMATDESCRIPTOR pfd;

		if (ContextParams.iMajor_Version<=2) {
			return false;
		} else if (WGLEW_ARB_create_context && WGLEW_ARB_pixel_format) {
			const int iPixelFormatAttribList[] =
			{
				WGL_DRAW_TO_WINDOW_ARB, PixelParams.bDraw_to_Window,
				WGL_SUPPORT_OPENGL_ARB, PixelParams.bSupport_OpenGL,
				WGL_DOUBLE_BUFFER_ARB, PixelParams.bDouble_Buffer,
				WGL_TRANSPARENT_ARB, PixelParams.bTransparency,
				//WGL_PIXEL_TYPE_ARB		,		PixelParams.ePixel_Type		,
				WGL_ACCELERATION_ARB, PixelParams.eAcceleration,
				WGL_SWAP_METHOD_ARB, PixelParams.eSwap_Method,
				WGL_COLOR_BITS_ARB, PixelParams.iColor_Bits,//32,
				WGL_DEPTH_BITS_ARB, PixelParams.iDepth_Bits,//24,
				WGL_STENCIL_BITS_ARB, PixelParams.iStencil_Bits,//8,
				0 // End of attributes list
			};
			int iContextAttribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, ContextParams.iMajor_Version,
				WGL_CONTEXT_MINOR_VERSION_ARB, ContextParams.iMinor_Version,
				WGL_CONTEXT_FLAGS_ARB, ContextParams.eProfile,
				0 // End of attributes list
			};

			int iPixelFormat, iNumFormats;
			wglChoosePixelFormatARB(winDeviceContext,
									iPixelFormatAttribList,
									NULL,
									1,
									&iPixelFormat,
									(UINT*)&iNumFormats);

			// PFD seems to be only redundant parameter now
			if (!SetPixelFormat(winDeviceContext, iPixelFormat, &pfd))return false;

			winGLContext = wglCreateContextAttribsARB(winDeviceContext,
													  0, iContextAttribs);
			// If everything went OK
			if (winGLContext) wglMakeCurrent(winDeviceContext, winGLContext);
			else bError = true;

		} else bError = true;

		if (bError) {
			// Generate error messages
			char sErrorMessage[255], sErrorTitle[255];
			sprintf_s(sErrorMessage, "OpenGL %d.%d is not supported! Please download latest GPU drivers!",
					ContextParams.iMajor_Version, ContextParams.iMinor_Version);
			sprintf_s(sErrorTitle, "OpenGL %d.%d Not Supported",
					ContextParams.iMajor_Version, ContextParams.iMinor_Version);
			MessageBox(hWnd, sErrorMessage, sErrorTitle, MB_ICONINFORMATION);
			return false;
		}
		//Need to tell the caller about the new contexts.
		OGLContext = m_WindowDB.GetGLContext(handle);
		DevContext = m_WindowDB.GetDeviceContext( handle );

		return true;
	}

	/*-----------------------------------------------------------------------------
	releases the specified GLContext
	Parameters:
	[IN]	context - the context to be revoked.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::ReleaseGLContext(OpenGLContext context) {
		HDC dc = m_WindowDB.GetWindowsDeviceContext(context);
		wglMakeCurrent(dc, NULL);
		HGLRC rc = m_WindowDB.GetWindowsGLContext(context);
		wglDeleteContext(rc);
	}

	/*-----------------------------------------------------------------------------
	Function to load the OpenGL extentions which will be used via the GL Extention
	Wrangler (GLEW) on windows.
	Returns:
	true on success, false on falure.
	-----------------------------------------------------------------------------*/
	bool WindowsSystemComponent::InitializeGLEW( ) {
		if (m_GLEWInitialized) return true;

		//Registering temporary class to windows.
		WNDCLASSEX windef;		//the object that holds the definition of our class
		//while window Class registration.
		memset(&windef, 0, sizeof(WNDCLASSEX));

		windef.cbSize = sizeof(WNDCLASSEX);
		windef.style = CS_DBLCLKS|CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
		windef.lpfnWndProc = (WNDPROC)WindowsSystemComponent::staticWndProc;
		windef.cbClsExtra = 0;
		windef.cbWndExtra = 0;
		windef.hInstance = m_appInstance;
		windef.hIcon = NULL;
		windef.hCursor = LoadCursor(NULL, IDC_ARROW);
		windef.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		windef.lpszMenuName = NULL;
		windef.lpszClassName = "FAKEOGLCLASS";
		windef.hIconSm = NULL;

		//Register the Window Class.
		RegisterClassEx(&windef);

		HWND hFAKEWnd = CreateWindow(
			"FAKEOGLCLASS",
			"FAKE",
			WS_OVERLAPPEDWINDOW|WS_MAXIMIZE|WS_CLIPCHILDREN,
			0,
			0,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			m_appInstance,
			NULL
			);

		m_hDeviceContext = GetDC(hFAKEWnd);

		// First, choose false pixel format

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER|PFD_SUPPORT_OPENGL|PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int iPixelFormat = ChoosePixelFormat(m_hDeviceContext, &pfd);
		if (iPixelFormat==0)return false;

		if (!SetPixelFormat(m_hDeviceContext, iPixelFormat, &pfd))return false;

		// Create the false, old style context (OpenGL 2.1 and before)

		HGLRC hRCFake = wglCreateContext(m_hDeviceContext);
		wglMakeCurrent(m_hDeviceContext, hRCFake);

		bool bResult = true;

		if (!m_GLEWInitialized) {
			if (glewInit( )!=GLEW_OK) {
				MessageBox(hFAKEWnd, "Couldn't initialize GLEW!", "Fatal Error", MB_ICONERROR);
				bResult = false;
			}
			m_GLEWInitialized = true;
		}

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRCFake);
		DestroyWindow(hFAKEWnd);
		UnregisterClass("FAKEOGLCLASS", m_appInstance);

		return bResult;
	}

	/*-----------------------------------------------------------------------------
	This function returns the Display mode of the requested display device.
	Parameters:
	[IN]	DeviceName	-	 the name of the device of which the mode will be
	returned.
	[OUT]	devMode		-	 the structure which will be filled with the mode.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::GetDeviceDisplayMode(char* DeviceName, DisplayMode& devMode) {
		DEVMODE winDevMode;
		EnumDisplaySettings(DeviceName, ENUM_CURRENT_SETTINGS, &winDevMode);

		//Its time to fill in
		devMode.BitsPerPel = winDevMode.dmBitsPerPel;
		devMode.DeviceName = winDevMode.dmDeviceName;
		devMode.DisplayFrequency = winDevMode.dmDisplayFrequency;
		devMode.PelsHeight = winDevMode.dmPelsHeight;
		devMode.PelsWidth = winDevMode.dmPelsWidth;

		//And the job is done...
	}

	/*-----------------------------------------------------------------------------
	This function sets the Display mode of the requested display device.
	Parameters:
	[IN]	DeviceName	-	 the name of the device of which the mode will be
	returned.
	[OUT]	newMode		-	 the structure containg the new mode
	-----------------------------------------------------------------------------*/
	bool WindowsSystemComponent::SetDeviceDisplayMode(char* DeviceName, DisplayMode newMode, bool tellSys) {
		DEVMODE winDevMode;

		winDevMode.dmSize = sizeof(DEVMODE);
		winDevMode.dmBitsPerPel = newMode.BitsPerPel;
		winDevMode.dmPelsWidth = newMode.PelsWidth;
		winDevMode.dmPelsHeight = newMode.PelsHeight;
		winDevMode.dmDisplayFrequency = newMode.DisplayFrequency;
		winDevMode.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY;

		long result = ChangeDisplaySettings(&winDevMode, CDS_FULLSCREEN);
		if (result==DISP_CHANGE_SUCCESSFUL) {
			
			if (tellSys) {
				SendMessage(HWND_BROADCAST, WM_DISPLAYCHANGE,
							(WPARAM)(winDevMode.dmBitsPerPel),
							MAKELPARAM(winDevMode.dmPelsWidth, winDevMode.dmPelsHeight));
			}

			return true;
		} else return false;
	}

	/*-----------------------------------------------------------------------------
	Makes the window vissible by drawing it.
	Parameters:
	[IN] handle	-	the platform independent handle to the window.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::ShowWindow_(WindowHandle handle) {
		HWND hWnd = m_WindowDB.GetHWND(handle);
		ShowWindow(hWnd, SW_SHOW);
	}

	/*-----------------------------------------------------------------------------
	Updaes the changes made to the properties of a window.
	Parameters:
	[IN] handle	-	the platform independent handle to the window.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::UpdateWindow_(WindowHandle handle) {
		HWND hWnd = m_WindowDB.GetHWND(handle);
		UpdateWindow(hWnd);
	}

	/*-----------------------------------------------------------------------------
	Changes the window style.
	Parameters:
	[IN] handle	-	the platform independent handle to the window.
	[IN] style	-	the new style specifcation.
	-----------------------------------------------------------------------------*/
	void WindowsSystemComponent::SetWindowStyle(WindowHandle handle, WindowStyle style) {
		HWND hWnd = m_WindowDB.GetHWND(handle);
		DWORD wndStyle = 0;
		switch (style) {
			case WSS_OVERLAPPINGWINDOW:
				wndStyle = WS_OVERLAPPEDWINDOW;
				break;
			case WSS_FULLSCREENWINDOW:
				wndStyle = WS_SYSMENU|WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_VISIBLE|WS_EX_TOPMOST;
				break;
		}
		SetWindowLongPtr(hWnd, GWL_STYLE, wndStyle);
	}

	void WindowsSystemComponent::SetWindowTittle(WindowHandle window, const char * newTitle ) {
		HWND handle = m_WindowDB.GetHWND( window );
		SetWindowText( handle, newTitle );
	}

	void WindowsSystemComponent::setSwapInterval( int interval ) {
		wglSwapIntervalEXT( interval );
	}

	/*-----------------------------------------------------------------------------
	Returns the infoemation regarding the window's placement.
	Parameters:
	[IN] handle	-	the platform independent handle to the window.
	-----------------------------------------------------------------------------*/
	WindowPlacementPtr WindowsSystemComponent::GetWindowPlacement_(WindowHandle handle) {
		HWND hWnd = m_WindowDB.GetHWND(handle);

		WINDOWPLACEMENT wndplcmnt;
		ZeroMemory(&wndplcmnt, sizeof(WINDOWPLACEMENT));
		wndplcmnt.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(hWnd, &wndplcmnt);

		return m_WindowDB.AddWindowPlacement(wndplcmnt);
	}

	void WindowsSystemComponent::SetWindowPlacement_(WindowHandle handle,
													 WindowPlacementPtr winplcemnet) {
		HWND hWnd = m_WindowDB.GetHWND(handle);
		WINDOWPLACEMENT* wp = m_WindowDB.GetWindowPlacement(winplcemnet);
		SetWindowPlacement(hWnd, wp);
	}

	void WindowsSystemComponent::UpdateWindowPlacement(WindowHandle handle,
													   WindowPlacementPtr* pWndPlcment) {
		HWND hWnd = m_WindowDB.GetHWND(handle);
		WINDOWPLACEMENT* wndplcmnt = m_WindowDB.GetWindowPlacement(*pWndPlcment);
		ZeroMemory(&wndplcmnt, sizeof(WINDOWPLACEMENT));
		wndplcmnt->length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(hWnd, wndplcmnt);
	}

	void WindowsSystemComponent::FrameInput( ) {
		m_First_Input_loop = true;
	}

	/*-------------------------------------------------------------------------
	Called at each frame. Does some per frame system stuff like posting the 
	KeyPress Event to the event que. 
	-------------------------------------------------------------------------*/
	UNDONE_API void WindowsSystemComponent::NewInputFrame( ) {
		
		Currentkeysync = !Currentkeysync;
		return;
	}

	/*-----------------------------------------------------------------------------
	Returns:
	0	if the message is not relevant or there is no message in the que.
	1   for some message is recieved and is successfully returned via pEvent.
	-1  for if an error occured.
	-----------------------------------------------------------------------------*/
	int WindowsSystemComponent::GetInputEvent(InputEvent* pEvent, __int64 given_time) {
		//Get the message
		MSG msg;
		POINTS ptCursor;
		
		
		
		if (!keyinit) {
			m_KeyBoard_Device.usUsagePage = 0x01;
			m_KeyBoard_Device.usUsage = 0x06;
			m_KeyBoard_Device.dwFlags = RIDEV_NOLEGACY;
			m_KeyBoard_Device.hwndTarget = m_WindowDB.GetHWND(0);
			RegisterRawInputDevices(&m_KeyBoard_Device, 1, sizeof(m_KeyBoard_Device));
			keyinit = true;
		}
		
		//send out keydpress messages first.
		for (unsigned i = 0; i < 256; ++i) {
			if (KeyPressed[i] && KeyPosted[i] != Currentkeysync) {
				pEvent->key.type = EVENT_KEYPRESS;
				pEvent->key.keycode = (Key)i;
				pEvent->key.timestamp = GetTickCount();
				KeyPosted[i]= !KeyPosted[i];
				return 1;
			}
		}
		

		//get next pending messages into our msg que
		if(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )>0) {
			msgque.push_back(msg);
		}

		//now we get one message at a time from the que.
		if(msgque.size() > 0 && __int64(msgque.front().time) <= given_time){
			msg = msgque.front( );
			msgque.pop_front();
			//Now parse this message to our own struct.
			pEvent->event.timestamp = msg.time;
			switch (msg.message) {
			
			case WM_QUIT:
				//The OS wants the App to quit.
				//So tell the caller the same.
				pEvent->event.type = EVENT_QUIT;
				return 1;
				
			//Mouse
			case WM_MOUSEMOVE:
				if (first) {
					ptPrevCursor = MAKEPOINTS(msg.lParam);
					first = false;
				}

				pEvent->event.type = EVENT_MOUSEMOVE;
				ptCursor = MAKEPOINTS(msg.lParam);
				pEvent->mouse_motion.mouse_pos_x = ptCursor.x;
				pEvent->mouse_motion.mouse_pos_y = ptCursor.y;
				pEvent->mouse_motion.delta_x = ptCursor.x - ptPrevCursor.x;
				pEvent->mouse_motion.delta_y = ptPrevCursor.y - ptCursor.y;

				ptPrevCursor = ptCursor;
				return 1;
			case WM_LBUTTONDOWN:
				pEvent->event.type = EVENT_MOUSEBUTTONDOWN;
				pEvent->mouse_button.button = MOUSE_BUTTON_L;
				SetCapture(msg.hwnd);
				return 1;
			case WM_MBUTTONDOWN:
				pEvent->event.type = EVENT_MOUSEBUTTONDOWN;
				pEvent->mouse_button.button = MOUSE_BUTTON_M;
				SetCapture(msg.hwnd);
				return 1;
			case WM_RBUTTONDOWN:
				SetCapture(msg.hwnd);
				pEvent->event.type = EVENT_MOUSEBUTTONDOWN;
				pEvent->mouse_button.button = MOUSE_BUTTON_R;
				return 1;
			case WM_LBUTTONUP:
				pEvent->event.type = EVENT_MOUSEBUTTONUP;
				pEvent->mouse_button.button = MOUSE_BUTTON_L;
				ReleaseCapture();
				return 1;
			case WM_MBUTTONUP:
				pEvent->event.type = EVENT_MOUSEBUTTONUP;
				pEvent->mouse_button.button = MOUSE_BUTTON_M;
				ReleaseCapture();
				return 1;
			case WM_RBUTTONUP:
				pEvent->event.type = EVENT_MOUSEBUTTONUP;
				pEvent->mouse_button.button = MOUSE_BUTTON_R;
				ReleaseCapture();
				return 1;
			
			//Keyboard
			case WM_INPUT:
			{
				char buffer[sizeof(RAWINPUT)] = {};
				UINT size = sizeof(RAWINPUT);
				GetRawInputData(reinterpret_cast<HRAWINPUT>(msg.lParam),
					RID_INPUT,
					buffer,
					&size,
					sizeof(RAWINPUTHEADER));
				//extract keyboard input data
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer);
				if (raw->header.dwType == RIM_TYPEKEYBOARD) {
					if (EvaluateKeyBaordInput( raw->data.keyboard, pEvent ) > 0) {
						if (pEvent->event.type == EVENT_KEYDOWN) {
							if(KeyPressed[pEvent->key.keycode])
								return 0; //ignoring the event.
							else {
								KeyPressed[pEvent->key.keycode] = true;
							
							}
						} else if (pEvent->event.type == EVENT_KEYUP) {
							KeyPressed[pEvent->key.keycode] = false;
							
						}
						return 1;
					}
				}//keyboard
				
			}//input
			return -1;

			default:
				//Things that are not input are windows messages.
				//Let them go to our window proc
				DispatchMessage(&msg);
				return 0;
			}
		} else return 0;

	}

	void WindowsSystemComponent::Swipe_Buffers(DeviceContext context) {
		HDC dc = m_WindowDB.GetWindowsDeviceContext(context);
		SwapBuffers(dc);
	}

	///////////////////////////////////////////////////////////////////////////////
	/////////////////////////////FUNTIONS FOR WINDOWDATABASE///////////////////////
	/*-----------------------------------------------------------------------------
	Initializer of the Window data base object. Defualt constructor, that is.
	-----------------------------------------------------------------------------*/
	WindowDataBase::WindowDataBase( ) {
		num_Windows = 0;
		num_Placements = 0;
	}

	/*-----------------------------------------------------------------------------
	Adds a window to the database and generates a Window Handle.
	Parameters:
	[IN]	hWnd			: the Windows specific handle to the created window.
	[IN]	pEventHandler	: the ascociated event handeller of the window.
	Returns: the WindowHandle object .
	-----------------------------------------------------------------------------*/
	WindowHandle WindowDataBase::AddWindow(HWND hWnd, IWindowEventHandeller* pEventHandeller) {
		if (SlotAvalable( )) {
			Windows[num_Windows].m_WindowsHandle = hWnd;
			Windows[num_Windows].m_EventHandeller = pEventHandeller;
			num_Windows++;
			return num_Windows-1;
		} else return -1;
	}

	/*-----------------------------------------------------------------------------
	Returns the Windows specific handle of the requested window.
	Parameters:
	[IN]	handle	: the handle to the window (not OS specific).
	-----------------------------------------------------------------------------*/
	HWND WindowDataBase::GetHWND(WindowHandle Handle) {
		if (Handle>num_Windows-1) return NULL;
		return Windows[Handle].m_WindowsHandle;
	}

	/*-----------------------------------------------------------------------------
	Returns the pointer to the event handeller of the requested window.
	Parameters:
	[IN]	handle	: the handle to the window (not OS specific).
	-----------------------------------------------------------------------------*/
	IWindowEventHandeller* WindowDataBase::GetEventHandeller(WindowHandle handle) {
		if (handle>num_Windows-1) return nullptr;
		return Windows[handle].m_EventHandeller;
	}

	/*-----------------------------------------------------------------------------
	To check if the database has any slots available
	Returs: true if yes, false if no.
	-----------------------------------------------------------------------------*/
	bool WindowDataBase::SlotAvalable( ) {
		return (num_Windows<NUMWINDOWS);
	}

	WindowPlacementPtr WindowDataBase::AddWindowPlacement(WINDOWPLACEMENT wndplcmnt) {
		if (num_Placements==NUMWINDOWS) return MAXBYTE;
		WindowPlacements[num_Placements] = wndplcmnt;
		num_Placements++;
		return num_Placements-1;
	}

	WINDOWPLACEMENT* WindowDataBase::GetWindowPlacement(WindowPlacementPtr ptr) {
		if (ptr>num_Placements-1) return nullptr;
		return &WindowPlacements[ptr];
	}

	/*-----------------------------------------------------------------------------
	Used to obtain the Event handeller pointer of a particular window.
	Parameters:
	[IN]	handle	-	Windows specific handle to the window.
	-----------------------------------------------------------------------------*/
	IWindowEventHandeller* WindowDataBase::GetEventHandeller(HWND handle) {
		for (auto& entry:Windows) {
			if (entry.m_WindowsHandle==handle) {
				return entry.m_EventHandeller;
			}
		}
		//No such window?
		return nullptr;
	}

	OpenGLContext WindowDataBase::GetGLContext(WindowHandle Handle) {
		//ha ha. this really makes me laugh.
		return Handle;
		//Beacause its just the index where the Window entry is stored.
	}

	DeviceContext WindowDataBase::GetDeviceContext(WindowHandle Handle) {
		return Handle;
	}

	HGLRC& WindowDataBase::GetWindowsGLContext(WindowHandle Handle) {
		return Windows[Handle].m_GLRenderContext;
	}



	HDC& WindowDataBase::GetWindowsDeviceContext(WindowHandle Handle) {
		return Windows[Handle].m_DeviceContext;
	}
	OpenGLContext WindowDataBase::AddGLContext( HGLRC winContext ) {
		GL_Contexts.push_back( winContext );
		return GL_Contexts.size( )-1;
	}
	HGLRC & WindowDataBase::GetwinGLContext( OpenGLContext context ) {
		return GL_Contexts[context];
	}
};

#endif