/******************************************************************************
File	:	Component.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNDONE_COMPONENT_H_
#define _UNDONE_COMPONENT_H_

#include "UNDONE_Engine_declr.h"

class GameObject;	//Forward Declared so we can use it.

/*-----------------------------------------------------------------------------
Components are the biulding blocks of game objects. These may be combined in
GameObjects to give any behavior needed.
-----------------------------------------------------------------------------*/
class UNDONE_API Component {
public:
	Component( );
	~Component( ) { Release( ); }

	virtual void Release( );
	void SetParent(GameObject* const parent);

	char* name[20];
protected:
	GameObject* m_pParent;
private:
	static int num_Components;
}; 

//Static initialisations
int Component::num_Components = 0;
#endif //_UNDONE_COMPONENT_H_

///////////////////////////////////////////////////////////////////////////////