/******************************************************************************
File:		WorldTransform.cpp
Author:		Anurup Dey
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
		m_ppParentTransform.m_pointer = nullptr;
		m_sync_num		= 0;
		m_par_sync_num	= 0;
		m_parented		= false;
		Reset( );
	}

	void WorldTransform::OnParentSet( ) {
		
	}

	void WorldTransform::OnParentBeingChilded( ) {
		m_ppParentTransform.m_pointer = m_ppParent->GetParent( )->worldTransform.m_pointer;
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

		++m_sync_num;
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

		++m_sync_num; UpdateMatLocal( );
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

		++m_sync_num; UpdateMatLocal( );
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
		m_rotation = glm::rotate(m_rotation, x, glm::vec3(1.0f, 0.0f, 0.0f));
		m_rotation = glm::rotate(m_rotation, y, glm::vec3(0.0f, 1.0f, 0.0f));
		m_rotation = glm::rotate(m_rotation, z, glm::vec3(0.0f, 0.0f, 1.0f));

		++m_sync_num; UpdateMatLocal( );
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

		++m_sync_num; UpdateMatLocal( );
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

		++m_sync_num; UpdateMatLocal( );
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

		++m_sync_num; UpdateMatLocal( );
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Get the transformation matrix
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	glm::mat4& WorldTransform::GetTransform( ) {
		
		if (!m_parented) {
			return m_localTransform;
		} else if (m_ppParentTransform->m_sync_num!=m_par_sync_num) {
			
			m_parentTransform = (m_ppParentTransform->GetTransform( ));
			m_par_sync_num = m_ppParentTransform->m_sync_num;
	
		}

		m_worldTransform = m_parentTransform*m_localTransform;
		return m_worldTransform;
	}
}