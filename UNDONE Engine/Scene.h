/******************************************************************************
Project	:	UNDONE Engine
File	:	Scene.h
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

#ifndef UNDONE_SCENE_H
#define UNDONE_SCENE_H

namespace UNDONE_ENGINE{
	typedef  unsigned int OwnerShip;
	
	class ObjectBuffer;

	/*-----------------------------------------------------------------------------
	The scene represents a segment of the game or application having its own memory
	space and set of objects.Think of them as separate levels. They can be loaded 
	samultaneousely and freed independent of each other. THis is an abstract 
	interface. The User can create any behavior they want in a scene.
	-----------------------------------------------------------------------------*/
	class Scene {
	public:
		virtual void Load(ObjectBuffer* pObjectBuffer)	= 0;
		virtual void UnLoad( )	= 0;
		virtual void Release( ) = 0;

		virtual void Update( )	= 0;

		virtual void Pause( )	= 0;
		virtual void Resume( )	= 0;

		OwnerShip GetOwnerShip( ) { return m_ownerShip; }
	protected:
		OwnerShip m_ownerShip;
	};

}
#endif