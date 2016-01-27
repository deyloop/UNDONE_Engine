/******************************************************************************
Project	:	UNDONE Engine
File	:   unEngineInterfaces
Author	:	Anurup Dey

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
#pragma once

#ifndef _UN_ENGINE_INTERFACES
#define _UN_ENGINE_INTERFACES

#include "Dptr.h"
#include "InputContext.h"

namespace UNDONE_ENGINE {

    //all the types of components::
	#define _GEN_FORWARD_DEC_COMPS_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()
	#define _GEN_FORWARD_DEC_COMPS_INT_
	#include "GENERATE_FUNCTIONS.h"
	GENFUNCS()

	class Camera;

	typedef  unsigned int OwnerShip;

    /*------------------------------------------------------------------------
    The Input interface is ipmlemented by the input subsystem.
    ------------------------------------------------------------------------*/
    class unInput {
    public:
		virtual void HandleInput(InputEvent& p_given_event) = 0;
		virtual void AddContext(InputContext context) = 0;
		virtual void RemoveContext(const char* context_name )= 0;
		virtual void ActivateContext(const char* context_name )= 0;
		virtual void DeactivateContext(const char* context_name )= 0;

		virtual void RegisterCallback(const function<void( )> callback, const char* event_name )= 0;
		virtual void RegisterCallback(const function<void(float,float)> callback, const char* event_name, int unused )= 0;
    };

    /*------------------------------------------------------------------------
    The Graphics interface is implemented by the graphics subsystem
    ------------------------------------------------------------------------*/
    class unGraphics {
    public:

    };

    /*-------------------------------------------------------------------------
	THe Object buffer is the place where all the components of the game are
	physically stored. This Object buffer has the capabiltity to store any
	type of component you throw at it.
	-------------------------------------------------------------------------*/
	class unObjectBuffer{
	public:
		virtual void SetInitAllocSize(unsigned int size) = 0;
		virtual OwnerShip CreateOwnerShip() = 0;

		#define _GENFUNC_DEC_UNOBJECTBUFFER_H_
		#include "GENERATE_FUNCTIONS.h"
		GENFUNCS()
		
		virtual Dptr<unCamera> GetControlCamera() = 0;
        virtual void setControlCamera( Dptr<unCamera> camera ) = 0;
	};
}
#endif
