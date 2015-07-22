/******************************************************************************
Project	:	UNDONE Engine
File	:	ObjectBuffer.cpp
Author	:	Anurup Dey

		Copyright (C) 2015 Anurup Dey 
		<anu.rup.dey98@gmail.com>

	This file is part of UNDONE-Engine.

	UNDONE-Engine can not be copied and/or distributed without the express
	permission of Anurup Dey. Unauthorized copying of this file, via any
	medium is strictly prohibited.

	Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Undone_Engine.h"
#include "ObjectBuffer.h"
#include "SystemComponent.h"
#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {
	ObjectBuffer::ObjectBuffer( ) {
		m_empty = true;
		m_init_vec_size = 0;
		m_num_owners = 0;
	}
	/*-------------------------------------------------------------------------
	DEfault Destructor.
	-------------------------------------------------------------------------*/
	ObjectBuffer::~ObjectBuffer( ) {
		if (m_storage_vectors.size( )!=0) {
			SystemComponent::GetInstance( )->ShowMessage("Some types of objects were not released",
														 "MEMORY LEAK WARNING!");
		}
		m_Components.clear( );
		m_pointer_table_lists.clear( );
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
	Dptr<Component> ObjectBuffer::GetComponentByName(const char* name,OwnerShip ownership) {
		for (Dptr<Component>& component : m_Components) {
			if (component->name==name) {
				return component;
			}
		}

		//If the program got untill here, that means there isn't a component 
		//present with that name, so we give out a fake one.
		Dptr<Component> ErrorComponent;
		ErrorComponent.m_pointer = nullptr;
		return ErrorComponent;
	}

	#define _GENFUNC_DEF_DOBJECTBUFFER_CPP_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()
}