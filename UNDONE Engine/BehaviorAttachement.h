/******************************************************************************
Project	:	UNDONE Engine
File	:	BehaviorAttachement.h
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
#pragma once

#ifndef UNDONE_BEHAVIORATTACHEMENT_H
#define UNDONE_BEHAVIORATTACHEMENT_H

#include "Component.h"
#include "unBehaviorAttachement.h"

#include <vector>
using std::vector;

namespace UNDONE_ENGINE {
	
	class Behavior;
	class UnFramework;

	/*-------------------------------------------------------------------------
	THe BehaviorAttachement component acts as a glue which will attach a 
	behavior script to the GameObject. Multiple scripts can be attached per
	GameObject using Attachement one point.
	-------------------------------------------------------------------------*/
	class BehaviorAttachement : public unBehaviorAttachement , public Component {
	public:
		void Load( );
		void Unload( );

		void OnParentAdopted( ) {};

		void AddBehavior(const char* script_name, Behavior* behavior_script );
		static void setFramework( UnFramework* pFramework );
	protected:
		void OnParentSet( );

	private:
		vector<Behavior*>     m_BehaviorList;
		vector<const char*>   m_Names;
	};
}

#endif
