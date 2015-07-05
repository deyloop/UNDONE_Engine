/******************************************************************************
File:		WorldTransform.h
Author:		Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _WORLDTRANSFORM_H_
#define _WORLDTRANSFORM_H_

#include "Component.h"
#include "unWorldTransform.h"
#include <glm.hpp>
using namespace glm;

namespace UNDONE_ENGINE {
	class WorldTransform : public Component, public unWorldTransform {
	public:
		WorldTransform( );
		~WorldTransform( ) { Reset( ); }

		void Load( ) { };
		void Unload( ) { };

		void OnParentBeingChilded( );

		void Reset( );
		void TranslateAbs(float x, float y, float z);
		void TranslateRel(float x, float y, float z);
		void RotateAbs(float x, float y, float z);
		void RotateRel(float x, float y, float z);
		void ScaleAbs(float x, float y, float z);
		void ScaleRel(float x, float y, float z);

		mat4& GetTransform( );
		vec3& GetPosition( ) { return m_position; }
		float GetXPosition( ) { return m_transX; }
		float GetYPosition( ) { return m_transY; }
		float GetZPosition( ) { return m_transZ; }
		float GetXRotation( ) { return m_rotationX; }
		float GetYRotation( ) { return m_rotationY; }
		float GetZRotation( ) { return m_rotationZ; }
		float GetXScale( ) { return m_scaleX; }
		float GetYScale( ) { return m_scaleY; }
		float GetZScale( ) { return m_scaleZ; }
		void SetXPosition(float x) { TranslateAbs(x, m_transY, m_transZ); }
		void SetYPosition(float y) { TranslateAbs(m_transX, y, m_transZ); }
		void SetZPosition(float z) { TranslateAbs(m_transX, m_transY, z); }
		void SetXRotation(float x) { RotateAbs(x, m_rotationY, m_rotationZ); }
		void SetYRotation(float y) { RotateAbs(m_rotationX, y, m_rotationZ); }
		void SetZRotation(float z) { RotateAbs(m_rotationX, m_rotationY, z); }
		void SetXScale(float x) { ScaleAbs(x, m_scaleY, m_scaleZ); }
		void SetYScale(float y) { ScaleAbs(m_scaleX, y, m_scaleZ); }
		void SetZScale(float z) { ScaleAbs(m_scaleX, m_scaleY, z); }

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

		void OnParentSet( );
	};
}
#endif