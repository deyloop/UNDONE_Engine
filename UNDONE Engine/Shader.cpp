/******************************************************************************
File	:	Shader.cpp
Author	:	Anurup Dey
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
	bool UNDONE_API Shader::LoadShader(string file, int type) {
		FILE* fp = nullptr;
		fopen_s(&fp, file.c_str( ), "rt");
		if (!fp) return false;

		// Get all lines from a file

		vector<string> sLines;
		char sLine[255];
		while (fgets(sLine, 255, fp))sLines.push_back(sLine);
		fclose(fp);

		const char** sProgram = new const char*[sLines.size( )];
		for (unsigned int i = 0; i<sLines.size( ); i++)sProgram[i] = sLines[i].c_str( );

		uiShader = glCreateShader(type);

		glShaderSource((GLuint)uiShader, sLines.size( ), sProgram, NULL);
		glCompileShader(uiShader);

		delete[] sProgram;

		int iCompilationStatus;
		glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);

		if (iCompilationStatus==GL_FALSE) {
			GLsizei len;
			glGetShaderiv(GetID( ), GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len+1];
			glGetShaderInfoLog(GetID( ), len, &len, log);
			SystemComponent::GetInstance( )->ShowMessage(log, "Shader could not compile.");
			delete[] log;
			return false;
		}
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
