/******************************************************************************
Project	:	UNDONE Engine
File	:	Scene.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef UNDONE_SCENE_H
#define UNDONE_SCENE_H

namespace UNDONE_ENGINE{
	typedef  unsigned int OwnerShip;
/*-----------------------------------------------------------------------------
The scene represents a segment of the game or application having its own memory
space and set of objects.Think of them as separate levels. They can be loaded 
samultaneousely and freed independent of each other. THis is an abstract 
interface. The User can create any behavior they want in a scene.
-----------------------------------------------------------------------------*/
	class Scene {
	public:
		virtual void Load( )	= 0;
		virtual void UnLoad( )	= 0;
		virtual void Release( ) = 0;
	protected:
		OwnerShip m_ownerShip;
	};
}
#endif