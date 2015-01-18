/******************************************************************************
File	:	GraphicsEngine.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "GraphicsEngine.h"

namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	Default Constructor
	-----------------------------------------------------------------------------*/
	GraphicsEngine::GraphicsEngine( ) {
		m_pGraphicsBuffer = nullptr;
		m_pFrameWork = nullptr;
		m_pSystem = nullptr;
		m_pRenderer = nullptr;

		m_windowed = true;
	}

	/*-----------------------------------------------------------------------------
	Default destructor
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::Release( ) {

		m_pSystem->ReleaseGLContext(m_GLContext);
		OnDestroyContext( );

		if (m_pGraphicsBuffer)	m_pGraphicsBuffer = nullptr;
		if (m_pFrameWork) {
			m_pFrameWork = nullptr;
		}

		m_pSystem = nullptr;

		if (m_pRenderer) {
			m_pRenderer->Release( );
			delete m_pRenderer;
			m_pRenderer = nullptr;
		}
	}

	/*-----------------------------------------------------------------------------
	Initializes OpenGL and gets ready to render things.
	Parameters:
	[IN]	window					-	the handle to a window.
	[IN]	pFrameWork				- pointer to the game Engine instance using
	the graphics.
	[IN]	pGraphicsBuffer			- pointer to a buffer contaning all the
	objects to be drawn.
	[IN]	context_version_major	- for the context version.
	[IN]	context_version_minor	- for the context version.
	[IN]	windowed				- indication for windowed or fullscreen.

	Returns:
	true on success, false on falure.
	-----------------------------------------------------------------------------*/
	bool GraphicsEngine::Initialize(WindowHandle window, IFrameWork* pFrameWork,
									ObjectBuffer* pGraphicsBuffer,
									int context_version_major, int context_version_minor,
									bool windowed) {
		m_pFrameWork = pFrameWork;
		m_pGraphicsBuffer = pGraphicsBuffer;
		m_windowed = windowed;

		m_pSystem = SystemComponent::GetInstance( );
		m_pRenderer = new Renderer( );

		//Get the current display mode
		m_pSystem->GetDeviceDisplayMode(NULL, m_DisplayMode);

		if (!(BiuldPixelParams( )&&BuildContextCreationParams( ))) {
			m_pSystem->ShowMessage("Could not build presentation params.", "ERROR: Initialize()");
			return false;
		}

		//Now create the context
		if (!m_pSystem->CreateGLContext(window,
			m_PixelFormatParams, m_ContextParams,
			m_GLContext, m_DeviceContext
			)
			) {
			m_pSystem->ShowMessage("Could not Create GL Context.", "ERROR: Initialize()");
			return false;
		}

		OnCreateContext( );

		m_pRenderer->Initialize(m_pGraphicsBuffer);

		return true;
	}

	/*-----------------------------------------------------------------------------
	Toggles between fullscreen rendering and windoed rtendering
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::ToggleFullscreen( ) {
		if (!m_pSystem) return;
		m_windowed = !m_windowed;

		ResetScreen( );

	}

	/*-----------------------------------------------------------------------------
	Sets the screen res.
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::SetResolution(const int hor, const int vert) {
		m_DisplayMode.PelsHeight = vert;
		m_DisplayMode.PelsWidth = hor;
		m_pSystem->SetDeviceDisplayMode(NULL, m_DisplayMode, true);
	}
	/*-----------------------------------------------------------------------------
	Resets the openGL viewport.
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::ResetScreen( ) {
		if (!m_pFrameWork) return;

		int width = m_pFrameWork->GetScreenWidth( );
		int hieght = m_pFrameWork->GetScreenHieght( );

		glViewport(0, 0, width, hieght);

		m_pGraphicsBuffer->GetControlCamera( ).SetAspectRatio((float)width/(float)hieght);

	}
	/*-----------------------------------------------------------------------------
	Creates the pixel parameters.
	-----------------------------------------------------------------------------*/
	bool GraphicsEngine::BiuldPixelParams( ) {
		m_PixelFormatParams.bDouble_Buffer = true;
		m_PixelFormatParams.bDraw_to_Window = m_windowed;
		m_PixelFormatParams.bSupport_OpenGL = true;
		m_PixelFormatParams.bTransparency = false;
		m_PixelFormatParams.eAcceleration = FULL_ACCELERATION;
		m_PixelFormatParams.eSwap_Method = SWAP_EXCHANGE;
		m_PixelFormatParams.ePixel_Type = RGBA;
		m_PixelFormatParams.iColor_Bits = 32;
		m_PixelFormatParams.iDepth_Bits = 24;
		m_PixelFormatParams.iStencil_Bits = 8;

		return true;
	}

	/*-----------------------------------------------------------------------------
	Fills the context parameters.
	-----------------------------------------------------------------------------*/
	bool GraphicsEngine::BuildContextCreationParams( ) {
		m_ContextParams.iMajor_Version = 3;
		m_ContextParams.iMinor_Version = 1;
		m_ContextParams.eProfile = CONTEXT_CORE_PROFILE;

		return true;
	}

	/*-----------------------------------------------------------------------------
	Called when the Context gets created
	All Graphical resources are alocated.
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::OnCreateContext( ) {
		//Initialize all the objects.
		if (m_pGraphicsBuffer) {
			for (auto& graphic:m_pGraphicsBuffer->GetObjectsToDraw( )) {
				graphic->OnInit( );
			}
		}
		//tell the framework 
		if (m_pFrameWork) m_pFrameWork->OnCreateContext( );
		ResetScreen( );
		//GL State variables.
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glClearStencil(1.0f);
		glCullFace(GL_BACK);
	}

	/*----------------------------------------------------------------------------
	Called when the context gets destroyed.
	All graphicalresources are deleted.
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::OnDestroyContext( ) {
		if (m_pGraphicsBuffer) {
			for (auto& graphic:m_pGraphicsBuffer->GetObjectsToDraw( )) {
				graphic->OnDestroy( );
			}
		}
	}

	/*-----------------------------------------------------------------------------
	Renders the scene.
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::RenderScene( ) {
		if (m_pRenderer) {
			//Do it!
			m_pRenderer->Render( );
		}
		m_pSystem->Swipe_Buffers(m_DeviceContext);
	}

}
///////////////////////////////////////////////////////////////////////////////