/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Undone_Engine.h"
#include "DObjectBuffer.h"
#include "SystemComponent.h"
#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {
	DObjectBuffer::DObjectBuffer( ) {
		m_empty = true;
		m_init_vec_size = 100;
		m_num_owners = 0;//
	}
	/*-------------------------------------------------------------------------
	DEfault Destructor.
	-------------------------------------------------------------------------*/
	DObjectBuffer::~DObjectBuffer( ) {
		if (m_storage_vectors.size( )!=0) {
			SystemComponent::GetInstance( )->ShowMessage("Some types of objects were not released",
														 "MEMORY LEAK WARNING!");
		}
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
	DPointer<Component> DObjectBuffer::GetComponentByName(const char* name,OwnerShip ownership) {
		for (DPointer<Component>& component : m_Components) {
			if (component->name==name) {
				return component;
			}
		}

		//If the program got untill here, that means there isn't a component 
		//present with that name, so we give out a fake one.
		DPointer<Component> ErrorComponent;
		ErrorComponent.m_pointer = nullptr;
		return ErrorComponent;
	}

#define GENERATE_FUNCTION_DEFINITIONS(x)\
	void DObjectBuffer::DeleteAll_ ## x (OwnerShip ownership){\
		DeleteAll<x>(ownership);\
	}\
	DPointer<x> DObjectBuffer::CreateNew_ ## x (OwnerShip ownership){\
		return CreateNew<x>(ownership);\
	}\
	DPointer<x> DObjectBuffer::Get_ ## x ## _ByName (const char* name, OwnerShip ownership){\
		return GetComponentByNameOfType<x>(name, ownership);\
	}

	GENERATE_FUNCTION_DEFINITIONS(GameObject);
	GENERATE_FUNCTION_DEFINITIONS(WorldTransform);
	GENERATE_FUNCTION_DEFINITIONS(Mesh);
	GENERATE_FUNCTION_DEFINITIONS(GraphicMaterial);
	GENERATE_FUNCTION_DEFINITIONS(_3DGraphic);
	GENERATE_FUNCTION_DEFINITIONS(_2DGraphic);
	GENERATE_FUNCTION_DEFINITIONS(Texture);
	GENERATE_FUNCTION_DEFINITIONS(Shader);
	GENERATE_FUNCTION_DEFINITIONS(ShaderProgram);
}