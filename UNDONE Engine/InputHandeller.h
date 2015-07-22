/******************************************************************************
File	:	InputHandeller.h
Author	:	Anurup Dey

Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>

This file is part of UNDONE-Engine.

UNDONE-Engine can not be copied and/or distributed without the express
permission of Anurup Dey. Unauthorized copying of this file, via any
medium is strictly prohibited.

Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNDONE_INPUTHANDELLER_H_
#define _UNDONE_INPUTHANDELLER_H_

//some includes.
#include <vector>	
#include "InputContext.h"
using std::vector;

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	This class of objects are responsible for the handelling of input  from
	system sources. its is designed so that it works on a 'context' driven Input
	handelling. It checks the input and compaires with a contex list, and calls
	the corresponding callback functions for that inputEvent.
	-----------------------------------------------------------------------------*/
	class InputHandeller {
	public:
		InputHandeller( ) { };
		~InputHandeller( ) { };

		vector<InputContext>& GetContextListForEditing( ) { return m_Contexts; }
		void HandleInput(InputEvent& p_given_event);

	private:
		vector<InputContext> m_Contexts;
	};
}
#endif