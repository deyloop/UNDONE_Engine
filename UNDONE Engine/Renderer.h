/*-----------------------------------------------------------------------------
File	:	Renderer.h
Author	:	Anurup Dey
-----------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "ObjectBuffer.h"
/*-----------------------------------------------------------------------------
This is the renderer object. Has the responsibility of rendering graphics on 
the screen. THe objects are managed by the GraphicEngine, and the renderer
simply draws them.
-----------------------------------------------------------------------------*/
class Renderer{
public:
	Renderer();
	~Renderer(){ Release(); }

	void Release();

	bool Initialize(ObjectBuffer* pGraphicsBuffer);
	void Render();
private:
	void Render3D();
	void Render2D();

	ObjectBuffer* m_pGraphicsBuffer;
	//TOADD:
	//the sprite_Manager object pointer
	//the control_camera object
};
#endif