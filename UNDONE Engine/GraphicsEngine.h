/******************************************************************************
File	:	GraphicsEngine.h
Author	:	Anurup Dey

Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>

This file is part of UNDONE-Engine.

UNDONE-Engine can not be copied and/or distributed without the express
permission of Anurup Dey. Unauthorized copying of this file, via any
medium is strictly prohibited.

Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _GRAPHICSENGINE_H_
#define _GRAPHICSENGINE_H_


#include <glew.h>
#include "SystemComponent.h"
#include "Renderer.h"
#include "ObjectBuffer.h"


namespace UNDONE_ENGINE {
	class IGraphicsUser;				//NOTE: this is an Abstract class.
	

	/*-----------------------------------------------------------------------------
	This class handles all the tasks related to graphics.
	-----------------------------------------------------------------------------*/
	class GraphicsEngine {
	public:
		GraphicsEngine( );
		~GraphicsEngine( ) { Release( ); }

		void Release( );

		bool Initialize(WindowHandle window,
						IGraphicsUser* pFrameWork,
						ObjectBuffer* pGraphicsBuffer,
						int context_version_major = 3,
						int context_version_minor = 1,
						bool windowed = true);

		void ToggleFullscreen( );
		void ToggleRenderMode( ) { };

		void RenderScene( );

		void OnCreateContext( );
		void OnDestroyContext( );
		void ResetScreen( );
		void SetResolution(const int hor, const int vert);

		const DisplayMode& GetDisplayMode( ) const { return m_DisplayMode; }

	private:
		bool BiuldPixelParams( );
		bool BuildContextCreationParams( );

		OpenGLContext		m_GLContext;
		DeviceContext		m_DeviceContext;
		bool				m_windowed;

		

		PixelFormatParameters		m_PixelFormatParams;
		ContextCreationPrameters	m_ContextParams;
		DisplayMode					m_DisplayMode;

		ObjectBuffer*		m_pGraphicsBuffer;
		IGraphicsUser*		m_pFrameWork;
		SystemComponent*	m_pSystem;
		Renderer*			m_pRenderer;
		glm::mat4			m_2DProjMat;
	};
}
#endif