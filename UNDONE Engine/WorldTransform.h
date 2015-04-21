/******************************************************************************
File:		WorldTransform.h
Author:		Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _WORLDTRANSFORM_H_
#define _WORLDTRANSFORM_H_

#include "UNDONE_Engine_declr.h"
#include "Component.h"
#include <glm.hpp>
using namespace glm;
namespace UNDONE_ENGINE {
	class WorldTransform : public Component {
	public:
		UNDONE_API WorldTransform( );
		UNDONE_API ~WorldTransform( ) { Reset( ); }

		UNDONE_API void Load( ) { };
		UNDONE_API void Unload( ) { };

		UNDONE_API void OnParentBeingChilded( );

		UNDONE_API void Reset( );
		UNDONE_API void TranslateAbs(float x, float y, float z);
		UNDONE_API void TranslateRel(float x, float y, float z);
		UNDONE_API void RotateAbs(float x, float y, float z);
		UNDONE_API void RotateRel(float x, float y, float z);
		UNDONE_API void ScaleAbs(float x, float y, float z);
		UNDONE_API void ScaleRel(float x, float y, float z);

		UNDONE_API glm::mat4& GetTransform( );
		UNDONE_API glm::vec3* GetPosition( ) { return &m_position; }
		UNDONE_API float GetXPosition( ) { return m_transX; }
		UNDONE_API float GetYPosition( ) { return m_transY; }
		UNDONE_API float GetZPosition( ) { return m_transZ; }
		UNDONE_API float GetXRotation( ) { return m_rotationX; }
		UNDONE_API float GetYRotation( ) { return m_rotationY; }
		UNDONE_API float GetZRotation( ) { return m_rotationZ; }
		UNDONE_API float GetXScale( ) { return m_scaleX; }
		UNDONE_API float GetYScale( ) { return m_scaleY; }
		UNDONE_API float GetZScale( ) { return m_scaleZ; }
		UNDONE_API void SetXPosition(float x) { TranslateAbs(x, m_transY, m_transZ); }
		UNDONE_API void SetYPosition(float y) { TranslateAbs(m_transX, y, m_transZ); }
		UNDONE_API void SetZPosition(float z) { TranslateAbs(m_transX, m_transY, z); }
		UNDONE_API void SetXRotation(float x) { RotateAbs(x, m_rotationY, m_rotationZ); }
		UNDONE_API void SetYRotation(float y) { RotateAbs(m_rotationX, y, m_rotationZ); }
		UNDONE_API void SetZRotation(float z) { RotateAbs(m_rotationX, m_rotationY, z); }
		UNDONE_API void SetXScale(float x) { ScaleAbs(x, m_scaleY, m_scaleZ); }
		UNDONE_API void SetYScale(float y) { ScaleAbs(m_scaleX, y, m_scaleZ); }
		UNDONE_API void SetZScale(float z) { ScaleAbs(m_scaleX, m_scaleY, z); }

	protected:
		void UpdateMatLocal( ) { 
			m_localTransform = m_translation*m_rotation*m_scale;
			++m_sync_num;
		};

		glm::mat4 m_localTransform, m_rotation, m_translation, m_scale;
		glm::vec3 m_position;
		float m_rotationX, m_rotationY, m_rotationZ,
			m_scaleX, m_scaleY, m_scaleZ,
			m_transX, m_transY, m_transZ;

		glm::mat4		m_worldTransform;
		glm::mat4		m_parentTransform;
		unsigned		m_sync_num;
		unsigned		m_par_sync_num;
		bool			m_parented;

		DPointer<WorldTransform> m_ppParentTransform;

		UNDONE_API void OnParentSet( );
	};
}
#endif