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
#include "DataFile.h"

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
	constexpr unsigned int str2int( const char* str, int h = 0 ) {
		return !str[h]?5381:(str2int(str,h+1)*33)^str[h];
	}

	Event_Type atoEvent_type( const char* str ) {
		switch(str2int(str)){
			case str2int("EVENT_KEYDOWN"):	return EVENT_KEYDOWN;
			case str2int("EVENT_KEYUP"):	return EVENT_KEYUP;
			case str2int("EVENT_QUIT"):		return EVENT_QUIT;
			case str2int("EVENT_KEYBOARD"): return EVENT_KEYBOARD;
			case str2int("EVENT_MOUSE") :	return EVENT_MOUSE;
			case str2int("EVENT_MOUSEMOVE"):return EVENT_MOUSEMOVE;
			case str2int("EVENT_KEYPRESS"): return EVENT_KEYPRESS;
		}
		//keep adding all here.
	}

	Key atoKeyCode(const char* str ) {
		
		switch(str2int(str)){
			case str2int("KEY_ARROW_UP")	:	return KEY_ARROW_UP;
			case str2int("KEY_ARROW_DOWN")	:	return KEY_ARROW_DOWN;
			case str2int("KEY_ARROW_LEFT")	:	return KEY_ARROW_LEFT;
			case str2int("KEY_ARROW_RIGHT")	:	return KEY_ARROW_RIGHT;
			case str2int("KEY_A")			:	return KEY_A;
			case str2int("KEY_W")			:	return KEY_W;
			case str2int("KEY_D")			:	return KEY_D;
			case str2int("KEY_S")			:	return KEY_S;
			case str2int("KEY_R")			:	return KEY_R;
			case str2int("KEY_E")			:	return KEY_E;
			case str2int("KEY_Q")			:	return KEY_Q;
			case str2int("KEY_Z")			:	return KEY_Z;
			case str2int("KEY_X")			:	return KEY_X;
			case str2int("KEY_NUM_8")		:	return KEY_NUM_8;
			case str2int("KEY_NUM_2")		:	return KEY_NUM_2;
			case str2int("KEY_NUM_4")		:	return KEY_NUM_4;
			case str2int("KEY_NUM_6")		:	return KEY_NUM_6;
			case str2int("KEY_NUM_7")		:	return KEY_NUM_7;
			case str2int("KEY_ESCAPE")		:	return KEY_ESCAPE;
		}
		//keep adding stuff
		return KEY_IRRELEVENT;
	}
	void InputHandeller::LoadContexts( const char * contextfile ) {
		DataFile context_file;
		context_file.parse(contextfile);
		for (auto& node : context_file.RootNode.subNodes) {
			if (node.name == "context") {
				InputContext context;
				context.m_name = node.GetAttribute("name");
				for (auto& event_node : node.subNodes) {
					if (event_node.name == "InputEvent") {
						InputEvent event;
						event.type = atoEvent_type(event_node.GetAttribute("type"));
						switch (event.type) {
							case EVENT_KEYBOARD:
							case EVENT_KEYUP:
							case EVENT_KEYDOWN:
							case EVENT_KEYPRESS: {
								event.key.keycode = atoKeyCode(event_node.GetAttribute("keycode"));
							}break;
						}//end of switch on event type.
						
						//after all that event neusence,
						InputPair pair(event,event_node.GetAttribute("name"));
						context.m_pairs.push_back(pair);
					}//if name is InputEvent
				}//end loop on events
				AddContext(context);
			}
		}
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