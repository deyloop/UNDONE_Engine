#pragma once

#ifndef _UNDONE_DPTR_H_
#define _INDONE_DPTR_H_

#include <list>
using std::list;

namespace UNDONE_ENGINE{
	class ObjectBuffer;

	class IPointer{
	public:
		bool Object_deleted;
		//virtual void Link(void* pPointer, list<IPointer*>* pTable) = 0;
		//virtual void Relink(void* pPointer) = 0;
	};

	template <typename T>
	class Dptr : public IPointer{
		bool linked;
	public:
		T*	m_pointer;
		list<IPointer*>* m_pPointerTable;

		Dptr(){
			m_pointer = nullptr;
			m_pPointerTable = nullptr;
			Object_deleted = false;
		}

		~Dptr(){
			//remove yourself from the table.
			if ((!Object_deleted) && m_pPointerTable) m_pPointerTable->remove(this);
		}

		/*Dptr(Dptr<T>& other){
			*this = other;
		}*/

		T* operator -> ()	{ return m_pointer; }
		T& operator * ()	{ return *m_pointer; }
		T* ptr()			{ return m_pointer; }
		T& Obj()			{ return *m_pointer; }
		
		Dptr<T>& operator = (Dptr<T>& other){
			if (!Object_deleted && m_pointer && m_pPointerTable){
				//remove yourself from previous table
				m_pPointerTable->remove(this);
			}

			//now switch tables
			m_pointer = other.m_pointer;
			m_pPointerTable = other.m_pPointerTable;
			if(m_pPointerTable) m_pPointerTable->push_back(this);

			return *this;
		}


		void Link(T* pPointer, list<IPointer*>* pTable){
			m_pointer = dynamic_cast<T*>(pPointer);
			m_pPointerTable = pTable;

			//Add this to table now.
			if (m_pPointerTable){
				m_pPointerTable->push_back(this);
			}
		}

		void Relink(T* pPointer){
			m_pointer = (T*)pPointer;
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