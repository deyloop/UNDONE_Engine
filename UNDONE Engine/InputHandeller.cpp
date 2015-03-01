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

		for (auto& context:m_Contexts) 
		{	//for each context,
			
			for (auto& pair:context.m_pairs)
			{	//...for each pair...
				
				if (p_given_event.event.type==pair.desired_event.event.type) 
				{
					
					switch (p_given_event.event.type) 
					{
						
						case EVENT_KEYDOWN:
							//check if keycode is relevent,
							if (pair.desired_event.key.keycode==KEY_IRRELEVENT) 
							{
								//just go forth with it
								pair.pCall_command->execute(context.m_pControl, p_given_event);
								
							} 
							else if (pair.desired_event.key.keycode==p_given_event.key.keycode) 
							{
								pair.pCall_command->execute(context.m_pControl, p_given_event);
							}
							break;
						case EVENT_KEYPRESS:
							//I am lazy.
							break;
						case EVENT_MOUSEMOVE:
							//just go forth with it
							pair.pCall_command->execute(context.m_pControl, p_given_event);
							break;
						case EVENT_MOUSEBUTTONDOWN: 
						case EVENT_MOUSEBUTTONUP:
							if (pair.desired_event.mouse_button.button==p_given_event.mouse_button.button)
							{
								pair.pCall_command->execute(context.m_pControl, p_given_event);
								
							}
							break;
						default:
							continue;	//get on with the next pair.
					} //end the switch.
					
				}//the if statement which checks if event types match
			}//next pair in loop
		}//next context.
		return;
	}





}