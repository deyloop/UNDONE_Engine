/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UN_GAMEOBJECT_H_
#define _UN_GAMEOBJECT_H_
#include "DPointer.h"

namespace UNDONE_ENGINE{
	class unGameObject{
	public:
		#define _GENFUNC_DEC_UNGAMEOBJECT_H_
		#include "GENERATE_FUNCTIONS.h"
		GENFUNCS()

		virtual void RemoveComponentByName(const char* name) = 0;
	};
}
#endif