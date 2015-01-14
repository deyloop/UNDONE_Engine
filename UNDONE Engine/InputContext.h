/******************************************************************************
File	:	InputContext.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNDONE_INPUT_CONTEXT
#define _UNDONE_INPUT_CONTEXT

#include <vector>
#include "InputEvent.h"
using std::vector;

namespace UNDONE_ENGINE {
	
	class InputControl {
	public:
		virtual ~InputControl( ) { };
	};

	class Command {
	public:
		virtual ~Command( ) { };
		virtual void execute(InputControl* control, InputEvent& given_event) = 0;
	};

	struct InputPair {
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