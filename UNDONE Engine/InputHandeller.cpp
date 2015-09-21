/******************************************************************************
File	:	InputHandeller.cpp

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
						case EVENT_KEYPRESS:
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