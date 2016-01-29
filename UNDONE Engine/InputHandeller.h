/******************************************************************************
File	:	InputHandeller.h
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

#ifndef _UNDONE_INPUTHANDELLER_H_
#define _UNDONE_INPUTHANDELLER_H_

//some includes.
#include <vector>
#include <map>
#include <string>
#include "InputContext.h"
#include "unEngineInterfaces.h"
using std::vector;
using std::map;
using std::string;

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	This class of objects are responsible for the handelling of input  from
	system sources. its is designed so that it works on a 'context' driven Input
	handelling. It checks the input and compaires with a contex list, and calls
	the corresponding callback functions for that inputEvent.
	-----------------------------------------------------------------------------*/
	class InputHandeller: public unInput {
	public:
		InputHandeller( ) { };
		~InputHandeller( ) { };

		void HandleInput(InputEvent& p_given_event);
		void AddContext(InputContext context);
		void LoadContexts(const char* contextfile );
		void RemoveContext(const char* context_name );
		void ActivateContext(const char* context_name );
		void DeactivateContext(const char* context_name );

		void RegisterCallback(const function<void( )> callback, const char* event_name );
		void RegisterCallback(const function<void(float,float)> callback, const char* event_name, int unused  );

	private:
		vector<InputContext>			m_Contexts;
		vector<InputContext>			m_ActiveContexts;
		map<string,vector<CallBack>>	m_callbacks;
	};
}
#endif