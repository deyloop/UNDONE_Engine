/******************************************************************************
Project	:	UNDONE Engine
File	:	UniformType.h
Author	:	Anurup Dey
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