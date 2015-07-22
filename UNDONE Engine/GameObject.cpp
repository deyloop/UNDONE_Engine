/******************************************************************************
Project	:	UNDONE Engine
File	:	GameObject.cpp
Author	:	Anurup Dey

		Copyright (C) 2015 Anurup Dey 
		<anu.rup.dey98@gmail.com>

	This file is part of UNDONE-Engine.

	UNDONE-Engine can not be copied and/or distributed without the express
	permission of Anurup Dey. Unauthorized copying of this file, via any
	medium is strictly prohibited.

	Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "GameObject.h"
namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	Default Constructor.
	-----------------------------------------------------------------------------*/
	GameObject::GameObject( ) {
		//Need to set things to default values.
		//But there is nothing to do here.
	}

	/*----------------------------------------------------------------------------
	The Default Destructor.
	----------------------------------------------------------------------------*/
	void GameObject::Release( ) {
		//TODO: See what has to be handled here.
	}
	
	void GameObject::Load( ) {
		//Load all children
		for (auto& childComponent:m_Components) {
			childComponent->Load( );
		}
	}

	void GameObject::Unload( ) {
		//UnLoad all children
		for (auto& childComponent:m_Components) {
			childComponent->Unload( );
		}
	}

	void GameObject::OnParentSet( ) {
		//Tell all children
		for (auto& childComponent:m_Components) {
			childComponent->SetPriority(GetPriority(0)+1,0);
			childComponent->OnParentBeingChilded();
		}
	}

	void GameObject::OnParentBeingChilded( ) {
		//We do nothing...
	}

	void GameObject::Set_Parent(Component* component) {
		component->SetParent(dcast<GameObject, Component>(m_ppMyself));
	}

	#define _GENFUNC_DEF_GAMEOBJECT_CPP_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS_ONLY_FOR_COMPONENTS()
}

