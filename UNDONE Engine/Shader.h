/******************************************************************************
File	:	Shader.h
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
#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

typedef  unsigned int UINT;
#include "unShader.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

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
		void GPU_Upload();
		void DeleteShader( );

		bool IsLoaded( ) { return bLoaded; }
		UINT GetID( ) { return uiShader; }

	private:
		UINT uiShader;		// ID of shader
		int iType;			// GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
		bool bLoaded;		// Whether shader was loaded and compiled
		vector<string> sLines;
	};

}
#endif
///////////////////////////////////////////////////////////////////////////////