/******************************************************************************
File	:	ShaderProgram.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "ShaderProgram.h"
#include "Shader.h"
#include <glew.h>

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	Defualt constructor.
	-----------------------------------------------------------------------------*/
	ShaderProgram::ShaderProgram( ) {
		uiProgram = 0;
		bLinked = false;
	}

	/*-----------------------------------------------------------------------------
	Creates the program.
	-----------------------------------------------------------------------------*/
	void ShaderProgram::CreateProgram( ) {
		uiProgram = glCreateProgram( );
	}

	/*-----------------------------------------------------------------------------
	Deletes the Program.
	-----------------------------------------------------------------------------*/
	void ShaderProgram::DeleteProgram( ) {
		if (!bLinked)return;
		bLinked = false;
		glDeleteProgram(uiProgram);
	}

	/*-----------------------------------------------------------------------------
	Adds a shader to the program.
	Parameters:
	[IN]	shShader	:	the shader to add.
	Returns:
	true on success, false on falure.
	-----------------------------------------------------------------------------*/
	bool ShaderProgram::AddShaderToProgram(unShader* shShader) {
		Shader* pShader = (Shader*)shShader;
		if (!pShader->IsLoaded( ))return false;

		glAttachShader(uiProgram, pShader->GetID( ));

		return true;
	}

	/*-----------------------------------------------------------------------------
	Links the program and makes it ready to be used.
	-----------------------------------------------------------------------------*/
	bool ShaderProgram::LinkProgram( ) {
		glLinkProgram(uiProgram);
		int iLinkStatus;
		glGetProgramiv(uiProgram, GL_LINK_STATUS, &iLinkStatus);
		bLinked = iLinkStatus==GL_TRUE;
		return bLinked;
	}

	/*-----------------------------------------------------------------------------
	Makes the program come under use
	-----------------------------------------------------------------------------*/
	void ShaderProgram::UseProgram( ) {
		if (bLinked)glUseProgram(uiProgram);
	}
}
///////////////////////////////////////////////////////////////////////////////