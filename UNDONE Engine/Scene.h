/******************************************************************************
Project	:	UNDONE Engine
File	:	Scene.h
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