/******************************************************************************
Project	:	UNDONE Engine
File	:	ObjectBuffer.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef UNDONE_OBJECTBUFFER_H
#define UNDONE_OBJECTBUFFER_H

#include "UnObjectBuffer.h"
#include "Dptr.h"
#include <vector>
#include <list>
#include <algorithm>
#include <type_traits>

#include "Camera.h"
#include "Component.h"

using namespace std;

namespace UNDONE_ENGINE{



	/*-------------------------------------------------------------------------
	The Object buffer is the place where all the components of the game are
	physically stored. This Object buffer has the capabiltity to store any
	type of component you throw at it. It also separates objects by ownership.
	-------------------------------------------------------------------------*/
	class ObjectBuffer : public UnObjectBuffer{
	};
}

#endif