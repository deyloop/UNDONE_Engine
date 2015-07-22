/*-----------------------------------------------------------------------------
File	:	Renderer.h
Author	:	Anurup Dey

Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>

This file is part of UNDONE-Engine.

UNDONE-Engine can not be copied and/or distributed without the express
permission of Anurup Dey. Unauthorized copying of this file, via any
medium is strictly prohibited.

Proprietary and confidential.

-----------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "ObjectBuffer.h"

namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	This is the renderer object. Has the responsibility of rendering graphics on
	the screen. THe objects are managed by the GraphicEngine, and the renderer
	simply draws them.
	-----------------------------------------------------------------------------*/
	class Renderer {
	public:
		Renderer( );
		~Renderer( ) { Release( ); }

		void Release( );

		bool Initialize(ObjectBuffer* pGraphicsBuffer,glm::mat4& _2DProjmatref);
		void Render( );
	private:
		void Render3D( );
		void Render2D( );

		ObjectBuffer* m_pGraphicsBuffer;
		glm::mat4*	   m_p2DProjMat;
		//TOADD:
		//the sprite_Manager object pointer
		//the control_camera object
	};
}
#endif