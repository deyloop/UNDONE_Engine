/******************************************************************************
Project	:	UNDONE Engine
File	:	ObjectContainer.h
Author	:	Anurup Dey

Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>

This file is part of UNDONE-Engine.

UNDONE-Engine can not be copied and/or distributed without the express
permission of Anurup Dey. Unauthorized copying of this file, via any
medium is strictly prohibited.

Proprietary and confidential.

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
		ContIter(ObjectContainer<T>* pContainer, unsigned int pos){
			m_pos = pos;
			m_pContainer = pContainer;
		}

		bool operator != (ContIter<T>& other){
			return (m_pContainer != other.m_pContainer) && (m_pos != other.m_pos);
		}

		T& operator * ();

		ContIter& operator ++ (){
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
			if ((num_obj_in_last_list == fixed_size)||(num_lists == 0)){
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
			(listof_arrays[num_lists - 1])[num_obj_in_last_list] = obj;
			num_obj_in_last_list++;
		}

		T& operator [] (unsigned int pos){
			return at(pos);
		}

		T& at(unsigned int pos){
			if (num_lists > 0){
				if (pos < fixed_size){
					//get the object from first list.
					return ((listof_arrays[0]))[pos];
				}
				else {
					auto list_num = (pos / fixed_size);
					auto obj_num = (pos % fixed_size);
					return ((listof_arrays[list_num]))[obj_num];
				}
			}
			T newT;
			Add(newT);
			return *(this->end());
		}

		ContIter<T> begin() {
			return ContIter<T>(this, 0);
		}

		ContIter<T> end() {
			return ContIter<T>(this, fixed_size*num_lists - 1);
		}
	};
	template <class T>
	T& ContIter<T>::operator * () {
		return m_pContainer->at(m_pos);
	}
}
#endif