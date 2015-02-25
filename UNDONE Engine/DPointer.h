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

/*-------------------------------------------------------------------------
A DPointer is simply a vrapper around a doible pointer. Provides a better
interface for dereferncing a double pointer (pointer to pointer).
-------------------------------------------------------------------------*/
	template <typename T>
	struct DPointer {
		T** m_pointer;
		T* ptr( ) { return *m_pointer; }
		T&  Obj( ) { return *(*m_pointer); }
	};
}
#endif