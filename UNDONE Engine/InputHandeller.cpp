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
		if (m_ActiveContexts.size( )==0) return;	//gotta do nothing 

		for (auto& context:m_ActiveContexts) 
		{	//for each context,
			
			for (auto& pair:context.m_pairs)
			{	//...for each pair...
				
				if (p_given_event.event.type==pair.Desired_event.event.type) 
				{
					
					switch (p_given_event.event.type) 
					{
						
						case EVENT_KEYDOWN:
						case EVENT_KEYPRESS:{
							//check if keycode is relevent,
							if (pair.Desired_event.key.keycode==KEY_IRRELEVENT) 
							{
								//just go forth with it
								vector<CallBack>& callbacklist = m_callbacks[pair.event_name];
								for (auto& callback : callbacklist) {
									callback.callback();
								}
								
							} 
							else if (pair.Desired_event.key.keycode==p_given_event.key.keycode) 
							{
								vector<CallBack>& callbacklist = m_callbacks[pair.event_name];
								for (auto& callback : callbacklist) {
									callback.callback();
								}
							}
						}break;
						
						case EVENT_MOUSEMOVE:{
							//just go forth with it
							vector<CallBack>& callbacklist = m_callbacks[pair.event_name];
							for (auto& callback : callbacklist) {
							
								callback.fcallback(p_given_event.mouse_motion.delta_x,p_given_event.mouse_motion.delta_y);
							}
						}break;
						case EVENT_MOUSEBUTTONDOWN: 
						case EVENT_MOUSEBUTTONUP:{
							if (pair.Desired_event.mouse_button.button==p_given_event.mouse_button.button)
							{
								vector<CallBack>& callbacklist = m_callbacks[pair.event_name];
								for (auto& callback : callbacklist) {
									callback.callback();
								}
								
							}
						}break;
						default:
							continue;	//get on with the next pair.
					} //end the switch.
					
				}//the if statement which checks if event types match
			}//next pair in loop
		}//next context.
		return;
	}

	void InputHandeller::AddContext( InputContext context ) {
		m_Contexts.push_back(context);
	}

	void InputHandeller::RemoveContext( const char * context_name ) {
		const int num_contexts = m_Contexts.size();
		//check if the context is active, by mistake
		int i = 0;
		for (auto& context : m_ActiveContexts) {
			if (context.m_name == context_name) {
				m_ActiveContexts[i] = m_ActiveContexts.back();
				m_ActiveContexts.pop_back();
				return;
			}
			++i;
		}

		//Remove from the main list.
		for (i = 0; i < num_contexts; ++i) {
			if(m_Contexts[i].m_name == context_name){
				m_Contexts[i] = m_Contexts.back();
				m_Contexts.pop_back();
				return;
			}
		}
	}

	void InputHandeller::ActivateContext( const char * context_name ) {
		const int num_contexts = m_Contexts.size();

		for (int i = 0; i < num_contexts; ++i) {
			if(m_Contexts[i].m_name == context_name){
				//Add it to active list.
				m_ActiveContexts.push_back(m_Contexts[i]);
				//remove from main list;
				m_Contexts[i] = m_Contexts.back();
				m_Contexts.pop_back();
				return;
			}
		}
	}

	void InputHandeller::DeactivateContext( const char * context_name ) {
		const int num_contexts = m_ActiveContexts.size();

		for (int i = 0; i < num_contexts; ++i) {
			if(m_ActiveContexts[i].m_name == context_name){
				//Add it to main list.
				m_Contexts.push_back(m_ActiveContexts[i]);
				//remove from active list;
				m_ActiveContexts[i] = m_ActiveContexts.back();
				m_ActiveContexts.pop_back();
				return;
			}
		}
	}

	void InputHandeller::RegisterCallback( const function<void( )> callback, const char * event_name ) {
		CallBack newcallback;
		newcallback.callback = callback;
		m_callbacks[event_name].push_back(newcallback);
	}

	void InputHandeller::RegisterCallback( const function<void(float,float)> callback, const char * event_name , int unused) {
		CallBack newcallback;
		newcallback.fcallback = callback;
		m_callbacks[event_name].push_back(newcallback);
	}




}