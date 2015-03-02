/******************************************************************************
Project	:	UNDONE Engine
File	:	GraphicMaterial.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "GraphicMaterial.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "glew.h"
#include "SystemComponent.h"
#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {

	unsigned int GraphicMaterial::s_ActiveShaderProgram = 0;

	/*-------------------------------------------------------------------------
	Default Constructor.
	-------------------------------------------------------------------------*/
	GraphicMaterial::GraphicMaterial( ) {
		m_num_parents = 0;
		m_ppShaderProgram.m_pointer = nullptr;
		m_diffcolor = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	void GraphicMaterial::OnParentSet() {
		if (m_num_parents==0) {
			++m_num_parents;
			Load( );
			return;
		} else {
			++m_num_parents;
		}

	}

	void GraphicMaterial::OnParentBeingChilded( ) {

	}

	/*-----------------------------------------------------------------------------
	Sets the shader program which must be used to render the graphic.
	Parameters:
	[IN]	pProgram	:	the pointer to the program to be used.
	-----------------------------------------------------------------------------*/
	void GraphicMaterial::SetShaderProgramToUse(DPointer<ShaderProgram> ppProgram) {
		m_ppShaderProgram = ppProgram;
		if (m_ppShaderProgram.m_pointer!=nullptr) {
			coutput(name+" aquired Shader Program\n");
		}
	}

	void GraphicMaterial::Load( ) {
		if (m_ppShaderProgram.m_pointer) {
			//fill out the uniform details.
			GLuint progID = m_ppShaderProgram->GetProgramID( );

			int HMVP = glGetUniformLocation(progID, "gMVP");
			int HWORLD = glGetUniformLocation(progID, "gWorld");
			int HDIFFUSE = glGetUniformLocation(progID, "gDiffuse");

			m_UniformDataLocations.push_back(HMVP);
			m_UniformDataLocations.push_back(HWORLD);
			m_UniformDataLocations.push_back(HDIFFUSE);

			UniformDataPair pair1, pair2;
			pair1.uniformType = UNIFORMTYPE_MODELVIEWPROJECTIONMATRIX;
			pair2.uniformType = UNIFORMTYPE_WORLDTRANSFORMATIONMATRIX;

			m_DataInterface.pairs.push_back(pair1);
			m_DataInterface.pairs.push_back(pair2);
		}
	}

	void GraphicMaterial::Unload( ) {

	}

	void GraphicMaterial::ApplyMaterial( ) {
		if (m_ppShaderProgram.m_pointer==nullptr) return;

		if (s_ActiveShaderProgram!=m_ppShaderProgram->GetProgramID( )) {
			m_ppShaderProgram->UseProgram( );
			s_ActiveShaderProgram = m_ppShaderProgram->GetProgramID( );
		}
		if (glGetError( )) {
			SystemComponent::GetInstance( )->ShowMessage("", "");
		}

		glUniformMatrix4fv(m_UniformDataLocations[0], 1, GL_FALSE, m_DataInterface.pairs[0].data.Data_fp);
		glUniformMatrix4fv(m_UniformDataLocations[1], 1, GL_FALSE, m_DataInterface.pairs[1].data.Data_fp);
		glUniform3fv(m_UniformDataLocations[2], 1, &m_diffcolor[0]);
	}

}