/******************************************************************************
Project	:	UNDONE Engine
File	:	unMesh.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UN_MESH_H_
#define _UN_MESH_H_
namespace UNDONE_ENGINE{
	/*----------------------------------------------------------------------------
	A Mesh data structure holds data about geometry. Must be used in conjuction
	with a Graphic3D Compnent to work properly.
	----------------------------------------------------------------------------*/
	class unMesh{
	public:
		virtual void SetModelFile(const char* filename) = 0;
	};
}
#endif