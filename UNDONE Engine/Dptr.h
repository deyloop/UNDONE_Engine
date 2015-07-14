#pragma once

#ifndef _UNDONE_DPTR_H_
#define _INDONE_DPTR_H_

#include <list>
using std::list;

namespace UNDONE_ENGINE{

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
			Object_deleted = true;
			linked = false;
		}

		~Dptr(){
			//remove yourself from the table.
			if ((!Object_deleted) && m_pPointerTable)
				if (m_pPointerTable->size() != 0)
					m_pPointerTable->remove((IPointer*)this);
		}

		Dptr(Dptr<T> const & other){
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

		void Relink(T* pPointer){
			m_pointer = (T*)pPointer;
			linked = true;
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