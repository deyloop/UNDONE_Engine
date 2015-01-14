/******************************************************************************
File			:	InputEvent.h
Author			:	Anurup Dey.
Date created	:	28.09.2014
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _INPUTEVENT_H_
#define _INPUTEVENT_H_

//Types of events.
typedef enum {
	EVENT_FIRSTEVENT = 0,

	EVENT_QUIT		 = 0x100,	//App wants to quit.

	//Keyboard Events
	EVENT_KEYBOARD,
	EVENT_KEYDOWN	 = 0x200,	//Keyboard button pressed down
	EVENT_KEYUP,				//Keyboard button released
	EVENT_KEYPRESS,				//Keyboard button still pressed

	//Mouse Events
	EVENT_MOUSE,
	EVENT_MOUSEMOVE  = 0x300,	//Mouse moved position.
	EVENT_MOUSEBUTTONDOWN,		//mouse button was pressed
	EVENT_MOUSEBUTTONUP,		//mouse button was released.
	EVENT_MOUSEWHEEL,			//mouse wheel was rotated.

} Event_Type;
	
//Keycodes for key board events.
typedef enum Key{
	KEY_ESCAPE = 0,
	//function keys
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	//Arrow Keys
	KEY_ARROW_UP,
	KEY_ARROW_DOWN,
	KEY_ARROW_LEFT,
	KEY_ARROW_RIGHT,
	//...
	KEY_IRRELEVENT
} key_code;

//Data common to all events
typedef struct CommonEventData{
	Event_Type type;
} CommonEvent;

//Data regarding Keybourd events
typedef struct KeyBoardEvent{
	Event_Type  type;
	Key			keycode;
} KeyBoardEvent;

//Data of mouse movement
typedef struct MouseMotionEvent{
	Event_Type type;

} MouseMotionEvent;

//Data of mouse button event.
struct MouseButtonEvent{
	Event_Type type;
	//...
};

//Data of mouse wheel movement.
struct MouseWheelEvent{
	Event_Type type;
};

//the input data structure.
struct InputEvent {
	CommonEvent			event;
	KeyBoardEvent		key;
	MouseMotionEvent	mouse_motion;
	MouseButtonEvent	mouse_button;
	MouseWheelEvent		mouse_wheel;
};

#endif