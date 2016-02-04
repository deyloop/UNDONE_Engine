/******************************************************************************
Project	:	UNDONE Engine
File	:	ObjectBuffer.h
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

#ifndef UNDONE_OBJECTBUFFER_H
#define UNDONE_OBJECTBUFFER_H

#include "unEngineInterfaces.h"
#include "Dptr.h"
#include <vector>
#include <list>
#include <algorithm>
#include <type_traits>

#include "Camera.h"
#include "Component.h"
#include "Header.h"

using namespace std;

namespace UNDONE_ENGINE{

	template<typename T>
	struct Binding {
		Binding( ){ptr_list = new list<IPointer*>( ); }
		T object;
		list<IPointer*>* ptr_list;
	};

	/*-------------------------------------------------------------------------
	The Object buffer is the place where all the components of the game are
	physically stored. This Object buffer has the capabiltity to store any
	type of component you throw at it. It also separates objects by ownership.
	-------------------------------------------------------------------------*/
	class ObjectBuffer : public unObjectBuffer{
		list<Dptr<Component>>		m_Components;
		vector<void*>				m_storage_vectors;
		vector<void*>				m_pointer_table_lists;
		vector<size_t>				m_storage_types;
		vector<OwnerShip>			m_storage_owners;
		bool						m_empty;

		Dptr<Camera>				m_Cam;
		unsigned int				m_init_vec_size;
		unsigned int				m_num_owners;

	public:

		ObjectBuffer();
		~ObjectBuffer();

		void SetInitAllocSize(unsigned int size) { m_init_vec_size = size; }
		OwnerShip CreateOwnerShip() { ++m_num_owners; return m_num_owners; }

		template<typename T>
		void DeleteAll(OwnerShip ownership = 0);
		
		template<typename T>
		void Delete(Dptr<T> ptr,OwnerShip ownership = 0);
		
		template<typename T>
		Dptr<T> CreateNew(OwnerShip ownership = 0);

		template<typename T>
		vector<Binding<T>>* GetListOf(OwnerShip ownership = 0);
		template<typename T>
		void SortByPriority(OwnerShip ownership = 0);

		Dptr<unCamera> GetControlCamera( ) { return dcast<unCamera,Camera>(m_Cam); }
		void setControlCamera( Dptr<unCamera> camera );

		Dptr<Component> GetComponentByName(const char* name, OwnerShip ownership = 0);

		template<typename T>
		Dptr<T> GetComponentByNameOfType(const char* name, OwnerShip ownership = 0);
		
#define _GENFUNC_DEC_DOBJECTBUFFER_H_
#include "GENERATE_FUNCTIONS.h"
		GENFUNCS()

	};

	//////////////////////////Definitions//////////////////////////////////////
	//Prototypes of templates used.
	template<typename storagetype>
	bool Reallocating(vector<Binding<storagetype>>& vec_to_check);
	template<typename storagetype>
	void Reallocate_vector(vector<Binding<storagetype>>& storageVector);
	template<typename storagetype>
	Dptr<storagetype> MakeNew(vector<Binding<storagetype>>& storageVector);

	/*-----------------------------------------------------------------------------
	Template function for checking if a container vector is about to relocate or
	not.
	Parameters:
	[IN] storagetype	-	the type of objects that are stored
	[IN] vec_to_check	-	the vector to check.
	Returns:
	true if about to resize, false otherwise.
	-----------------------------------------------------------------------------*/
	template<typename storagetype>
	bool Reallocating(vector<Binding<storagetype>>& vec_to_check) {
		if (!vec_to_check.empty()) {
			if (vec_to_check.size() == vec_to_check.capacity()) {
				//things gonna change
				return true;
			}
		}
		return false;
	}

	/*-----------------------------------------------------------------------------
	Called when a vector reallocates to update the corresponding linked list.
	Parameters:
	[IN] storagetype	-	the type of objects that are stored.
	[IN] storageVector	-	the vector (which is reallocating)
	[IN] storageList	-	the linked list which will be updated.
	-----------------------------------------------------------------------------*/
	template<typename storagetype>
	void Reallocate_vector(vector<Binding<storagetype>>& storageVector) {
		for (Binding<storagetype>& binding : storageVector){
			for (IPointer* pointer : *binding.ptr_list){
				size_t pointer_type = pointer->Get_Type();
				const size_t Component_type = typeid(Component).hash_code();
				if (pointer_type == Component_type){
					((Dptr<Component>*)pointer)->Relink<storagetype>(&binding.object);
				} else {
					((Dptr<storagetype>*)pointer)->Relink<storagetype>(&binding.object);
				}
			}
		}
	}

	/*-----------------------------------------------------------------------------
	Template function that adds an object to the buffer by creating an instance fir
	-st and the returns a pointer-to-pointer to that object created.
	Para meters:
	[IN] storagetype	-	the type of objects that are stored.
	[IN] storageVector	-	the vector (which is reallocating)
	[IN] storageList	-	the linked list.
	-----------------------------------------------------------------------------*/
	template<typename storagetype>
	Dptr<storagetype> MakeNew(vector<Binding<storagetype>>& storageVector) {
		bool reallocate_list = Reallocating<storagetype>(storageVector);

		Binding<storagetype> binding;
		storageVector.push_back(binding);

		if (reallocate_list) {
			Reallocate_vector<storagetype>(storageVector);
		}

		//now create a new pointer and put it in new table.
		Dptr<storagetype> newptr;
		newptr.Object_deleted = false;
		newptr.Link(&storageVector.back().object, storageVector.back().ptr_list);

		return newptr;
	}

	template<typename T>
	Dptr<T> ObjectBuffer::CreateNew(OwnerShip ownership) {
		m_empty = false;

		vector<Binding<T>>*				pvec = nullptr;

		//Check if we already store this type of objects.
		size_t this_type = typeid(T).hash_code();
		for (unsigned x = 0; x<m_storage_owners.size(); ++x) {
			if (m_storage_owners[x] == ownership) {
				if (m_storage_types[x] == this_type) {
					//This type is stored.
					//we now get the corresponding vector and list.
					pvec = (vector<Binding<T>>*)m_storage_vectors[x];
					break;
				}

			}
		}

		if (pvec == nullptr) {
			//the type is not already stored. make arrangements
			//to store it.
			pvec = new vector<Binding<T>>();
			//Make pre-Allocated space.
			pvec->reserve(m_init_vec_size);

			m_storage_vectors.push_back((void*)pvec);
			m_storage_types.push_back(this_type);
			m_storage_owners.push_back(ownership);
		}

		Dptr<T> pointer = MakeNew<T>(*pvec);
		//Components are kept specially, So that they can be
		//searched up by name later
		if (is_base_of<Component, T>::value) {
			//That line above checks if the type is derived from Component
			//or not.

			//So now we proceed...
			Dptr<Component> clrg;
			clrg.Link((Component*)pointer.m_pointer,pointer.m_pPointerTable);

			m_Components.push_back(clrg);
			//give the this DPOinter
			clrg->m_ppMyself = clrg;
		}
		return pointer;
	}

	/*-------------------------------------------------------------------------
	Deletes all objects of the given type.
	Parameters	:
	T	-	the type of objects to be deleted.
	Since the buffer doesn't have access to the type of objects it stores,
	Each system should be responsible for calling this function for each
	type of object it uses.
	----------------------------------------------------------------------------*/
	template<typename T>
	void ObjectBuffer::DeleteAll(OwnerShip ownership) {
		vector<Binding<T>>*				pvec = nullptr;

		//Check if we already store this type of objects.
		size_t this_type = typeid(T).hash_code();
		for (unsigned i = 0; i<m_storage_owners.size(); ++i) {
			if (m_storage_owners[i] == ownership) {
				if (m_storage_types[i] == this_type) {
					//This type is stored.
					//we now get the corresponding vector and list.
					pvec = (vector<Binding<T>>*)m_storage_vectors[i];
					//Now we empty the list and the vector.
					//need to tell each pointer out there that your object
					//has been deleted...
					for (Binding<T>& binding : *pvec ){
						for (IPointer* pointer : *binding.ptr_list){
							pointer->Object_deleted = true;
						}
					}

					pvec->clear();

					//delete the vector and list.
					delete pvec;
				
					//erase the pos in storage.
					m_storage_vectors.erase(m_storage_vectors.begin() + i);
					
					//We don't store this type anymore.
					m_storage_types.erase(m_storage_types.begin() + i);
					m_storage_owners.erase(m_storage_owners.begin() + i);
					return;
				}
			}
		}
		return;
	}

	template<typename T>
	void ObjectBuffer::Delete( Dptr<T> ptr, OwnerShip ownership ) {
		if(!ptr.m_pointer) return;
		cout << "Deleteing\n";
		vector<Binding<T>>* vec = GetListOf<T>(ownership);
		for (Binding<T>& binding : *vec) {
			if (&binding.object == ptr.m_pointer) {
				if (is_base_of<Component, T>::value) {
					Component* comp = (Component*)ptr.m_pointer;
					comp->OnDelete( );

					//removing from the component list.
					for (Dptr<Component> compptr : m_Components) {
						if (compptr.m_pointer == comp) {
							m_Components.remove(compptr);
							break;
						}
					}
				}

				ptr.~Dptr( );
				for (IPointer* pptr : *binding.ptr_list) {
					pptr->Object_deleted = true;
				}

				binding = vec->back( );

				for (IPointer* pointer : *(vec->back().ptr_list)) {
					size_t pointer_type = pointer->Get_Type();
					const size_t Component_type = typeid(Component).hash_code();
					if (pointer_type == Component_type){
						((Dptr<Component>*)pointer)->Relink<T>(&binding.object);
					} else {
						((Dptr<T>*)pointer)->Relink<T>(&binding.object);
					}
				}

				vec->pop_back( );
				break;
			}
		}
	}

	/*----------------------------------------------------------------------------
	Useed to Get a vector of corresponding things.
	----------------------------------------------------------------------------*/
	template<typename T>
	vector<Binding<T>>* ObjectBuffer::GetListOf(OwnerShip ownership) {

		//Check if we already store this type of objects.
		size_t this_type = typeid(T).hash_code();
		for (unsigned x = 0; x<m_storage_owners.size(); ++x) {
			if (m_storage_owners[x] == ownership) {
				if (m_storage_types[x] == this_type) {
					//This type is stored.
					//we now get the corresponding vector
					return ((vector<Binding<T>>*)m_storage_vectors[x]);
				}
			}
		}
		//if execution reaches here, we don't store such an object.
		//In such a case, we create an empty vector and add it under
		//the current ownership. 
		vector<Binding<T>>*	pvec = new vector<Binding<T>>();
		
		//Make pre-Allocated space.
		pvec->reserve(m_init_vec_size);

		m_storage_vectors.push_back((void*)pvec);
		m_storage_types.push_back(this_type);
		m_storage_owners.push_back(ownership);

		return pvec;
	}

	/*----------------------------------------------------------------------------
	Returns a Dpointer to a component of given type and name
	Parameter:
	[IN]	T	:	the type of component.
	[IN]	name:	the name of the componet.
	----------------------------------------------------------------------------*/
	template<typename T>
	Dptr<T> ObjectBuffer::GetComponentByNameOfType(const char* name, OwnerShip ownership) {
		for (Dptr<Component>& component : m_Components) {
			if (component->name == name) {
				//Contruct a DPointer of the given type.
				Dptr<T> returnComp;
				returnComp.Link((T*)(component.m_pointer),component.m_pPointerTable);
				return returnComp;
			}
		}
		//If the program got untill here, that means there isn't a component 
		//present with that name, so we give out a fake one.
		Dptr<T> ErrorComponent;
		ErrorComponent.m_pointer = nullptr;
		return ErrorComponent;
	}
	
	template<class T>
	bool Compare_list(T* ra, T* rb) {
		Component* a = (Component*)ra;
		Component* b = (Component*)rb;
		for (unsigned level = 0;
			a->GetPriority(level) != -1 || b->GetPriority(level) != -1;
			++level) {
			if (a->GetPriority(level) == b->GetPriority(level)) {
				continue;
			}
			else {
				return a->GetPriority(level) <= b->GetPriority(level);
			}
		}
		return a->GetNumber() < b->GetNumber();;
	}

	template<class T>
	bool Compare_vec(T& a, T& b) {
		//Component* a = (Component*)&ra;
		//Component* b = (Component*)&rb;
		for (unsigned level = 0;
			a.object.GetPriority(level) != -1 || b.object.GetPriority(level) != -1;
			++level) {
			if (a.object.GetPriority(level) == b.object.GetPriority(level)) {
				continue;
			}
			else {
				return (a.object.GetPriority(level)) <= (b.object.GetPriority(level));
			}
		}
		return a.object.GetNumber() < b.object.GetNumber();
	}
	
	template<typename T>
	void ObjectBuffer::SortByPriority(OwnerShip ownership) {
		//we proceed to sort, only if T is a type of Component.
		if (!is_base_of<Component, T>::value) {
			return;
		}

		//first, we get the vector and lists to sort,
		vector<Binding<T>>* pvec = nullptr;
		//Check if we already store this type of objects.
		size_t this_type = typeid(T).hash_code();
		for (unsigned x = 0; x<m_storage_owners.size(); ++x) {
			if (m_storage_owners[x] == ownership) {
				if (m_storage_types[x] == this_type) {
					//This type is stored.
					//we now get the corresponding vector and list.
					pvec = (vector<Binding<T>>*)m_storage_vectors[x];
				}

			}
		}

		if (pvec == nullptr) {
			//the type is not already stored.
			return;
		}
		
		//STEP 1: sort the vector..
		sort(pvec->begin(), pvec->end(), Compare_vec<Binding<T>>);
		//STEP 2: relink the list to the vector.
		Reallocate_vector<T>(*pvec);
		//STEP 3 : enjoy the view!
		
		return;
		
	}
}
#endif
