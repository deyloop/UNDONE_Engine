/******************************************************************************
Project	:	UNDONE Engine
File	:	ObjectBuffer.cpp
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