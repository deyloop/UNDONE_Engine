/******************************************************************************
Project	:	UNDONE Engine
File	:	IGraphicsUser.h
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
	};
}
#endif