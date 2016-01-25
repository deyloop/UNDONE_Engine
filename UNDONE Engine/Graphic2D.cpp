/******************************************************************************
Project	:	UNDONE Engine
File	:	Graphic2D.h
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
#include "Graphic2D.h"
#include "GameObject.h"
#include "WorldTransform.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "glew.h"
#include <glm.hpp>
#include <gtx\transform.hpp>
#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {

	int Graphic2D::HMVP			= -1;
	int Graphic2D::HSampler		= -1;

	int Graphic2D::screenwidth		= 0;
	int Graphic2D::screenhieght	= 0;

	unsigned Graphic2D::m_uiVAO[1] = {0};
	unsigned Graphic2D::m_uiVBO[3] = {0};
	Dptr<ShaderProgram> Graphic2D::m_ppShaderProgram;

	Graphic2D::Graphic2D( ) { 
		m_ppTexture.m_pointer			= nullptr;
		m_ppWorldTransform.m_pointer	= nullptr;
		m_rect.x = 0.0f;
		m_rect.y = 0.0f;
		m_rect.width = 1.0f;
		m_rect.hieght = 1.0f;
	}

	void Graphic2D::SetImageRect(rect& rectref) {
		m_rect = rectref;
	}

	Graphic2D::~Graphic2D( ) { }

	void Graphic2D::InitVAO( ) {
		if (m_ppShaderProgram.m_pointer) {
			int progID = m_ppShaderProgram->GetProgramID( );
			int vertexpos_loc = glGetAttribLocation(progID, "inPosition");
			int texcoord_loc = glGetAttribLocation(progID, "inTexCoord");
			int vertind_loc = glGetAttribLocation(progID, "inVertIndices");
			
			float vertices[12] = {
				0.0f, 2.0f, 0.0f,	//top left
				0.0f, 0.0f, 0.0f,	//bottom left
				2.0f, 2.0f, 0.0f,	//top right
				2.0f, 0.0f, 0.0f	//bottom right
			};

			float texture_coords[8] = {
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 0.0f
			};

			glGenVertexArrays(1, m_uiVAO);
			glGenBuffers(3, m_uiVBO);

			glBindVertexArray(m_uiVAO[0]);
			
			glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO[0]);
			glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(vertexpos_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO[1]);
			glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), texture_coords, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
			
		}
	}

	void Graphic2D::OnParentSet( ) {
		m_ppWorldTransform = m_ppParent->GetComponent<WorldTransform>();
		if (m_ppWorldTransform.m_pointer) {
			coutput(name+" aquired transform "+m_ppWorldTransform->name.c_str( )+"\n");
		}
	}

	void Graphic2D::SetTexture(Dptr<unTexture> ppTex) {
		if (ppTex.m_pointer) {
			m_ppTexture = dcast<Texture,unTexture>(ppTex);

			int image_hieght = m_ppTexture->getHeight( );
			int image_width = m_ppTexture->getWidth( );

			m_ScaleCorrection = glm::scale(glm::vec3((image_width/(float)screenwidth),
													 image_hieght/(float)screenhieght,
													 1.0f));
			coutput(name+" aquired texture.\n");
		}
	}

	void Graphic2D::Load( ) {
		
	}

	void Graphic2D::GPU_Upload( ) {

		if (m_ppShaderProgram.m_pointer) {
			GLuint progID = m_ppShaderProgram->GetProgramID( );

			HMVP			= glGetUniformLocation(progID, "gMVP");
			HSampler		= glGetUniformLocation(progID, "gSampler");
		}

	}


	void Graphic2D::Render(_2DRenderParams& render_params ) {
		if (m_ppWorldTransform.m_pointer	==	nullptr	||
			m_ppShaderProgram.m_pointer		==	nullptr	||
			m_ppTexture.m_pointer			==	nullptr	
			) {
				return;
			}
		// else proceed with rendering.

		glBindVertexArray(m_uiVAO[0]);
		m_ppTexture->BindTexture(0);
		m_ppTexture->setFiltering(TEXTURE_FILTER_MAG_NEAREST, TEXTURE_FILTER_MIN_NEAREST);
		int progID = m_ppShaderProgram->GetProgramID( );
		m_ppShaderProgram->UseProgram( );

		float Rect_coords[8] = {
			m_rect.x		,		m_rect.hieght	,
			m_rect.x		,		m_rect.y		,
			m_rect.width	,		m_rect.hieght	,
			m_rect.width	,		m_rect.y
		};

		HRECT = glGetUniformLocation(progID, "gRect");

		glUniform1fv(HRECT, 8, Rect_coords);
		glUniformMatrix4fv(HMVP, 1, GL_FALSE, &(m_ppWorldTransform->GetTransform( )*m_ScaleCorrection)[0][0]);
		glUniform1i(HSampler, 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	}

	void Graphic2D::Unload( ) {
		
	}

	void Graphic2D::DeleteVAO( ) {
		glDeleteBuffers(2, m_uiVBO);
		glDeleteVertexArrays(1, m_uiVAO);
	}

	void Graphic2D::SetShader(Dptr<ShaderProgram> ppShaderProgram) {
		m_ppShaderProgram = ppShaderProgram;
		
	}
}
