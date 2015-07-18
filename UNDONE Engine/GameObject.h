/******************************************************************************
File	:	GameObject.h
Author	:	Anurup Dey

				Copyright (C) 2015  Anurup Dey

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _UNDONE_GAMEOBJECT_H_
#define _UNDONE_GAMEOBJECT_H_
//includes:
#include "Header.h"
#include "unGameObject.h"	//For dll Interface
#include "Dptr.h"		//To be compaible with the framework
#include "Component.h"		//because thats what we are made up of
#include <vector>			//Need to store components together.
#include <typeinfo>			//For handelling types of different /unknown Components
using std::vector;
namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	A game object is any object that is there in the game. Its behavior is
	customized with adding and removing components.
	-----------------------------------------------------------------------------*/
	class GameObject : public unGameObject, public Component {
	public:
		GameObject();
		~GameObject() { Release(); }

		void Release();

		template<class ComponentType>
		Dptr<ComponentType>				GetComponent();

		virtual void Load();
		virtual void Unload();

		template<class ComponentType>
		void AddComponent(Dptr<ComponentType> rComponent);
		template<class ComponentType>
		void RemoveComponent();
		void RemoveComponentByName(const char* name) { };

		virtual void OnParentBeingChilded();

		#define _GENFUNC_DEC_GAMEOBJECT_H_
		#include "GENERATE_FUNCTIONS.h"
		GENFUNCS_ONLY_FOR_COMPONENTS()

	protected:
		void OnParentSet();

	private:
		vector<Dptr<Component>>	m_Components;
		vector<size_t>				m_Component_types;


		void Set_Parent(Component* component);
	};


	/*-----------------------------------------------------------------------------
	Template implimentation for GetComponent. Returns the component of the given
	type, if it is present, otherwise a null pointer.
	-----------------------------------------------------------------------------*/
	template <class ComponentType>
	Dptr<ComponentType> GameObject::GetComponent() {
		Dptr<ComponentType> component;
		

		size_t Requested_type = typeid(ComponentType).hash_code();
		//search if we have such a component type in us,
		unsigned int i = 0;
		for (auto& type : m_Component_types) {
			if (type == Requested_type) {
				component = dcast<ComponentType,Component>(m_Components[i]);
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
	void GameObject::AddComponent(Dptr<ComponentType> rComponent) {
		Set_Parent((Component*)rComponent.ptr());
		size_t new_component_type = typeid(ComponentType).hash_code();
		//Not cjecking if the component already exists, just adding it to 
		//the object
		Dptr<Component> comp;
		comp = dcast<Component,ComponentType>(rComponent);
		m_Components.push_back(comp);
		m_Component_types.push_back(new_component_type);
	}

	/*-----------------------------------------------------------------------------
	Template for removing a component of a given type.
	-----------------------------------------------------------------------------*/
	template<class ComponentType>
	void GameObject::RemoveComponent() {
		size_t Requested_type = typeid(ComponentType).hash_code();
		//search if we have such a component type in us,
		unsigned int i = 0;
		for (auto& type : m_Component_types) {
			if (type == Requested_type) {
				m_Components.erase(m_Components.begin() + i);
				break;
			}
			++i;
		}
	}
}
#endif
///////////////////////////////////////////////////////////////////////////////