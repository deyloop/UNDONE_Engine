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
	class UNDONE_API Component {
	public:
		Component( );
		~Component( ) { Release( ); }

		void Release( );
		virtual void SetParent(DPointer<GameObject> ppParent);
		virtual void Rename(char* newname);
		string name;
	protected:
		DPointer<GameObject> m_ppParent;
		DPointer<Component> m_ppMyself;
		friend class DObjectBuffer;
	private:
		static int num_Components;
	};
	
}
#endif //_UNDONE_COMPONENT_H_

///////////////////////////////////////////////////////////////////////////////