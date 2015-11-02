/******************************************************************************
Project	:	UNDONE Engine
File	:
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

#ifndef _UN_WORLDTRANSFORM_H_
#define _UN_WORLDTRANSFORM_H_
#include "unComponent.h"
#include <glm.hpp>
using namespace glm;

namespace UNDONE_ENGINE{
	class unWorldTransform : public virtual unComponent{
	public:
		virtual void Reset() = 0;
		virtual void TranslateAbs(float x, float y, float z)	= 0;
		virtual void TranslateRel(float x, float y, float z)	= 0;
		virtual void RotateAbs(float x, float y, float z)		= 0;
		virtual void RotateRel(float x, float y, float z)		= 0;
		virtual void ScaleAbs(float x, float y, float z)		= 0;
		virtual void ScaleRel(float x, float y, float z)		= 0;
		
		virtual mat4& GetTransform()							= 0;
		virtual vec3& GetPosition() 							= 0;
		virtual float GetXPosition()							= 0;
		virtual float GetYPosition()							= 0;
		virtual float GetZPosition()							= 0;
		virtual float GetXRotation()							= 0;
		virtual float GetYRotation()							= 0;
		virtual float GetZRotation()							= 0;
		virtual float GetXScale() 								= 0;
		virtual float GetYScale() 								= 0;
		virtual float GetZScale() 								= 0;
		virtual void SetXPosition(float x)						= 0;
		virtual void SetYPosition(float y)						= 0;
		virtual void SetZPosition(float z)						= 0;
		virtual void SetXRotation(float x) 						= 0;
		virtual void SetYRotation(float y) 						= 0;
		virtual void SetZRotation(float z) 						= 0;
		virtual void SetXScale(float x) 						= 0;
		virtual void SetYScale(float y) 						= 0;
		virtual void SetZScale(float z) 						= 0;
		virtual const vec3 GetUp( )                           =0;
		virtual const vec3 GetDown( )                         =0;
		virtual const vec3 GetLeft( )                         =0;
		virtual const vec3 GetRight( )                        =0;
		virtual const vec3 GetForward( )                      =0;
		virtual const vec3 GetBackWard( )                     =0;
        virtual void SetLookAt ( float, float, float )        = 0;
	};                                                        
}
#endif