/******************************************************************************
File	:	Component.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNDONE_COMPONENT_H_
#define _UNDONE_COMPONENT_H_
class GameObject;	//Forward Declared so we can use it.

/*-----------------------------------------------------------------------------
Components are the biulding blocks of game objects. These may be combined in
GameObjects to give any behavior needed.
-----------------------------------------------------------------------------*/
class Component {
public:
	Component( );
	virtual ~Component( ) { Release( ); }

	virtual void Release( );

	const char* name[20];
	GameObject* m_pParent;
}; //end of Component class
#endif //_UNDONE_COMPONENT_H_

///////////////////////////////////////////////////////////////////////////////