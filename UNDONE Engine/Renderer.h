/*-----------------------------------------------------------------------------
File	:	Renderer.h
Author	:	Anurup Dey
-----------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "DObjectBuffer.h"

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

		bool Initialize(DObjectBuffer* pGraphicsBuffer,glm::mat4& _2DProjmatref);
		void Render( );
	private:
		void Render3D( );
		void Render2D( );

		DObjectBuffer* m_pGraphicsBuffer;
		glm::mat4*	   m_p2DProjMat;
		//TOADD:
		//the sprite_Manager object pointer
		//the control_camera object
	};
}
#endif