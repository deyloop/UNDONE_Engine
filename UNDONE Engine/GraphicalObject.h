/******************************************************************************
File	:	GraphicalObject.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _GRAPHICALOBJECT_H_
#define _GRAPHICALOBJECT_H_

#include "SimpleObject.h"

/*-----------------------------------------------------------------------------
This class of objects hold an object type which is used by the graphic engine
to draw images on the screen
-----------------------------------------------------------------------------*/
class GraphicalObject :public SimpleObject{
public:
	GraphicalObject(){}

	virtual void Release()			= 0;
	virtual void Render()			= 0;

	virtual void OnInit()			= 0;
	virtual void OnDestroy()		= 0;
};
#endif
///////////////////////////////////////////////////////////////////////////////