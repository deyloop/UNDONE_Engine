/******************************************************************************
Project	:	UNDONE Engine
File	:	UniformType.h
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

#ifndef _UNIFORMTYPE_H
#define _UNIFORMTYPE_H

namespace UNDONE_ENGINE {
	/*-------------------------------------------------------------------------
	Enumerates the various types of UNiform variables that can be passed to a 
	GLSL shader. Used as a medium of comunication between Graphical Materials
	and 3D Graphic objects.
	-------------------------------------------------------------------------*/
	enum UniformType {
		UNIFORMTYPE_WORLDTRANSFORMATIONMATRIX,
		UNIFORMTYPE_MODELVIEWPROJECTIONMATRIX,
		UNIFORMTYPE_GLTYPE,
		UNIFORMTYPE_UNKOWNDATA
	};
}

#endif