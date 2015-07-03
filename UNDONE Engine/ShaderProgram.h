/******************************************************************************
File	:	ShaderProgram.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _SHADER_PROG_H_
#define _SHADER_PROG_H_

#include "unShaderProgram.h"

namespace UNDONE_ENGINE {

	class unShader;
	/*-----------------------------------------------------------------------------
	A class that Wraps OpenGL shader program and make its usage easy.
	-----------------------------------------------------------------------------*/
	class ShaderProgram : public unShaderProgram{
	public:
		void CreateProgram( );
		void DeleteProgram( );

		bool AddShaderToProgram(unShader* shShader);
		bool LinkProgram( );

		void UseProgram( );

		UINT GetProgramID( ) { return uiProgram; }

		ShaderProgram( );

	private:
		UINT uiProgram; // ID of program
		bool bLinked;	// Whether program was linked and is ready to use
	};
}
#endif
///////////////////////////////////////////////////////////////////////////////