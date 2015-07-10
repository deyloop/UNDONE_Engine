/******************************************************************************
Project	:	UNDONE Engine
File	:	ObjectContainer.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNDONE_OBJECTCONTAINER_H_
#define _UNDONE_OBJECTCONTAINER_H_

#include <vector>
using std::vector;

namespace UNDONE_ENGINE{

	template <class T> class ObjectContainer;

	template <class T>
	class ContIter{
		ObjectContainer<T> *m_pContainer;
		unsigned int m_pos;
	public:
		ContIter(const ObjectContainer<T>* pContainer, unsigned int pos){
			m_pos = pos;
			m_pContainer = pContainer;
		}

		bool operator != (const ContIter<T>& other) const{
			return (m_pContainer != other.m_pContainer) && (m_pos != other.m_pos);
		}

		T& operator * () const;

		const ContIter& operator ++ (){
			m_pos++;
			return *this;
		}
	};

	template <class T>
	class ObjectContainer{
		vector<T*> listof_arrays;
		unsigned int fixed_size;
		unsigned int num_lists;
		unsigned int num_obj_in_last_list;
	public:
		ObjectContainer(){
			fixed_size				= 10;
			num_lists				= 0;
			num_obj_in_last_list	= 0;
		}
		~ObjectContainer(){
			//need to delete all objects.
			for (T* array : listof_arrays){
				delete[] array;
			}
		}

		void Add(T obj){
			if (num_obj_in_last_list == fixed_size){
				//create new list.
				const auto num_elems = fixed_size;
				T* newlist = new T[num_elems];

				//Adding the new list to the vector
				listof_arrays.push_back(newlist);

				//reset counting of last object
				num_obj_in_last_list = 0;
				num_lists++;
			}

			//add the new objet.
			(*listof_arrays[num_lists - 1])[num_obj_in_last_list] = obj;
			num_obj_in_last_list++;
		}

		T& operator [] (const unsigned int pos){
			if (num_lists > 0){
				if (pos <= fixed_size){
					//get the object from first list.
					return (*(listof_arrays[0]))[pos - 1];
				} else {
					const auto list_num = (pos / fixed_size) - 1;
					const auto obj_num = (pos % fixed_size) - 1;
					return (*(listof_arrays[list_num]))[obj_num];
				}
			}
		}

		ContIter<T> begin() const{
			return ContIter(this, 0);
		}

		ContIter<T> end() const{
			return ContIter(this, fixed_size*num_lists - 1);
		}
	};
	template <class T>
	T& ContIter<T>::operator * () const{
		return m_pContainer[m_pos];
	}
}
#endif