/******************************************************************************
Project	:	UNDONE Engine
File	:	_2DGraphic.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "_2DGraphic.h"
#include "GameObject.h"
#include "WorldTransform.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "glew.h"
#include <glm.hpp>
#include <gtx\transform.hpp>
#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {

	int _2DGraphic::HMVP			= -1;
	int _2DGraphic::HSampler		= -1;

	int _2DGraphic::screenwidth		= 0;
	int _2DGraphic::screenhieght	= 0;

	unsigned _2DGraphic::m_uiVAO[1] = {0};
	unsigned _2DGraphic::m_uiVBO[3] = {0};
	DPointer<ShaderProgram> _2DGraphic::m_ppShaderProgram;

	_2DGraphic::_2DGraphic( ) { 
		m_ppTexture.m_pointer			= nullptr;
		m_ppWorldTransform.m_pointer	= nullptr;
		m_rect.x = 0.0f;
		m_rect.y = 0.0f;
		m_rect.width = 1.0f;
		m_rect.hieght = 1.0f;
	}

	void _2DGraphic::SetImageRect(rect& rectref) {
		m_rect = rectref;
	}

	_2DGraphic::~_2DGraphic( ) { }

	void _2DGraphic::InitVAO( ) {
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

			unsigned vertIndeces[4] = {0,2,4,6};

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

			glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO[2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float), vertIndeces, GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(vertind_loc, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

		}
	}

	void _2DGraphic::OnParentSet( ) {
		m_ppWorldTransform = m_ppParent->worldTransform;
		if (m_ppWorldTransform.m_pointer) {
			coutput(name+" aquired transform "+m_ppWorldTransform->name.c_str( )+"\n");
			Load( );
		}
	}

	void _2DGraphic::SetTexture(DPointer<Texture> ppTex) {
		if (ppTex.m_pointer) {
			m_ppTexture = ppTex;

			int image_hieght = m_ppTexture->getHeight( );
			int image_width = m_ppTexture->getWidth( );

			m_TranslateCorrection = glm::translate(glm::vec3(-1.0f, -1.0f, 0.0f));
			m_ScaleCorrection = glm::scale(glm::vec3((image_width/(float)screenwidth),
													 image_hieght/(float)screenhieght,
													 1.0f));
			coutput(name+" aquired texture.\n");
		}
	}

	void _2DGraphic::Load( ) {
		
	}


	void _2DGraphic::Render(_2DRenderParams& render_params ) {
		if (m_ppWorldTransform.m_pointer	==	nullptr	||
			m_ppShaderProgram.m_pointer		==	nullptr	||
			m_ppTexture.m_pointer			==	nullptr	
			) {
				return;
			}
		// else proceed with rendering.

		glBindVertexArray(m_uiVAO[0]);
		m_ppTexture->BindTexture(0);
		m_ppTexture->SetFiltering(TEXTURE_FILTER_MAG_NEAREST, TEXTURE_FILTER_MIN_NEAREST);
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
		glUniformMatrix4fv(HMVP, 1, GL_FALSE, &(m_TranslateCorrection*m_ppWorldTransform->GetTransform( )*m_ScaleCorrection)[0][0]);
		glUniform1i(HSampler, 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	}

	void _2DGraphic::Unload( ) {
		
	}

	void _2DGraphic::DeleteVAO( ) {
		glDeleteBuffers(2, m_uiVBO);
		glDeleteVertexArrays(1, m_uiVAO);
	}

	void _2DGraphic::SetShader(DPointer<ShaderProgram> ppShaderProgram) {
		m_ppShaderProgram = ppShaderProgram;
		if (m_ppShaderProgram.m_pointer) {
			m_ppShaderProgram->UseProgram( );
			GLuint progID = m_ppShaderProgram->GetProgramID( );

			HMVP			= glGetUniformLocation(progID, "gMVP");
			HSampler		= glGetUniformLocation(progID, "gSampler");
		}
	}
}
