/******************************************************************************
Project	:	UNDONE Engine
File	:	IWindowUser.h
Author	:	Anurup Dey
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