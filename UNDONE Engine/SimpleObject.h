/******************************************************************************
File	:	SimpleObject.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _SIMPLEOBJECT_H_
#define _SIMPLEOBJECT_H_

#include <cstdio>
/*-----------------------------------------------------------------------------
Summary:	This class defines an object which is the most simple form of
			objects to be used in the Framework. All more complex objects
			will inherit from this object type.
-----------------------------------------------------------------------------*/
class SimpleObject{
public:
	SimpleObject();

	
private:
	static unsigned int num_objects;
};


#endif