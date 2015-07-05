/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UN_SHADER_H_
#define _UN_SHADER_H_

typedef  unsigned int UINT;

namespace UNDONE_ENGINE{

	/*----------------------------------------------------------------------------
	Shaders contain functional code that will instruct the Graphical Processing
	UNit what operation to perform on the Graphics Pipeline.
	It is essentially an Arbitrary program that gets executed directly on the GPU.
	Several shaders make a shader Program.
	----------------------------------------------------------------------------*/
	class unShader{
	public:
		virtual bool LoadShader(const char* file, int type) = 0;
		virtual bool IsLoaded() = 0;
	};
}

#endif