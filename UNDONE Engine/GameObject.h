/******************************************************************************
File	:	GameObject.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _UNDONE_GAMEOBJECT_H_
#define _UNDONE_GAMEOBJECT_H_
//includes:
#include "UNDONE_Engine_declr.h"	//To make this part of the API
#include "DPointer.h"	//To be compaible with the framework
#include "Component.h"	//because thats what we are made up of
#include <vector>		//Need to store components together.
#include <typeinfo>		//For handelling types of different /unknown Components
using std::vector;
namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	A game object is any object that is there in the game. Its behavior is
	customized with adding and removing components.
	-----------------------------------------------------------------------------*/
	class GameObject : public Component {
	public:
		UNDONE_API GameObject( );
		UNDONE_API ~GameObject( ) { Release( ); }

		void Release( );

		template<class ComponentType>
		DPointer<ComponentType>				GetComponent( ) const;
		UNDONE_API DPointer<Component>		GetComponentByName(const char* name) const;

		UNDONE_API virtual void Load( );
		UNDONE_API virtual void Unload( );

		template<class ComponentType>
		void AddComponent(DPointer<ComponentType> rComponent);
		template<class ComponentType>
		void RemoveComponent( );
		UNDONE_API void RemoveComponentByName(const char* name) { };
		
		UNDONE_API void OnParentBeingChilded( );
	protected:
		UNDONE_API virtual void OnParentSet( );
		
	private:
		vector<DPointer<Component>>	m_Components;
		vector<size_t>				m_Component_types;

		
		UNDONE_API void Set_Parent(Component* component);
	};

#define worldTransform	GetComponent<WorldTransform>()
#define mesh			GetComponent<Mesh>()
#define _3Dgraphic		GetComponent<_3DGraphic>();
#define graphicMaterial GetComponent<GraphicMaterial>();

	/*-----------------------------------------------------------------------------
	Template implimentation for GetComponent. Returns the component of the given
	type, if it is present, otherwise a null pointer.
	-----------------------------------------------------------------------------*/
	template <class ComponentType>
	DPointer<ComponentType> GameObject::GetComponent( ) const {
		DPointer<ComponentType> component;
		component.m_pointer = nullptr;

		size_t Requested_type = typeid(ComponentType).hash_code( );
		//search if we have such a component type in us,
		unsigned int i = 0;
		for (auto& type:m_Component_types) {
			if (type==Requested_type) {
				component.m_pointer = (ComponentType**)m_Components[i].m_pointer;
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
	void GameObject::AddComponent(DPointer<ComponentType> rComponent) {
		Set_Parent((Component*)rComponent.ptr( ));
		size_t new_component_type = typeid(ComponentType).hash_code( );
		//Not cjecking if the component already exists, just adding it to 
		//the object
		DPointer<Component> comp;
		comp.m_pointer = (Component**)rComponent.m_pointer;
		m_Components.push_back(comp);
		m_Component_types.push_back(new_component_type);
	}

	/*-----------------------------------------------------------------------------
	Template for removing a component of a given type.
	-----------------------------------------------------------------------------*/
	template<class ComponentType>
	void GameObject::RemoveComponent( ) {
		size_t Requested_type = typeid(ComponentType).hash_code( );
		//search if we have such a component type in us,
		unsigned int i = 0;
		for (auto& type:m_Component_types) {
			if (type==Requested_type) {
				m_Components.erase(m_Components.begin( )+i)
					break;
			}
			++i;
		}
	}
}
#endif
///////////////////////////////////////////////////////////////////////////////