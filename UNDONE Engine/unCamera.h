/******************************************************************************
Project	:	UNDONE Engine
File	:   unCamera.h
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

#ifndef _UN_CAMERA_H_
#define _UN_CAMERA_H_

#include "unComponent.h"
#include <glm.hpp>
#include <gtx/transform.hpp>

namespace UNDONE_ENGINE {

	class unCamera : public virtual unComponent {
	public:
		virtual ~unCamera( ) {}

		virtual void CreateProjectionMatrix( float fov, float aspect, float nearPlane, float farPlane ) = 0;
		virtual void SetLookAt(float x, float y, float z) = 0;
		virtual void SetFOV( float fov ) = 0;
		virtual void SetAspectRatio( float aspect ) = 0;
		virtual void SetNearPlane( float plane ) = 0;
		virtual void SetFarPlane( float plane ) = 0;

		virtual glm::mat4* GetViewMatrix( ) = 0;
		virtual glm::mat4* GetProjectionMatrix( ) = 0;
		virtual glm::vec3* GetLookAt( ) = 0;
		virtual float GetFOV( ) = 0;
		virtual float GetAspectRatio( ) = 0;
		virtual float GetNearPlane( ) = 0;
		virtual float GetFarPlane( ) = 0;
	};

}

#endif