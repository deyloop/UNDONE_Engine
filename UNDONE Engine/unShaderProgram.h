/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UN_SHADERPROGRAM_H_
#define _UN_SHADERPROGRAM_H_

typedef unsigned int UINT;

namespace UNDONE_ENGINE{

	class unShader;

	/*-------------------------------------------------------------------------
	Interface for shader Programs. A class that wraps OpenGL shader Programs
	and makes it easy to use.
	-------------------------------------------------------------------------*/
	class unShaderProgram{
	public:
		virtual void CreateProgram() = 0;
		virtual void DeleteProgram() = 0;

		virtual bool AddShaderToProgram(unShader* shShader) = 0;
		virtual bool LinkProgram() = 0;

	};

}

#endif