/******************************************************************************
Project	:	UNDONE Engine
File	:	IGraphicsUser.h
Author	:	Anurup Dey
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

		virtual void  OnCreateContext() = 0;
		virtual const int   GetScreenHieght() const = 0;
		virtual const int   GetScreenWidth() const = 0;
		virtual const float GetElapsedTime() const = 0;
	};
}
#endif