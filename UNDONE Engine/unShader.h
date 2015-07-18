/******************************************************************************
Project	:	UNDONE Engine
File	:
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