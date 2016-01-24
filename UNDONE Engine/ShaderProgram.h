/******************************************************************************
File	:	ShaderProgram.h
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

#ifndef _SHADER_PROG_H_
#define _SHADER_PROG_H_

#include "unShaderProgram.h"
#include <vector>
using namespace std;

namespace UNDONE_ENGINE {

	class unShader;
	class Shader;
	/*-----------------------------------------------------------------------------
	A class that Wraps OpenGL shader program and make its usage easy.
	-----------------------------------------------------------------------------*/
	class ShaderProgram : public unShaderProgram{
	public:
		void CreateProgram( );
		void DeleteProgram( );

		bool AddShaderToProgram(unShader* shShader);
		bool LinkProgram( );
		void GPU_Upload();

		void UseProgram( );

		const UINT GetProgramID( ) const { return uiProgram; }
		const bool IsLinked() const;
		ShaderProgram( );

	private:
		UINT uiProgram; // ID of program
		static UINT CurrentProgramInUse;
		vector<Shader*> shaders;
	};
}
#endif
///////////////////////////////////////////////////////////////////////////////