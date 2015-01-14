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
using namespace UNDONE_ENGINE;

class MoveControl : public InputControl {
public:
	virtual void YawLeft( ) = 0;
	virtual void YawRight( ) = 0;
};

class LeftYawCommand : public Command {
public:
	void execute(InputControl* control, InputEvent& given_event) {
		MoveControl* m_control = (MoveControl*)control;
		m_control->YawLeft( );
	}
};

class RightYawCommand : public Command {
public:
	void execute(InputControl* control, InputEvent& given_event) {
		MoveControl* m_control = (MoveControl*)control;
		m_control->YawRight( );
	}
};
/*-----------------------------------------------------------------------------
THis class object structure represents the camera object, which is used to get 
the view of the world. This class controls and encapsulates the view and
projection transforms of the objects when rendered to the screen.
-----------------------------------------------------------------------------*/
class UNDONE_API Camera :public MoveControl {
public:
	Camera();

	virtual void YawLeft( ) { Yaw(1.0f); }
	virtual void YawRight( ) { Yaw(-1.0f); }

	void CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane);
	void MoveForward(float units);
	void Strafe(float units);
	void MoveUp(float units);

	void Yaw(float degrees);
	void Pitch(float degrees);
	void Roll(float degrees);
	void Update();

	void SetPosition(glm::vec3& refPosition);
	void SetLookAt(glm::vec3& refLookAt);
	void SetFOV(float fov) { CreateProjectionMatrix(fov, m_aspect, m_nearPlane, m_farPlane); }
	void SetAspectRatio(float aspect) { CreateProjectionMatrix(m_fov, aspect, m_nearPlane, m_farPlane); }
	void SetNearPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, plane, m_farPlane); }
	void SetFarPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, m_nearPlane, plane); }
	void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	void SetInvertY(bool invert) { m_invertY = invert; }
	void SetMaxPitch(float maxPitch) { m_maxPitch = maxPitch; }

	glm::mat4* GetViewMatrix() { return &m_view; }
	glm::mat4* GetProjectionMatrix() { return &m_projection; }
	glm::vec3* GetPosition() { return &m_position; }
	glm::vec3* GetLookAt() { return &m_lookAt; }
	float GetFOV() { return m_fov; }
	float GetAspectRatio() { return m_aspect; }
	float GetNearPlane() { return m_nearPlane; }
	float GetFarPlane() { return m_farPlane; }
	float GetMaxVelocity() { return m_maxVelocity; }
	bool  GetInvertY() { return m_invertY; }
	float GetPitch() { return m_pitch; }
	float GetYaw() { return m_yaw; }
	float GetMaxPitch() { return m_maxPitch; }

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
#endif

///////////////////////////////////////////////////////////////////////////////