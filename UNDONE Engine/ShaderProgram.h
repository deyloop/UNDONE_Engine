/******************************************************************************
File	:	ShaderProgram.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _SHADER_PROG_H_
#define _SHADER_PROG_H_

#include "UNDONE_Engine_declr.h"
#include "Shader.h"
#include "UNDONE_Engine_declr.h"

/*-----------------------------------------------------------------------------
A class that Wraps OpenGL shader program and make its usage easy.
-----------------------------------------------------------------------------*/
class UNDONE_API ShaderProgram{
public:
	void CreateProgram();
	void DeleteProgram();

	bool AddShaderToProgram(Shader* shShader);
	bool LinkProgram();

	void UseProgram();

	UINT GetProgramID(){ return uiProgram; }

	ShaderProgram();

private:
	UINT uiProgram; // ID of program
	bool bLinked;	// Whether program was linked and is ready to use
};
#endif
///////////////////////////////////////////////////////////////////////////////