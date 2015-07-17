/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UN_GAMEOBJECT_H_
#define _UN_GAMEOBJECT_H_
#include "Dptr.h"
#include "unComponent.h"

namespace UNDONE_ENGINE{
	class unGameObject: public virtual unComponent{
	public:
		#define _GENFUNC_DEC_UNGAMEOBJECT_H_
		#include "GENERATE_FUNCTIONS.h"
		GENFUNCS_ONLY_FOR_COMPONENTS()

		virtual void RemoveComponentByName(const char* name) = 0;
	};
}
#endif