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

#ifndef _UN_COMPONENT_
#define _UN_COMPONENT_

namespace UNDONE_ENGINE{
	class unComponent{
	public:
		virtual void Rename(const char*) = 0;
	};
}

#endif