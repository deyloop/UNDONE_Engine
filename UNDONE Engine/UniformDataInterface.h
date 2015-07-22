/******************************************************************************
Project	:	UNDONE Engine
File	:	UniformDataInterface.h
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