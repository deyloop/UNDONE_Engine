/*-----------------------------------------------------------------------------
File	:	Renderer.h
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

        void ToggleVSYNC( ) { m_VSYNC = !m_VSYNC; }
	private:
		void Render3D( );
		void Render2D( );

		ObjectBuffer* m_pGraphicsBuffer;
		glm::mat4*	  m_p2DProjMat;
        bool          m_VSYNC;
		//TOADD:
		//the sprite_Manager object pointer
		//the control_camera object
	};
}
#endif