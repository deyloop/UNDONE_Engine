/*-----------------------------------------------------------------------------
File	:	Renderer.cpp
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
#include "Renderer.h"
#include "Graphic3D.h"
#include "Graphic2D.h"
#include <gtx/transform.hpp>

namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	Default constructor
	-----------------------------------------------------------------------------*/
	Renderer::Renderer( ) {
		m_pGraphicsBuffer = nullptr;
	}

	/*-----------------------------------------------------------------------------
	Default destructor.
	-----------------------------------------------------------------------------*/
	void Renderer::Release( ) {
		m_pGraphicsBuffer = nullptr;
	}

	/*-----------------------------------------------------------------------------
	Initializes the Renderer.
	Parameters:
	[IN] pGraphicsBuffer	:	pointer to an objectbuffer containing the objects to
	be rendered.
	-----------------------------------------------------------------------------*/
	bool Renderer::Initialize(ObjectBuffer* pGraphicsBuffer,glm::mat4& _2DProjectionref) {
		if (pGraphicsBuffer) {
			m_pGraphicsBuffer = pGraphicsBuffer;
			m_p2DProjMat = &_2DProjectionref;
		} else return false;

		return true;
	}

	/*-----------------------------------------------------------------------------
	Renders the objects to the screen.
	-----------------------------------------------------------------------------*/
	void Renderer::Render( ) {
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
		if (m_pGraphicsBuffer) {
			Render3D( );
			Render2D();
		}
	}

	/*-----------------------------------------------------------------------------
	Renders all the 3DGraphics to the screen.
	-----------------------------------------------------------------------------*/
	void Renderer::Render3D( ) {
		//loop for each object in the buffer...

		RenderParams render_params;
		render_params.View_x_Projection = *(m_pGraphicsBuffer->GetControlCamera( ).GetProjectionMatrix( ));
		render_params.View_x_Projection *= *(m_pGraphicsBuffer->GetControlCamera( ).GetViewMatrix( ));

		Mesh::SetCurrentlyBoundVAO(0);
		GraphicMaterial::SetCurrentlyActiveProgram(0);

		for (auto& graphic:*m_pGraphicsBuffer->GetListOf<Graphic3D>( )) {
			graphic.Render(render_params);
		}

	}

	/*-----------------------------------------------------------------------------
	Renders all the 2DGraphics to the screen.
	-----------------------------------------------------------------------------*/
	void Renderer::Render2D( ) {
		_2DRenderParams params;
		glm::mat4 view = glm::lookAt(
									 glm::vec3(0.0f),
									 glm::vec3(0.0f, 0.0f, -1.0f), 
									 glm::vec3(0.0f, 1.0f, 0.0f)
									 );
		params.ProjectionMat = (*m_p2DProjMat) * view;
		
		glDisable(GL_DEPTH_TEST);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (auto& graphic:*m_pGraphicsBuffer->GetListOf<Graphic2D>( )) {
			graphic.Render(params);
		}

		glEnable(GL_DEPTH_TEST);
	}
}