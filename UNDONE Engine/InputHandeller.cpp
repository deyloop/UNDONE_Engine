/******************************************************************************
File	:	InputHandeller.cpp
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "InputHandeller.h"

namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	Processes the Input, calls the corresponding callback functions. The wierdest
	looking function in all of the codebase...
	-----------------------------------------------------------------------------*/
	void InputHandeller::HandleInput(InputEvent& p_given_event) {
		if (m_Contexts.size( )==0) return;	//gotta do nothing 

		for (auto& context:m_Contexts) {
			for (auto& pair:context.m_pairs) {
				if (p_given_event.event.type==pair.desired_event.event.type) {
					switch (p_given_event.event.type) {
						case EVENT_KEYDOWN:
							//check if keycode is relevent,
							if (pair.desired_event.key.keycode!=KEY_IRRELEVENT) {
								//we check for keycode similarity,
								if (pair.desired_event.key.keycode==p_given_event.key.keycode) {
									pair.pCall_command->execute(context.m_pControl, p_given_event);
								}
							} else {
								//just go forth with it
								pair.pCall_command->execute(context.m_pControl, p_given_event);
							}
							break;
						case EVENT_KEYPRESS:
							//I am lazy.
							break;
					}
					
				}
			}
		}
	}
}