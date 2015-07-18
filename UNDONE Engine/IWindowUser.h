/******************************************************************************
Project	:	UNDONE Engine
File	:	IWindowUser.h
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

#ifndef IWINDOWUSER_H
#define IWINDOWUSER_H

namespace UNDONE_ENGINE {

	/*-------------------------------------------------------------------------
	The interface for the object to be using the Window class.
	-------------------------------------------------------------------------*/
	class IWindowUser {
	public:
		virtual void OnMinimized() = 0;
		virtual void OnResize(int newHieght,
							  int newWidth,
							  int oldHieght,
							  int oldWidth) = 0;
	};
}

#endif