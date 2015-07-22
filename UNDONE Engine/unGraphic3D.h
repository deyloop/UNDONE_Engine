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

#ifndef _UN_GRAPHIC3D_H_
#define _UN_GRAPHIC3D_H_

#include "unComponent.h"

namespace UNDONE_ENGINE{
	class unGraphic3D :public virtual unComponent{
	public:
		virtual ~unGraphic3D(){}
		//no exposed functionality from here.
	};
}

#endif