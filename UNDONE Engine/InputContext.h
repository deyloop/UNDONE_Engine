/******************************************************************************
File	:	InputContext.h
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

#ifndef _UNDONE_INPUT_CONTEXT
#define _UNDONE_INPUT_CONTEXT

#include <vector>
#include "InputEvent.h"
#include "UNDONE_Engine_declr.h"
using std::vector;

namespace UNDONE_ENGINE {
	
	class UNDONE_API InputControl {
	public:
		virtual ~InputControl( ) { };
	};

	class UNDONE_API  Command {
	public:
		virtual ~Command( ) { };
		virtual void execute(InputControl* control, InputEvent& given_event) = 0;
	};

	struct UNDONE_API InputPair {
		InputPair(InputEvent des_event, Command& pcommand)
			:desired_event(des_event), pCall_command(&pcommand) { };

		InputEvent	desired_event;
		Command*	pCall_command;
	};
	
	/*-----------------------------------------------------------------------------
	Contexts store the data needed to execute input handelling.
	-----------------------------------------------------------------------------*/
	struct InputContext {
		InputControl*		m_pControl;
		vector<InputPair>	m_pairs;
	};
}
#endif