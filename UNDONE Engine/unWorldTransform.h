/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UN_WORLDTRANSFORM_H_
#define _UN_WORLDTRANSFORM_H_
#include "unComponent.h"
#include <glm.hpp>
using namespace glm;

namespace UNDONE_ENGINE{
	class unWorldTransform{
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
	};
}
#endif