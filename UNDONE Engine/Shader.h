/******************************************************************************
File	:	Shader.h
Author	:	Anurup Dey

Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>

This file is part of UNDONE-Engine.

UNDONE-Engine can not be copied and/or distributed without the express
permission of Anurup Dey. Unauthorized copying of this file, via any
medium is strictly prohibited.

Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

typedef  unsigned int UINT;
#include "unShader.h"

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	This class represents a shader. A shader is an arbitrary program which is
	executed directly on the GPU or graphics hardware. Several shaders make a
	shader program.
	-----------------------------------------------------------------------------*/
	class Shader : public unShader {
	public:
		Shader( );
		~Shader( ) { DeleteShader( ); }

		bool LoadShader(const char* file, int type);
		void DeleteShader( );

		bool IsLoaded( ) { return bLoaded; }
		UINT GetID( ) { return uiShader; }

	private:
		UINT uiShader;		// ID of shader
		int iType;			// GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
		bool bLoaded;		// Whether shader was loaded and compiled
	};

}
#endif
///////////////////////////////////////////////////////////////////////////////