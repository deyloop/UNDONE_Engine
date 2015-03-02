/******************************************************************************
Project	:	UNDONE Engine
File	:	GameObject.cpp
Author	:	Anurup Dey
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
	/*-----------------------------------------------------------------------------
	Used to Acces a member Component by name.
	Parameters:
	[IN]	name	-	the name of the component requested.
	Returns:
	the pointer to the component requested.
	----------------------------------------------------------------------------*/
	DPointer<Component>	GameObject::GetComponentByName(const char* name) const {
		
		//Searching for a component with such a name.
		for (auto comp:m_Components) {
			if (comp->name == name) { //checking if name matches
				return comp;
			}
		} 

		//No such thing in here,
		DPointer<Component> fake;
		fake.m_pointer = nullptr;
		return fake;
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
}

