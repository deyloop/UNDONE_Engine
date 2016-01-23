/******************************************************************************
File:		WorldTransform.cpp
Author:		Anurup Dey

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
#include "Worldtransform.h"
#include "GameObject.h"
#include <gtc\matrix_transform.hpp>

namespace UNDONE_ENGINE {
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Default Constructor
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	WorldTransform::WorldTransform( ) {
		m_sync_num		= 0;
		m_par_sync_num	= 0;
		m_parented		= false;
		Reset( );
	}

	void WorldTransform::OnParentSet( ) {
		
	}

	void WorldTransform::OnParentAdopted( ) {
		m_ppParentTransform = m_ppParent->GetParent( )->GetComponent<WorldTransform>();
		m_parented = true;
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Reset the matrices to default position.
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	void WorldTransform::Reset( ) {
		m_localTransform = m_translation = m_worldTransform =  
		m_rotation = m_scale = m_parentTransform = glm::mat4(1.0f);

		m_position = glm::vec3(0.0f, 0.0f, 0.0f);

		m_rotationX = m_rotationY = m_rotationZ = 0.0f;
		m_scaleX = m_scaleY = m_scaleZ = 1.0f;
		m_transX = m_transY = m_transZ = 0.0f;

		
		UpdateMatLocal( );
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Absolute translation
	Parameters:
	[in] x - X position
	[in] y - Y position
	[in] z - Z position
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	void WorldTransform::TranslateAbs(float x, float y, float z) {
		m_transX = x;
		m_transY = y;
		m_transZ = z;

		m_translation = glm::mat4(1.0f);
		m_translation = glm::translate(m_translation, glm::vec3(x, y, z));

		m_position.x = x;
		m_position.y = y;
		m_position.z = z;

		UpdateMatLocal( );
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Relative translation
	Parameters:
	[in] x - X amount
	[in] y - Y amount
	[in] z - Z amount
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	void WorldTransform::TranslateRel(float x, float y, float z) {
		m_transX += x;
		m_transY += y;
		m_transZ += z;

		m_translation = glm::translate(m_translation, glm::vec3(x, y, z));

		m_position.x += x;
		m_position.y += y;
		m_position.z += z;

		UpdateMatLocal( );
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Absolute rotation
	Parameters:
	[in] x - X radians
	[in] y - Y radians
	[in] z - Z radians
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	void WorldTransform::RotateAbs(float x, float y, float z) {
		m_rotationX = x;
		m_rotationY = y;
		m_rotationZ = z;

		m_rotation = glm::mat4(1.0f);
		
		m_rotation *= glm::rotate(y, glm::vec3(0.0f, 1.0f, 0.0f));
		m_rotation *= glm::rotate(x, glm::vec3(1.0f, 0.0f, 0.0f));
		m_rotation *= glm::rotate(z, glm::vec3(0.0f, 0.0f, 1.0f));

		UpdateMatLocal( );
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Relative rotation
	Parameters:
	[in] x - X radians
	[in] y - Y radians
	[in] z - Z radians
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	void WorldTransform::RotateRel(float x, float y, float z) {
		m_rotationX += x;
		m_rotationY += y;
		m_rotationZ += z;
		m_rotation = glm::rotate(m_rotation, x, glm::vec3(1.0f, 0.0f, 0.0f));
		m_rotation = glm::rotate(m_rotation, y, glm::vec3(0.0f, 1.0f, 0.0f));
		m_rotation = glm::rotate(m_rotation, z, glm::vec3(0.0f, 0.0f, 1.0f));

		UpdateMatLocal( );
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Absolute scale.
	Parameters:
	[in] x - X size
	[in] y - Y size
	[in] z - Z size
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	void WorldTransform::ScaleAbs(float x, float y, float z) {
		m_scaleX = x;
		m_scaleY = y;
		m_scaleZ = z;

		m_scale = glm::mat4(1.0f);

		m_scale = glm::scale(m_scale, glm::vec3(x, y, z));

		UpdateMatLocal( );
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Relative scale.
	Parameters:
	[in] x - X size
	[in] y - Y size
	[in] z - Z size
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	void WorldTransform::ScaleRel(float x, float y, float z) {
		m_scaleX += x;
		m_scaleY += y;
		m_scaleZ += z;
		m_scale = glm::scale(m_scale, glm::vec3(x, y, z));

		UpdateMatLocal( );
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Get the transformation matrix
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	glm::mat4& WorldTransform::GetTransform( ) {
		
		if (!m_parented) {
			return m_localTransform;
		} 
		
		if (m_ppParentTransform->m_sync_num!=m_sync_num) {
			
			m_parentTransform = (m_ppParentTransform->GetTransform( ));
			m_par_sync_num = m_ppParentTransform->m_sync_num;
		}

		m_worldTransform = m_parentTransform*m_localTransform;
		return m_worldTransform;
	}

   

	void WorldTransform::SetLookAt( float x, float y, float z ) {
		
		vec3 lookPoint = vec3 ( x, y, z );
		
		vec3 lookDir =  normalize(lookPoint - m_position);

		float lookLengthOnXZ = sqrtf( lookDir.z*lookDir.z + lookDir.x*lookDir.x );
		m_rotationX = -degrees(atan2f( lookDir.y, lookLengthOnXZ ));
		m_rotationY = degrees(atan2f( lookDir.x, lookDir.z ));

		RotateAbs( m_rotationX, m_rotationY, m_rotationZ );

		UpdateMatLocal( );
	}
}