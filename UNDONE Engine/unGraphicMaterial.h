/******************************************************************************
Project	:	UNDONE Engine
File	:
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