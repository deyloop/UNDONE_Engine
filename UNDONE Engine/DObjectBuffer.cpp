/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "DObjectBuffer.h"

namespace UNDONE_ENGINE {
	DObjectBuffer::DObjectBuffer( ) {
		m_empty = true;
	}
	/*-------------------------------------------------------------------------
	DEfault Destructor.
	-------------------------------------------------------------------------*/
	DObjectBuffer::~DObjectBuffer( ) {
		m_Components.clear( );
		m_storage_lists.clear( );
		m_storage_vectors.clear( );
		m_storage_types.clear( );
		m_empty = true;
	}

	/*----------------------------------------------------------------------------
	Returns a Components with the given name.
	Parameters:
	[IN]	name	-	the name of the required Component.
	Returns:
	THe required component if it exists, otherwise a DPOINTER with a nullptr
	----------------------------------------------------------------------------*/
	DPointer<Component> DObjectBuffer::GetComponentByName(const char* name) {
		for (DPointer<Component>& component : m_Components) {
			if (component.ptr( )->name==name) {
				return component;
			}
		}

		//If the program got untill here, that means there isn't a component 
		//present with that name, so we give out a fake one.
		DPointer<Component> ErrorComponent;
		ErrorComponent.m_pointer = nullptr;
		return ErrorComponent;
	}

}