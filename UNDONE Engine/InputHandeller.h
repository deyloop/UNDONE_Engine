/******************************************************************************
File	:	InputHandeller.h
Author	:	Anurup Dey
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