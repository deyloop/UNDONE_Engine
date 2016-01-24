/******************************************************************************
File	:	Shader.cpp
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
#include "Shader.h"
#include "SystemComponent.h"
#include <glew.h>
#include <vector>
using namespace std;


namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	Defualt Constructor.
	-----------------------------------------------------------------------------*/
	Shader::Shader( ) {
		uiShader = 0;
		iType = 0;
		bLoaded = false;
	}

	void Shader::GPU_Upload( ) {
		if(bLoaded){
			const char** program_code = (new const char*[sLines.size( )]);
			for (unsigned int i = 0; i<sLines.size( ); i++)program_code[i] = const_cast<char*>(sLines[i].c_str( ));
			uiShader = glCreateShader(iType);

			glShaderSource((GLuint)uiShader, sLines.size(), program_code, NULL);
			glCompileShader(uiShader);

			delete[] program_code;

			int iCompilationStatus;
			glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);

			if (iCompilationStatus==GL_FALSE) {
				GLsizei len;
				glGetShaderiv(GetID( ), GL_INFO_LOG_LENGTH, &len);

				GLchar* log = new GLchar[len+1];
				glGetShaderInfoLog(GetID( ), len, &len, log);
				SystemComponent::GetInstance( )->ShowMessage(log, "Shader could not compile.");
				delete[] log;
				//TODO: Do I need to Delete the shader?
				return;
			}
		}
	}

	/*-----------------------------------------------------------------------------
	Laods the shader from the given file name. Makes it ready to be used and linked
	by a program.
	Parameters:
	[IN]	file	:	string containing the file name from which to load.
	[IN]	type	:	GL_VERTEX_SHADER, GL_FRAGMENT_SHADER... stating the type of
	shader this is.
	Returns:
	true on successful compilation, false on falure.
	-----------------------------------------------------------------------------*/
	bool Shader::LoadShader(const char* file, int type) {
		FILE* fp = nullptr;
		fopen_s(&fp, file, "rt");
		if (!fp) return false;

		// Get all lines from a file

	
		char sLine[255];
		while (fgets(sLine, 255, fp))sLines.push_back(sLine);
		fclose(fp);

		
		
		iType = type;
		bLoaded = true;

		return true;
	}

	/*-----------------------------------------------------------------------------
	As advertized, deletes the shader.
	-----------------------------------------------------------------------------*/
	void Shader::DeleteShader( ) {
		if (!IsLoaded( ))return;
		bLoaded = false;
		glDeleteShader(uiShader);
	}

}
