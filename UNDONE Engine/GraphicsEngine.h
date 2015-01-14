/******************************************************************************
File	:	GraphicsEngine.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _GRAPHICSENGINE_H_
#define _GRAPHICSENGINE_H_

#include <glew.h>
#include "SystemComponent.h"
#include "Renderer.h"
#include "ObjectBuffer.h"
using namespace UNDONE_ENGINE;

/*-----------------------------------------------------------------------------
Summary:	This Interface has to be implimented by the using framework to be
able to use the GraphicEngine Class. This Interface contains some
events which the Engine can trigger in accordance to the creation
and activities of the Graphic Card.
-----------------------------------------------------------------------------*/
class IFrameWork					//NOTE: this is an Abstract class.
{
public:

	virtual void  OnCreateContext()					= 0;
	virtual const int   GetScreenHieght() const		= 0;
	virtual const int   GetScreenWidth() const 		= 0;
	virtual const float GetElapsedTime() const		= 0;
};

/*-----------------------------------------------------------------------------
This class handles all the tasks related to graphics.
-----------------------------------------------------------------------------*/
class GraphicsEngine{
public:
	GraphicsEngine();
	~GraphicsEngine(){ Release(); }

	void Release();

	bool Initialize(WindowHandle window, 
					IFrameWork* pFrameWork,
					ObjectBuffer* pGraphicsBuffer,
					int context_version_major = 3, 
					int context_version_minor = 1,
					bool windowed = true);

	void ToggleFullscreen();
	void ToggleRenderMode(){};

	void RenderScene();

	void OnCreateContext();
	void OnDestroyContext();

	const DisplayMode& GetDisplayMode( ) const { return m_DisplayMode; }

private:
	bool BiuldPixelParams();
	bool BuildContextCreationParams();

	OpenGLContext		m_GLContext;
	DeviceContext		m_DeviceContext;
	bool				m_windowed;

	PixelFormatParameters		m_PixelFormatParams;
	ContextCreationPrameters	m_ContextParams;
	DisplayMode					m_DisplayMode;

	ObjectBuffer*		m_pGraphicsBuffer;
	IFrameWork*			m_pFrameWork;
	SystemComponent*	m_pSystem;
	Renderer*			m_pRenderer;
};
#endif