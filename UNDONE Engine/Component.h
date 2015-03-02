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
#include <vector>
#include <deque>
using namespace std;
namespace UNDONE_ENGINE {


	class GameObject;	//Forward Declared so we can use it.

	/*-----------------------------------------------------------------------------
	Components are the biulding blocks of game objects. These may be combined in
	GameObjects to give any behavior needed.
	-----------------------------------------------------------------------------*/
	class UNDONE_API Component {
	public:
		Component( );
		~Component( ) { Release( ); }

		void Release( );
		void SetParent(DPointer<GameObject> ppParent);
		void Rename(string newname);

		virtual void Load( ) = 0;
		virtual void Unload( ) = 0;
		
		virtual void OnParentBeingChilded( ) = 0;

		unsigned GetPriority(unsigned priority_level);
		void SetPriority(unsigned priority, unsigned priority_level);

		DPointer<GameObject> GetParent( ) { return m_ppParent; };
		int GetNumber( ) { return m_number; }
		
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