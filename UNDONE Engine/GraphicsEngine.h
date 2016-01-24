/******************************************************************************
File	:	GraphicsEngine.h
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

#ifndef _GRAPHICSENGINE_H_
#define _GRAPHICSENGINE_H_


#include <glew.h>
#include "SystemComponent.h"
#include "Renderer.h"
#include "ObjectBuffer.h"
#include "unEngineInterfaces.h"


namespace UNDONE_ENGINE {
	class IGraphicsUser;				//NOTE: this is an Abstract class.
	

	/*-----------------------------------------------------------------------------
	This class handles all the tasks related to graphics.
	-----------------------------------------------------------------------------*/
	class GraphicsEngine : public unGraphics {
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
		void ToggleVSYNC( );

		void RenderScene( );

		void OnCreateContext( );
		void OnDestroyContext( );

		template<class T>
		void Upload_( ) {
			vector<T>* list = m_pGraphicsBuffer->GetListOf<T>( );
			for (auto& resource : *list)
				resource.GPU_Upload();
		}

		void Upload( ){
			Upload_<Shader>();
			Upload_<ShaderProgram>();
			Upload_<Texture>( );
			Upload_<Mesh>();
			Upload_<GraphicMaterial>();
			Upload_<Graphic2D>();
		}// temp member.

		void ResetScreen( );
		void SetResolution(const int hor, const int vert);

		const DisplayMode& GetDisplayMode( ) const { return m_DisplayMode; }

	private:
		bool BiuldPixelParams( );
		bool BuildContextCreationParams( );

		OpenGLContext		m_GLContext;
		DeviceContext		m_DeviceContext;
		bool				m_windowed;
		bool                m_VSYNC;
		

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