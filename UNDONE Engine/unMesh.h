/******************************************************************************
Project	:	UNDONE Engine
File	:	unMesh.h
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