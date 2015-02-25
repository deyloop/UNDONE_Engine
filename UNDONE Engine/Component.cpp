/******************************************************************************
Project	:	UNDONE Engine
File	:	Component.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Component.h"
#include <cstdio>
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
	}

	/*-----------------------------------------------------------------------------
	Default Destructor. Cleans up resoureces.
	-----------------------------------------------------------------------------*/
	void Component::Release( ) {
		m_pParent/*.m_pointer*/ = nullptr;
	}

	/*-----------------------------------------------------------------------------
	Sets the Parent of the Component.
	Parameters:
	[IN] parent	:	pointer to a GameObject acting as the parent of this Component.
	-----------------------------------------------------------------------------*/
	void Component::SetParent(/*DPointer<*/GameObject*/*>*/ parent) {
		if ((parent/*.ptr()*/)!=nullptr) {
			m_pParent = parent;
		}
	}
}