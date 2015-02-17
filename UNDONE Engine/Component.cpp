/******************************************************************************
Project	:	UNDONE Engine
File	:	Component.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Component.h"
#include <cstdio>
using namespace std;

/*-----------------------------------------------------------------------------
Default Constructor
-----------------------------------------------------------------------------*/
Component::Component( ) {
	m_pParent = nullptr;
	sprintf(*name, "Component_%i", num_Components);
	++num_Components;
}

/*-----------------------------------------------------------------------------
Default Destructor. Cleans up resoureces.
-----------------------------------------------------------------------------*/
void Component::Release( ) {
	m_pParent = nullptr;
}

/*-----------------------------------------------------------------------------
Sets the Parent of the Component.
Parameters:
[IN] parent	:	pointer to a GameObject acting as the parent of this Component.
-----------------------------------------------------------------------------*/
void Component::SetParent(GameObject*  const parent) {
	if (parent!=nullptr) {
		m_pParent = parent;
	}
}