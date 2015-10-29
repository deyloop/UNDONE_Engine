/******************************************************************************
Project	:	UNDONE Engine
File	:	IGraphicsUser.h
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

#ifndef _IGRAPHICSUSER_H
#define _IGRAPHICSUSER_H
namespace UNDONE_ENGINE {
	/*-------------------------------------------------------------------------
	Summary:	This Interface has to be implimented by the using framework to 
	be able to use the GraphicEngine Class. This Interface contains some
	events which the Engine can trigger in accordance to the creation
	and activities of the Graphic Card.
	-------------------------------------------------------------------------*/
	class IGraphicsUser					//NOTE: this is an Abstract class.
	{
	public:

		virtual const int   GetScreenHieght() const = 0;
		virtual const int   GetScreenWidth() const = 0;
		virtual const float GetElapsedTime() const = 0;
        virtual const float GetFPS( ) const = 0;
	};
}
#endif