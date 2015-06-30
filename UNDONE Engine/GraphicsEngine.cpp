/******************************************************************************
File	:	GraphicsEngine.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "GraphicsEngine.h"
#include "IGraphicsUser.h"
#include "Texture.h"
#include "_3DGraphic.h"
#include "_2DGraphic.h"
#include "Font.h"



namespace UNDONE_ENGINE {
	Font font;
	
	/*-----------------------------------------------------------------------------
	Default Constructor
	-----------------------------------------------------------------------------*/
	GraphicsEngine::GraphicsEngine( ) {
		m_pGraphicsBuffer = nullptr;
		m_pFrameWork = nullptr;
		m_pSystem = nullptr;
		m_pRenderer = nullptr;
		m_2DProjMat = glm::mat4(1.0f);

		m_windowed = true;
	}

	/*-----------------------------------------------------------------------------
	Default destructor
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::Release( ) {

		m_pSystem->ReleaseGLContext(m_GLContext);
		OnDestroyContext( );

		if (m_pGraphicsBuffer) {
			m_pGraphicsBuffer->DeleteAll<_3DGraphic>( );
			m_pGraphicsBuffer->DeleteAll<ShaderProgram>( );
			m_pGraphicsBuffer->DeleteAll<Shader>( );
			m_pGraphicsBuffer->DeleteAll<Texture>( );
			m_pGraphicsBuffer->DeleteAll<Mesh>( );
			m_pGraphicsBuffer->DeleteAll<_2DGraphic>( );
			m_pGraphicsBuffer->DeleteAll<WorldTransform>( );
			m_pGraphicsBuffer->DeleteAll<GraphicMaterial>( );
			m_pGraphicsBuffer = nullptr;
		}
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
	bool GraphicsEngine::Initialize(WindowHandle window, IGraphicsUser* pFrameWork,
									DObjectBuffer* pGraphicsBuffer,
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

		m_pRenderer->Initialize(m_pGraphicsBuffer,m_2DProjMat);

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

		m_2DProjMat = glm::ortho(0.0f, (float)width, (float)hieght, 0.0f);
		glViewport(0, 0, width, hieght);

		_2DGraphic::SetScreenDimentions(hieght, width);

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
	
		//tell the framework 
		if (m_pFrameWork) m_pFrameWork->OnCreateContext( );
		//Set up 2D.
		
		DPointer<Shader> vertexShader = m_pGraphicsBuffer->CreateNew<Shader>( );
		DPointer<Shader> fragmentShader = m_pGraphicsBuffer->CreateNew<Shader>( );
		DPointer<Shader> FontFragmentShader = m_pGraphicsBuffer->CreateNew<Shader>();
		DPointer<ShaderProgram> _FontShader = m_pGraphicsBuffer->CreateNew<ShaderProgram>();
		DPointer<ShaderProgram> _2DShader = m_pGraphicsBuffer->CreateNew<ShaderProgram>( );
		vertexShader->LoadShader("2Dshader.vert", GL_VERTEX_SHADER);
		fragmentShader->LoadShader("2Dshader.frag", GL_FRAGMENT_SHADER);
		FontFragmentShader->LoadShader("2DFontShader.frag", GL_FRAGMENT_SHADER);
		
		_2DShader->CreateProgram( );
		_2DShader->AddShaderToProgram(vertexShader.ptr( ));
		_2DShader->AddShaderToProgram(fragmentShader.ptr( ));
		_2DShader->LinkProgram( );

		_FontShader->CreateProgram();
		_FontShader->AddShaderToProgram(vertexShader.ptr());
		_FontShader->AddShaderToProgram(FontFragmentShader.ptr());
		_FontShader->LinkProgram();
		
		_2DGraphic::SetShader(_2DShader);
		_2DGraphic::InitVAO( );

		
		font.SetShaderProgram(_FontShader);
		font.LoadSystemFont("arial.ttf", 32);

		
		//GL State variables.
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glClearStencil(1);
		
		glCullFace(GL_BACK);

		ResetScreen( );

	}

	/*----------------------------------------------------------------------------
	Called when the context gets destroyed.
	All graphicalresources are deleted.
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::OnDestroyContext( ) {
		if (m_pGraphicsBuffer) {
			for (auto& graphic:*m_pGraphicsBuffer->GetListOf<_3DGraphic>( )) {
				graphic.OnDestroy( );
			}
		}
		
		_2DGraphic::DeleteVAO( );
	
	}

	/*-----------------------------------------------------------------------------
	Renders the scene.
	-----------------------------------------------------------------------------*/
	void GraphicsEngine::RenderScene( ) {
		if (m_pRenderer) {
			//Do it!
			
			m_pRenderer->Render( );
			font.print("TEXT WORKS!\n hurray!", -1, 0, 2);
		}

		
		m_pSystem->Swipe_Buffers(m_DeviceContext);
	}

}
///////////////////////////////////////////////////////////////////////////////