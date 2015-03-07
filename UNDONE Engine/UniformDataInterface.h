/******************************************************************************
Project	:	UNDONE Engine
File	:	UniformDataInterface.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNIFORMDATAINTERFACE_H
#define _UNIFORMDATAINTERFACE_H

#include "UniformType.h"
#include <vector>
using std::vector;

namespace UNDONE_ENGINE {
	
	/*-------------------------------------------------------------------------
	
	-------------------------------------------------------------------------*/
	struct UniformData {
		UniformType uniformType;
		union data {
			float	Data_f;
			float*	Data_fp;
			int		Data_i;
		} data;
	};

	/*-------------------------------------------------------------------------
	THis structure is used as a meduim of comunication between 3D graphic and 
	GraphicMaterial for them to exchange uniform variable data.
	-------------------------------------------------------------------------*/
	struct UniformDataInterface {
		vector<UniformData> pairs;
	};

	
};

#endif