/******************************************************************************
File	:	Component.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNDONE_COMPONENT_H_
#define _UNDONE_COMPONENT_H_

#include "UNDONE_Engine_declr.h"
#include <string>					//We are going to use this to store names
#include "DPointer.h"				//We are associated to the DObjectBuffer.

using namespace std;

namespace UNDONE_ENGINE {


	class GameObject;	//Forward Declared so we can use it.

	/*-----------------------------------------------------------------------------
	Components are the biulding blocks of game objects. These may be combined in
	GameObjects to give any behavior needed.
	-----------------------------------------------------------------------------*/
	class Component {
	public:
		UNDONE_API Component( );
		UNDONE_API ~Component( ) { Release( ); }

		void Release( );
		void SetParent(DPointer<GameObject> ppParent);
		UNDONE_API void Rename(const char* newname);

		UNDONE_API virtual void Load( ) = 0;
		UNDONE_API virtual void Unload( ) = 0;
		
		virtual void OnParentBeingChilded( ) = 0;

		UNDONE_API unsigned GetPriority(unsigned priority_level);
		UNDONE_API void SetPriority(unsigned priority, unsigned priority_level);

		UNDONE_API DPointer<GameObject> GetParent( ) { return m_ppParent; };
		UNDONE_API int GetNumber( ) { return m_number; }
		
		string name;
	
	protected:
		DPointer<GameObject>	m_ppParent;
		DPointer<Component>		m_ppMyself;
#define NUM_MAX_PRIORITIES 2
		int						m_num_priority[NUM_MAX_PRIORITIES];
		int						m_number;
		
		virtual void OnParentSet( ) = 0;
		

		friend class DObjectBuffer;
	private:
		static int num_Components;
	};
	
}
#endif //_UNDONE_COMPONENT_H_

///////////////////////////////////////////////////////////////////////////////