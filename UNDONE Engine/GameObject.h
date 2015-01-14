/******************************************************************************
File	:	GameObject.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _UNDONE_GAMEOBJECT_H_
#define _UNDONE_GAMEOBJECT_H_
//includes:
#include "Component.h"	//because thats what we are made up of
#include <vector>		//Need to store components together.
#include <typeinfo>		//For handelling types of different /unknown Components
using std::vector;
/*-----------------------------------------------------------------------------
A game object is any object that is there in the game. Its behavior is 
customized with adding and removing components.
-----------------------------------------------------------------------------*/
class GameObject : public Component {
public:
	GameObject( );
	~GameObject( ) { Release( ); }

	void Release( );

	template<class ComponentType>
	ComponentType*	GetComponent( ) const;
	Component*		GetComponentByName(const char* name) const;

	template<class ComponentType>
	void AddComponent(ComponentType& rComponent);
	template<class ComponentType>
	void RemoveComponent( );
	void RemoveComponentByName(const char* name);

private:
	vector<Component*>	m_Components;
	vector<size_t>		m_Component_types;
};
#endif

/*-----------------------------------------------------------------------------
Template implimentation for GetComponent. Returns the component of the given 
type, if it is present, otherwise a null pointer.
-----------------------------------------------------------------------------*/
template <class ComponentType>
ComponentType* GameObject::GetComponent( ) const {
	ComponentType* component = nullptr;
	size_t Requested_type = typeid(ComponentType).hash_code();
	//serch if we have such a component type in us,
	unsigned int i = 0;
	for (auto& type:m_Component_types) {
		if (type==Requested_type) {
			component = (ComponentType*)m_Components[i];
			break;
		} 
		++i;
	}

	return component;
}

/*-----------------------------------------------------------------------------
Template function for adding a component.
-----------------------------------------------------------------------------*/
template<class ComponentType>
void GameObject::AddComponent(ComponentType& rComponent) {
	size_t new_component_type = typeid(ComponentType).hash_code( );
	//Not cjecking if the component already exists, just adding it to the object
	m_Components.push_back((Component*)&rComponent);
	m_Component_types.push_back(new_component_type);
	//Done.
}

/*-----------------------------------------------------------------------------
Template for removing a component of a given type.
-----------------------------------------------------------------------------*/
template<class ComponentType>
void GameObject::RemoveComponent( ) {
	ComponentType* component = nullptr;
	size_t Requested_type = typeid(ComponentType).hash_code( );
	//serch if we have such a component type in us,
	unsigned int i = 0;
	for (auto& type:m_Component_types) {
		if (type==Requested_type) {
			component = (ComponentType*)m_Components[i];
			break;
		}
		++i;
	}
}
///////////////////////////////////////////////////////////////////////////////