/******************************************************************************
Project	:	UNDONE Engine
File	:
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

#ifndef _UNDONE_DPTR_H_
#define _INDONE_DPTR_H_

#include <list>
#include <typeinfo>
//#include "Header.h"
;
using std::list;

namespace UNDONE_ENGINE{

	class IPointer{
	public:
		bool Object_deleted;
		virtual size_t Get_Type() = 0;
	};

	template <typename T>
	class Dptr : public IPointer{
		bool linked;

		void Initialize(){
			m_pointer		= nullptr;
			m_pPointerTable = nullptr;
			Object_deleted	= true;
			linked			= false;
		}

	public:
		T*	m_pointer;
		list<IPointer*>* m_pPointerTable;

		Dptr(){
			Initialize();
		}

		~Dptr(){
			//remove yourself from the table.
			if ((!Object_deleted) && m_pPointerTable)
				if (m_pPointerTable->size() != 0)
					m_pPointerTable->remove((IPointer*)this);
		}

		Dptr(Dptr<T> const & other){
			Initialize();
			*this = other;
		}

		T* operator -> ()	{ return m_pointer; }
		T& operator * ()	{ return *m_pointer; }
		T* ptr()			{ return m_pointer; }
		T& Obj()			{ return *m_pointer; }
		
	
		Dptr<T>& operator = (Dptr<T> const & other){
			if (linked && !Object_deleted && m_pointer && m_pPointerTable){
				//remove yourself from previous table
				if (m_pPointerTable->size() != 0)
				m_pPointerTable->remove((IPointer*)this);
			}

			//now switch tables
			m_pointer = other.m_pointer; 
			m_pPointerTable = other.m_pPointerTable;
			Object_deleted = other.Object_deleted;
			linked = true;
			if (!Object_deleted && m_pPointerTable) m_pPointerTable->push_back((IPointer*)this);

			return *this;
		}


		void Link(T* pPointer, list<IPointer*>* pTable){
			m_pointer = dynamic_cast<T*>(pPointer);
			m_pPointerTable = pTable;
			Object_deleted = false;
			//Add this to table now.
			if (m_pPointerTable){
				m_pPointerTable->push_back((IPointer*)this);
			}
			linked = true;
		}
		template <class T2>
		void Relink(T2* pPointer){
			m_pointer = (T*)pPointer;
			linked = true;
		}

		size_t Get_Type(){
			return typeid(T).hash_code();
		}
	};

	template <typename to, typename from>
	Dptr<to> dcast(Dptr<from> pFrom){
		Dptr<to> pTo;
		pTo.Link((to*)pFrom.m_pointer, pFrom.m_pPointerTable);
		return pTo;
	}
}
#endif