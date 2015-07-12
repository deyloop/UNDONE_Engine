/******************************************************************************
Project	:	UNDONE Engine
File	:	UnObjectBuffer.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UN_OBJECTBUFFER_H_
#define _UN_OBJECTBUFFER_H_

#include "Dptr.h"

namespace UNDONE_ENGINE{
	
	//all the types of components::
	#define _GEN_FORWARD_DEC_COMPS_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()
	#define _GEN_FORWARD_DEC_COMPS_INT_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()

	class Camera;

	typedef  unsigned int OwnerShip;

	/*-------------------------------------------------------------------------
	THe Object buffer is the place where all the components of the game are
	physically stored. THis Object buffer has the capabiltity to store any
	type of component you throw at it.
	-------------------------------------------------------------------------*/
	class UnObjectBuffer{
	public:
		virtual void SetInitAllocSize(unsigned int size) = 0;
		virtual OwnerShip CreateOwnerShip() = 0;

		#define _GENFUNC_DEC_UNOBJECTBUFFER_H_
		#include "GENERATE_FUNCTIONS.h"
		GENFUNCS()
		
		virtual Camera& GetControlCamera() = 0;
	};
};
#endif