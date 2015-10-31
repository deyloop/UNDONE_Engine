/******************************************************************************
File	:	Camera.cpp
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
#include "Camera.h"
#include "WorldTransform.h"
#include "GameObject.h"

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	Default constructor.
	-----------------------------------------------------------------------------*/
	Camera::Camera( ) {
		m_pTransform.m_pointer = nullptr;

		m_look	= glm::vec3(0.0f, 0.0f, -1.0f);
		m_view  = glm::mat4( 1.0f );
		
		SetLookAt(0,0,0);
		CreateProjectionMatrix(90.0f, 1.0f, 0.25f, 100.0f);
		Update( );
	}

	/*-----------------------------------------------------------------------------
	Creates the Projection Matrix.
	Parameters:
	[IN]	fov	-	Field of view
	[in] aspect - Aspect ratio
	[in] near - Near plane
	[in] far - Far plane
	-----------------------------------------------------------------------------*/
	void Camera::CreateProjectionMatrix(float fov, float aspect,
										float nearPlane, float farPlane) {
		m_fov		= fov;
		m_aspect	= aspect;
		m_nearPlane = nearPlane;
		m_farPlane	= farPlane;

		m_projection = glm::perspective(m_fov, m_aspect, m_nearPlane, m_farPlane);
	}

	void Camera::OnParentSet( ) {
		m_pTransform = dcast<WorldTransform,unWorldTransform>(m_ppParent->GetWorldTransform( ));
	}

	/*-----------------------------------------------------------------------------
	Updates the camera and creates the new view matrix. Must be called ever time
	Properties of the csamera are changed. do not call each frame, only where changes
	are aplied.
	-----------------------------------------------------------------------------*/
	void Camera::Update( ) {
		if (m_pTransform.m_pointer == nullptr) return;

		vec3& position = m_pTransform->GetPosition( );
		m_look         = m_pTransform->GetForward( );
		m_lookAt       = position + m_look;

		//Calculate the new matrix
		m_view = glm::lookAt( position, m_lookAt, glm::vec3( 0.0f, 1.f, 0.0f ));
	}

	/*-----------------------------------------------------------------------------
	Sets camera look at position - the point at wich the camera is looking at.
	Parameters:
	[in] x, y, z of new target.
	-----------------------------------------------------------------------------*/
	void Camera::SetLookAt(float x, float y, float z) {
		if (m_pTransform.m_pointer == nullptr) return;

		m_lookAt = vec3( x, y, z );
		
		vec3& position = m_pTransform->GetPosition( );
		m_look = glm::normalize( m_lookAt - position);
	}

}