/******************************************************************************
File	:	Component.h
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

#ifndef _UNDONE_COMPONENT_H_
#define _UNDONE_COMPONENT_H_

#include "unComponent.h"
#include <string>					//We are going to use this to store names
#include "Dptr.h"				//We are associated to the ObjectBuffer.

using namespace std;

namespace UNDONE_ENGINE {


	class GameObject;	//Forward Declared so we can use it.

	/*-----------------------------------------------------------------------------
	Components are the biulding blocks of game objects. These may be combined in
	GameObjects to give any behavior needed.
	-----------------------------------------------------------------------------*/
	class Component : public virtual unComponent{
	public:
		Component( );
		~Component( ) { Release( ); }

		void Release( );
		void SetParent(Dptr<GameObject> ppParent);
		virtual void Rename(const char* newName);

		virtual void Load( ) = 0;
		virtual void Unload( ) = 0;
		
		virtual void OnParentBeingChilded( ) = 0;

		unsigned GetPriority(unsigned priority_level);
		void SetPriority(unsigned priority, unsigned priority_level);

		Dptr<GameObject> GetParent( ) { return m_ppParent; };
		int GetNumber() { return m_number; }
	
		string name;
	protected:
		Dptr<GameObject>	m_ppParent;
		Dptr<Component>		m_ppMyself;
#define NUM_MAX_PRIORITIES 2
		int						m_num_priority[NUM_MAX_PRIORITIES];
		int						m_number;
		
		virtual void OnParentSet( ) = 0;
		

		friend class ObjectBuffer;
	private:
		static int num_Components;
	};
	
}
#endif //_UNDONE_COMPONENT_H_

///////////////////////////////////////////////////////////////////////////////