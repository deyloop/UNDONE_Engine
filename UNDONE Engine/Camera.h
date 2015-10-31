/******************************************************************************
File	:	Camera.h
Author	:	Anurup.Dey

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

#ifndef _CAMERA_H_
#define _CAMERA_H_

//Includes
//#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtx/transform.hpp>
#include "InputContext.h"
#include "UNDONE_Engine_declr.h"
#include "Component.h"
#include "unCamera.h"
#include <iostream>

namespace UNDONE_ENGINE {

	class WorldTransform;


	/*-----------------------------------------------------------------------------
	THis class object structure represents the camera object, which is used to get
	the view of the world. This class controls and encapsulates the view and
	projection transforms of the objects when rendered to the screen.
	-----------------------------------------------------------------------------*/
	class Camera :public unCamera, public Component {
	public:
		Camera( );

		void Load( ) {};
		void Unload( ) {};

		void OnParentAdopted( ) {};
		
		void CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane);
		
		void Update( );

		void SetLookAt(float x, float y, float z);
		void SetFOV(float fov) { CreateProjectionMatrix(fov, m_aspect, m_nearPlane, m_farPlane); }
		void SetAspectRatio(float aspect) { CreateProjectionMatrix(m_fov, aspect, m_nearPlane, m_farPlane); }
		void SetNearPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, plane, m_farPlane); }
		void SetFarPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, m_nearPlane, plane); }

        glm::mat4* GetViewMatrix( ) { return &m_view; }
        glm::mat4* GetProjectionMatrix( ) { return &m_projection; }
		glm::vec3* GetLookAt( ) { return &m_lookAt; }
		float GetFOV( ) { return m_fov; }
		float GetAspectRatio( ) { return m_aspect; }
		float GetNearPlane( ) { return m_nearPlane; }
		float GetFarPlane( ) { return m_farPlane; }

	private:

		void OnParentSet( );
		Dptr<WorldTransform> m_pTransform;

		glm::mat4   m_view;
		glm::mat4	m_projection;
	
		glm::vec3	m_look;
		glm::vec3	m_lookAt;
	
		float       m_fov;
		float       m_aspect;
		float       m_nearPlane;
		float       m_farPlane;
	};
};
#endif

///////////////////////////////////////////////////////////////////////////////