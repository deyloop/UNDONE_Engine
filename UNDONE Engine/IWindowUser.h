/******************************************************************************
Project	:	UNDONE Engine
File	:	IWindowUser.h
Author	:	Anurup Dey

Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>

This file is part of UNDONE-Engine.

UNDONE-Engine can not be copied and/or distributed without the express
permission of Anurup Dey. Unauthorized copying of this file, via any
medium is strictly prohibited.

Proprietary and confidential.

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