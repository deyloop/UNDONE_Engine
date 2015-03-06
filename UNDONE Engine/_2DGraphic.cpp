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
#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {

	unsigned _2DGraphic::m_uiVAO[1] = {0};
	unsigned _2DGraphic::m_uiVBO[2] = {0, 0};
	DPointer<ShaderProgram> _2DGraphic::m_ppShaderProgram;

	_2DGraphic::_2DGraphic( ) { 
		m_ppTexture.m_pointer			= nullptr;
		m_ppWorldTransform.m_pointer	= nullptr;
	}


	_2DGraphic::~_2DGraphic( ) { }

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
			coutput(name+" aquired texture.\n");
		}
	}

	void _2DGraphic::Load( ) {
		if (m_ppTexture.m_pointer && m_ppShaderProgram.m_pointer) {
			float vertices[12] = {
				-1.0f,	1.0f,	0.0f,
				-1.0f,	-1.0f,	0.0f,
				1.0f,	1.0f,	0.0f,
				1.0f,	-1.0f,	0.0f
			};

			float texture_coords[8] = {
				0.0f,0.0f,
				0.0f,1.0f,
				1.0f,0.0f,
				1.0f,1.0f
			};

			glGenVertexArrays(1, m_uiVAO);
			glGenBuffers(2, m_uiVBO);

			glBindVertexArray(m_uiVAO[0]);

			int progID = m_ppShaderProgram->GetProgramID( );
			int vertexpos_loc = glGetAttribLocation(progID, "inPosition");
			int texcoord_loc = glGetAttribLocation(progID, "inTexCoord");

			glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO[0]);
			glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), &vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(vertexpos_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO[1]);
			glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), &texture_coords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, 0, 0);

		}
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

		int HMVP = glGetUniformLocation(progID, "gMVP");
		int HSampler = glGetUniformLocation(progID, "gSampler");

		glUniformMatrix4fv(HMVP, 1, GL_FALSE, &(m_ppWorldTransform->GetTransform( ))[0][0]);
		glUniform1i(HSampler, 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void _2DGraphic::Unload( ) {
		glDeleteBuffers(2, m_uiVBO);
		glDeleteVertexArrays(1, m_uiVAO);
	}

	void _2DGraphic::SetShader(DPointer<ShaderProgram> ppShaderProgram) {
		m_ppShaderProgram = ppShaderProgram;
	}
}
