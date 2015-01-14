/******************************************************************************
File	:	InputHandeller.cpp
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "InputHandeller.h"

/*-----------------------------------------------------------------------------
Processes the Input, calls the corresponding callback functions.
-----------------------------------------------------------------------------*/
void InputHandeller::HandleInput(InputEvent& p_given_event) {
	if (m_Contexts.size( )==0) return;	//gotta do nothing 

	for (auto& context:m_Contexts) {
		for (auto& pair:context.m_pairs) {
			if (p_given_event.event.type==pair.desired_event.event.type) {
				switch (p_given_event.event.type) {
				//WAIT... LET ME THINK...	
				}
				pair.pCall_command->execute(context.m_pControl, p_given_event);
			}
		}
	}
}