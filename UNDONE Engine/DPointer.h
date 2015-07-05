/******************************************************************************
Project	:	UNDONE Engine
File	:	DPointer.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNDONE_DPOINTER_H
#define _UNDONE_DPOINTER_H

namespace UNDONE_ENGINE {

	#define _GEN_FORWARD_DEC_COMPS_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()
	#define _GEN_FORWARD_DEC_COMPS_INT_ 
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()

/*-------------------------------------------------------------------------
A DPointer is simply a vrapper around a doible pointer. Provides a better
interface for dereferncing a double pointer (pointer to pointer).
-------------------------------------------------------------------------*/
	template <typename T>
	struct DPointer {
		T** m_pointer;
		T* ptr( ) { return *m_pointer; }
		T&  Obj( ) { return *(*m_pointer); }
		T* operator ->() {
			return (*m_pointer);
		}
	};

	#define _GENFUNC_DEC_DPOINTER_H_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()


	template <typename to, typename from>
	DPointer<to> dcast(DPointer<from> dp ) {
		DPointer<to> t;
		t.m_pointer = reinterpret_cast<to**>(dp.m_pointer);
		return t;
	}
}
#endif