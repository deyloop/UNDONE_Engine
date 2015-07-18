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

#ifndef _UN_GRAPHICMATERIAL_H_
#define _UN_GRAPHICMATERIAL_H_

#include "Dptr.h"
#include "unComponent.h"

namespace UNDONE_ENGINE{

	class unShaderProgram;
	/*-------------------------------------------------------------------------
	THe material of the object will decide how it will appear on screen.
	Contains the instructions on how to draw the mesh.
	-------------------------------------------------------------------------*/
	class unGraphicMaterial : public virtual unComponent{
	public:
		virtual void SetShaderProgramToUse(Dptr<unShaderProgram> ppShaderProgram) = 0;

		virtual void SetDiffuseColor(float r, float g, float b) = 0;
		virtual void SetProperty(const char* property_name, float value) = 0;
		virtual void SetProperty(const char* property_name, int value) = 0;
		virtual void SetProperty(const char* property_name, float x, float y, float z) = 0;
		virtual void SetProperty(const char* property_name, float x, float y, float z, float w) = 0;
	};
}
#endif