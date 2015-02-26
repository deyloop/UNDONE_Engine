/******************************************************************************
Project	:	UNDONE Engine
File	:	Component.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Component.h"
#include <iostream>
#include "UNDONE_DEBUG.h"
#include "GameObject.h"
using namespace std;

namespace UNDONE_ENGINE {
	int UNDONE_API Component::num_Components = 0;
	/*-----------------------------------------------------------------------------
	Default Constructor
	-----------------------------------------------------------------------------*/
	Component::Component( ) {
		m_pParent/*.m_pointer*/ = nullptr;
		char str[20];
		sprintf_s(str, "Component_%i", num_Components);
		name = str;
		++num_Components;
		
		coutput("New Component Constructed with name "+name+"\n");

	}

	/*-----------------------------------------------------------------------------
	Default Destructor. Cleans up resoureces.
	-----------------------------------------------------------------------------*/
	void Component::Release( ) {
		m_pParent/*.m_pointer*/ = nullptr;
		coutput("Component "+name+" Released.\n");
	}

	/*-----------------------------------------------------------------------------
	Sets the Parent of the Component.
	Parameters:
	[IN] parent	:	pointer to a GameObject acting as the parent of this Component.
	-----------------------------------------------------------------------------*/
	void Component::SetParent(/*DPointer<*/GameObject*/*>*/ parent) {
		if ((parent/*.ptr()*/)!=nullptr) {
			m_pParent = parent;
			coutput(name+" made child of "+m_pParent->name+"\n");
		}
	}
}