/******************************************************************************
Project	:	UNDONE Engine
File	:	GENERATE_FUNCTIONS.h
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
/*-----------------------------------------------------------------------------
This Header file contains macros which when the file is included with a 
preceding definition specifying the group of functions, automatically generates 
the functions involving Components of all types. Please Add the definition for
any new components you add later to this file so that the functons corresponding 
to that component can be generated automatically.
-------------------------------------------------------------------------------*/

#include "Dptr.h"

#ifdef GENERATE_FUNCTIONS
#undef GENERATE_FUNCTIONS
#endif

//For ObJectBuffer
#ifdef _GENFUNC_DEC_UNOBJECTBUFFER_H_
	#define  GENERATE_FUNCTIONS(type)																		\
		virtual void DeleteAll_ ## type (UNDONE_ENGINE::OwnerShip ownership = 0) = 0;										\
		virtual UNDONE_ENGINE::Dptr<un##type> CreateNew_ ## type (UNDONE_ENGINE::OwnerShip ownership = 0) = 0;							\
		virtual void Delete_##type(UNDONE_ENGINE::Dptr<un##type>,UNDONE_ENGINE::OwnerShip ownership = 0) = 0;\
		virtual UNDONE_ENGINE::Dptr<un##type> Get_ ## type ## _ByName (const char* name, UNDONE_ENGINE::OwnerShip ownership = 0) = 0; 
	#undef _GENFUNC_DEC_UNOBJECTBUFFER_H_
#elif defined _GENFUNC_DEC_DOBJECTBUFFER_H_
	#define GENERATE_FUNCTIONS(type)																		\
		void DeleteAll_ ## type (UNDONE_ENGINE::OwnerShip ownership = 0);													\
		UNDONE_ENGINE::Dptr<un##type> CreateNew_ ## type (UNDONE_ENGINE::OwnerShip ownership = 0);										\
		void Delete_##type(UNDONE_ENGINE::Dptr<un##type>,UNDONE_ENGINE::OwnerShip ownership = 0) ;\
		UNDONE_ENGINE::Dptr<un##type> Get_ ## type ## _ByName (const char* name, UNDONE_ENGINE::OwnerShip ownership = 0);
	#undef _GENFUNC_DEC_DOBJECTBUFFER_H_
#elif defined _GENFUNC_DEF_DOBJECTBUFFER_CPP_
	#define GENERATE_FUNCTIONS(type)\
	void ObjectBuffer::Delete_ ## type(UNDONE_ENGINE::Dptr<un##type> ptr,UNDONE_ENGINE::OwnerShip ownership){ \
		Delete<type>(dcast<type,un##type>(ptr),ownership);\
	}\
	void ObjectBuffer::DeleteAll_ ## type (UNDONE_ENGINE::OwnerShip ownership){											\
		DeleteAll<type>(ownership);																			\
	}																									\
	UNDONE_ENGINE::Dptr<un##type> ObjectBuffer::CreateNew_ ## type (UNDONE_ENGINE::OwnerShip ownership){									\
		return dcast<un##type,type>(CreateNew<type>(ownership));\
																		\
	}																									\
	UNDONE_ENGINE::Dptr<un##type> ObjectBuffer::Get_ ## type ## _ByName (const char* name, UNDONE_ENGINE::OwnerShip ownership){			\
		return dcast<un##type,type>(GetComponentByNameOfType<type>(name, ownership));												\
	}
	#undef _GENFUNC_DEF_DOBJECTBUFFER_CPP_

//for Dptr
#elif defined _GENFUNC_DEC_DPOINTER_H_
	#define GENERATE_FUNCTIONS(type)\
	template struct Dptr<type>;\
	template struct Dptr < un##type > ;
	#undef _GENFUNC_DEC_DPOINTER_H_

//General use
#elif defined _GEN_FORWARD_DEC_COMPS_
	#define GENERATE_FUNCTIONS(type)\
		class type;
	#undef _GEN_FORWARD_DEC_COMPS_
#elif defined _GEN_FORWARD_DEC_COMPS_INT_
	#define GENERATE_FUNCTIONS(type)\
		class un##type;
	#undef _GEN_FORWARD_DEC_COMPS_INT_

//For GameObject
#elif defined _GENFUNC_DEC_UNGAMEOBJECT_H_
	#define GENERATE_FUNCTIONS(type)\
		virtual Dptr<un##type> Get ## type() = 0;\
		virtual void Add ## type (Dptr<un ## type> rComponent) = 0;\
		virtual void Remove ## type () = 0;\
		virtual void Remove ## type ## byName(const char* name) = 0;
	#undef _GENFUNC_DEC_UNGAMEOBJECT_H_
#elif defined _GENFUNC_DEC_GAMEOBJECT_H_
	#define GENERATE_FUNCTIONS(type)\
		UNDONE_ENGINE::Dptr<un##type> Get ## type();\
		void Add ## type (UNDONE_ENGINE::Dptr<un ## type> rComponent);\
		void Remove ## type();\
		void Remove ## type ## byName(const char* name);
	#undef _GENFUNC_DEC_GAMEOBJECT_H_
#elif defined _GENFUNC_DEF_GAMEOBJECT_CPP_
#define GENERATE_FUNCTIONS(type)\
		Dptr<un ## type> GameObject::Get ## type(){\
			return dcast<un ## type,type>(GetComponent<type>());\
		}\
		void GameObject::Add ## type (Dptr<un ## type> rComponent){\
			 AddComponent<type>(dcast<type,un ## type>(rComponent));\
		}\
		void GameObject::Remove ## type (){\
			RemoveComponent<type>();\
		}\
		void GameObject::Remove ## type ## byName(const char* name){\
			RemoveComponentByName(name);\
		}
		#undef _GENFUNC_DEF_GAMEOBJECT_CPP_
#elif defined _GENDEC_DEF_BEHAVIOR_CPP_
#define GENERATE_FUNCTIONS(type)\
       Dptr<un ## type > m_## type;
       #undef _GENDEC_DEF_BEHAVIOR_CPP_
#elif defined _GEN_DEF_BEHAVIOR_ATT_CPP_
#define GENERATE_FUNCTIONS(type)\
       behavior_script->m_##type = m_ppParent->Get##type();
       #undef _GEN_DEF_BEHAVIOR_ATT_CPP_

#endif

	/*--------------------------------------------------------------------------
	Please insert a Macro call to GENERATE_FUNCTIONS for each new Component
	you create under here.
	-------------------------------------------------------------------------*/
#define GEN_FUNCTIONS_ONLY_COMPS_NO_GAMEOBJECT()\
    GENERATE_FUNCTIONS(WorldTransform)\
	GENERATE_FUNCTIONS(Mesh)\
	GENERATE_FUNCTIONS(GraphicMaterial)\
	GENERATE_FUNCTIONS(Graphic3D)\
	GENERATE_FUNCTIONS(Graphic2D)\
	GENERATE_FUNCTIONS(BehaviorAttachement)\
	GENERATE_FUNCTIONS(Camera)\

#define GENFUNCS_ONLY_FOR_COMPONENTS()\
	GENERATE_FUNCTIONS(GameObject)\
    GEN_FUNCTIONS_ONLY_COMPS_NO_GAMEOBJECT()\
	

#define GENFUNCS()\
	GENFUNCS_ONLY_FOR_COMPONENTS() \
	GENERATE_FUNCTIONS(Texture)\
	GENERATE_FUNCTIONS(Shader)\
	GENERATE_FUNCTIONS(ShaderProgram)\







