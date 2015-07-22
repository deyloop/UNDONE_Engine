/******************************************************************************
Project	:	UNDONE Engine
File	:	unMesh.h
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

#ifndef _UN_MESH_H_
#define _UN_MESH_H_

#include "unComponent.h"
namespace UNDONE_ENGINE{
	/*----------------------------------------------------------------------------
	A Mesh data structure holds data about geometry. Must be used in conjuction
	with a Graphic3D Compnent to work properly.
	----------------------------------------------------------------------------*/
	class unMesh : public virtual unComponent{
	public:
		virtual void SetModelFile(const char* filename) = 0;
	};
}
#endif