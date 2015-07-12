/******************************************************************************
Project	:	UNDONE Engine
File	:	Component.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Component.h"
#include <iostream>
#include "UNDONE_DEBUG.h"
#include "GameObject.h"
using namespace std;

namespace UNDONE_ENGINE {
	int Component::num_Components = 0;
	/*-----------------------------------------------------------------------------
	Default Constructor
	-----------------------------------------------------------------------------*/
	Component::Component( ) {
		char str[20];
		m_number = num_Components;
		sprintf_s(str, "Component_%i", num_Components);
		name = str;
		++num_Components;
		
		m_num_priority[0] = 0;

		coutput("New Component Constructed with name "+name+"\n");

	}

	/*-----------------------------------------------------------------------------
	Default Destructor. Cleans up resoureces.
	-----------------------------------------------------------------------------*/
	void Component::Release( ) {
		m_ppParent.m_pointer = nullptr;
		coutput("Component "+name+" Released.\n");
	}

	unsigned Component::GetPriority(unsigned priority_level) {

		if (priority_level>=NUM_MAX_PRIORITIES || priority_level == -1) {
			return -1;
		} else {
			return m_num_priority[priority_level];
		}
	}

	void Component::SetPriority(unsigned priority, unsigned priority_level) {
		
		if (priority_level>=NUM_MAX_PRIORITIES) {
			return;
		} else {
			m_num_priority[priority_level] = priority;
			coutput("'s primary priority set to "+(int)m_num_priority[0]+"\n");
		}
	}

	/*-----------------------------------------------------------------------------
	Sets the Parent of the Component.
	Parameters:
	[IN] parent	:	pointer to a GameObject acting as the parent of this Component.
	-----------------------------------------------------------------------------*/
	void Component::SetParent(Dptr<GameObject> ppParent) {
		if ((ppParent.ptr())!=nullptr) {
			m_ppParent = ppParent;
			//Increase primary priority to one more than parent's
			SetPriority(m_ppParent->GetPriority(0)+1,0);

			coutput(name+" made child of "+m_ppParent->name+"\n");
			
			
			//see if parent has parent
			if ((ppParent->GetParent( )).m_pointer) { 
				OnParentBeingChilded( );
			}
			
			OnParentSet( );
		}
	}

	/*-------------------------------------------------------------------------
	Renames the Component.
	Parameters:
	[IN] newname	:	string containig the new name.
	-------------------------------------------------------------------------*/
	void Component::Rename(const char* newname) {
		coutput(name+" is renamed to "+string(newname)+"\n");
		name = newname;
	}
}