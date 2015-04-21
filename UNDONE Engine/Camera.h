/******************************************************************************
File	:	Camera.h
Author	:	Anurup.Dey
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
#include <iostream>

namespace UNDONE_ENGINE {

	class UNDONE_API MoveControl : public InputControl {
	public:
		MoveControl( ) {
			moused = false;
		}
		virtual void Yaw(float degrees) = 0;
		virtual void MoveForward(float units) = 0;
		virtual void Strafe(float units) = 0;
		virtual void MoveUp(float units)=0;

		virtual void Pitch(float degrees)=0;
		virtual void Roll(float degrees)=0;

		bool moused;
	};

	
	class Yaw_PitchCommand : public Command {
	public:
		void execute(InputControl* control, InputEvent& given_event) {
			MoveControl* m_control = (MoveControl*)control;
			
			if (given_event.event.type==EVENT_KEYDOWN) {
				m_control->Yaw(1.0f);
				m_control->Pitch(1.0f);
			} else if (given_event.event.type==EVENT_MOUSEMOVE) {
				if (!(m_control->moused)) return;
				m_control->Pitch(-given_event.mouse_motion.delta_y*0.5f);
				m_control->Yaw(-given_event.mouse_motion.delta_x*0.5f);
			}
		}
	};

	class Enable_Yaw_Pitch_Command : public Command {
	public:
		void execute(InputControl* control, InputEvent& given_event) {
			MoveControl* m_control = (MoveControl*)control;
			m_control->moused = true;
		}
	};

	class Disable_Yaw_Pitch_Command : public Command {
	public:
		void execute(InputControl* control, InputEvent& given_event) {
			MoveControl* m_control = (MoveControl*)control;
			m_control->moused = false;
		}
	};


	class MoveForwardCommand : public Command {
	public:
		void execute(InputControl* control, InputEvent& given_event) {
			MoveControl* m_control = (MoveControl*)control;
			m_control->MoveForward(0.1f);
		}
	};

	class MoveBackwardCommand : public Command {
	public:
		void execute(InputControl* control, InputEvent& given_event) {
			MoveControl* m_control = (MoveControl*)control;
			m_control->MoveForward(-0.1f);
		}
	};
	/*-----------------------------------------------------------------------------
	THis class object structure represents the camera object, which is used to get
	the view of the world. This class controls and encapsulates the view and
	projection transforms of the objects when rendered to the screen.
	-----------------------------------------------------------------------------*/
	class Camera :public MoveControl {
	public:
		UNDONE_API Camera( );

		virtual void YawLeft( ) { Yaw(1.0f); }
		virtual void YawRight( ) { Yaw(-1.0f); }

		UNDONE_API void CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane);
		void MoveForward(float units);
		void Strafe(float units);
		void MoveUp(float units);

		void Yaw(float degrees);
		void Pitch(float degrees);
		void Roll(float degrees);
		UNDONE_API void Update( );

		UNDONE_API void SetPosition(glm::vec3& refPosition);
		UNDONE_API void SetLookAt(glm::vec3& refLookAt);
		UNDONE_API void SetFOV(float fov) { CreateProjectionMatrix(fov, m_aspect, m_nearPlane, m_farPlane); }
		UNDONE_API void SetAspectRatio(float aspect) { CreateProjectionMatrix(m_fov, aspect, m_nearPlane, m_farPlane); }
		UNDONE_API void SetNearPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, plane, m_farPlane); }
		UNDONE_API void SetFarPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, m_nearPlane, plane); }
		UNDONE_API void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
		UNDONE_API void SetInvertY(bool invert) { m_invertY = invert; }
		UNDONE_API void SetMaxPitch(float maxPitch) { m_maxPitch = maxPitch; }

		glm::mat4* GetViewMatrix( ) { return &m_view; }
		glm::mat4* GetProjectionMatrix( ) { return &m_projection; }
		glm::vec3* GetPosition( ) { return &m_position; }
		glm::vec3* GetLookAt( ) { return &m_lookAt; }
		float GetFOV( ) { return m_fov; }
		float GetAspectRatio( ) { return m_aspect; }
		float GetNearPlane( ) { return m_nearPlane; }
		float GetFarPlane( ) { return m_farPlane; }
		float GetMaxVelocity( ) { return m_maxVelocity; }
		bool  GetInvertY( ) { return m_invertY; }
		float GetPitch( ) { return m_pitch; }
		float GetYaw( ) { return m_yaw; }
		float GetMaxPitch( ) { return m_maxPitch; }

	private:

		glm::mat4	m_view;
		glm::mat4	m_projection;
		glm::vec3	m_right;
		glm::vec3	m_up;
		glm::vec3	m_look;
		glm::vec3	m_position;
		glm::vec3	m_lookAt;
		glm::vec3	m_velocity;

		float       m_yaw;
		float       m_pitch;
		float       m_maxPitch;
		float       m_maxVelocity;
		float       m_fov;
		float       m_aspect;
		float       m_nearPlane;
		float       m_farPlane;
		bool        m_invertY;
		bool        m_enableYMovement;
	};
}
#endif

///////////////////////////////////////////////////////////////////////////////