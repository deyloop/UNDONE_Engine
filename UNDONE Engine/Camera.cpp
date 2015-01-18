/******************************************************************************
File	:	Camera.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Camera.h"

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	Default constructor.
	-----------------------------------------------------------------------------*/
	Camera::Camera( ) {
		m_maxPitch = 89.0f;
		m_maxVelocity = 1.0f;
		m_invertY = false;
		m_enableYMovement = true;
		m_position = glm::vec3(10.0f);
		m_velocity = glm::vec3(0.0f);
		m_look = glm::vec3(0.0f, 0.0f, -1.0f);
		SetLookAt(glm::vec3(0.0f));
		CreateProjectionMatrix(90.0f, 1.0f, 1.0f, 100.0f);
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
		m_fov = fov;
		m_aspect = aspect;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
		m_projection = glm::perspective(m_fov, m_aspect, m_nearPlane, m_farPlane);
	}

	/*-----------------------------------------------------------------------------
	Moves the camera forward and backward
	Prameters:
	[IN] units - Amount to move
	-----------------------------------------------------------------------------*/
	void Camera::MoveForward(float units) {
		if (m_enableYMovement) {
			m_velocity += m_look * units;
		} else {
			glm::vec3 moveVector(m_look.x, 0.0f, m_look.x);
			moveVector = glm::normalize(moveVector);
			moveVector *= units;
			m_velocity += moveVector;
		}
	}

	/*-----------------------------------------------------------------------------
	Moves the camera left and right
	Parameters:
	[IN] units - Amount to move
	-----------------------------------------------------------------------------*/
	void Camera::Strafe(float units) {
		m_velocity += m_right * units;
	}

	/*-----------------------------------------------------------------------------
	Moves the camera up and down.
	Parameters:
	[IN] units - amount to move
	-----------------------------------------------------------------------------*/
	void Camera::MoveUp(float units) {
		if (m_enableYMovement) {
			m_velocity.y += units;
		}
	}

	/*-----------------------------------------------------------------------------
	Yaw the camera around its Y-axis.
	Prameters:
	[IN] degrees - degrees to yaw.
	-----------------------------------------------------------------------------*/
	void Camera::Yaw(float degrees) {
		if (degrees==0.0f) {
			return;
		}
		glm::mat4 rotation(1.0f);
		rotation = glm::rotate(rotation, degrees, m_up);
		m_right = glm::mat3(rotation) * m_right;
		m_look = glm::mat3(rotation) * m_look;
		m_right = glm::normalize(m_right);
		m_look = glm::normalize(m_look);
	}

	/*-----------------------------------------------------------------------------
	Pitch the camera around its X-axis.
	Parameters:
	[IN] degrees - degrees to pitch.
	-----------------------------------------------------------------------------*/
	void Camera::Pitch(float degrees) {
		if (degrees==0.0f) {
			return;
		}

		degrees = (m_invertY) ? -degrees : degrees;
		m_pitch -= degrees;
		if (m_pitch>m_maxPitch) degrees += m_pitch-m_maxPitch;
		if (m_pitch<-m_maxPitch) degrees += m_pitch+m_maxPitch;

		glm::mat4 rotation;
		rotation = glm::rotate(rotation, degrees, m_right);
		m_up = glm::mat3(rotation) * m_up;
		m_look = glm::mat3(rotation) * m_look;
		m_up = glm::normalize(m_up);
		m_look = glm::normalize(m_look);
	}

	/*-----------------------------------------------------------------------------
	Roll the camera around its z-axis.
	Parameters:
	[IN] degrees - degrees to roll;
	-----------------------------------------------------------------------------*/
	void Camera::Roll(float degrees) {
		if (degrees==0.0f) {
			return;
		}

		glm::mat4 rotation;
		rotation = glm::rotate(rotation, degrees, m_look);
		m_up = glm::mat3(rotation) * m_up;
		m_right = glm::mat3(rotation) * m_right;
		m_up = glm::normalize(m_up);
		m_right = glm::normalize(m_right);
	}

	/*-----------------------------------------------------------------------------
	Updates the camera and creates the new view matrix. Must be called ever time
	Properties of the csamera are changed. do not call each frame, only where changes
	are aplied.
	-----------------------------------------------------------------------------*/
	void Camera::Update( ) {
		//cap velocity to max velocity
		if (glm::length(m_velocity)>m_maxVelocity) {
			m_velocity = glm::normalize(m_velocity)*m_maxVelocity;
		}

		//Move the camera
		m_position += m_velocity;
		//Could decellerate here. I'll just stop completely.
		m_velocity = glm::vec3(0.0f);
		m_lookAt = m_position+m_look;

		//Calculate the new matrix
		m_view = glm::lookAt(m_position, m_lookAt, glm::vec3(0.0f, 1.f, 0.0f)/*m_up*/);

		//Set the camera axes from the view matrix
		m_right.x = -m_view[0][0]; //might have to nagate this. ogl uses right handed
		m_right.y = -m_view[1][0]; //coordianate system?
		m_right.x = -m_view[2][0];
		m_up.x = m_view[0][1];
		m_up.y = m_view[1][1];
		m_up.z = m_view[2][1];
		m_look.x = -m_view[0][2];
		m_look.y = -m_view[1][2];
		m_look.z = -m_view[2][2];

		// Calculate yaw and pitch
		float lookLengthOnXZ = sqrtf(m_look.z * m_look.z+m_look.x * m_look.x);
		m_pitch = atan2f(m_look.y, lookLengthOnXZ);
		m_yaw = atan2f(m_look.x, m_look.z);
	}

	/*-----------------------------------------------------------------------------
	Sets camera position.
	Parameter:
	[in] refPos - new position
	-----------------------------------------------------------------------------*/
	void Camera::SetPosition(glm::vec3& refPos) {
		m_position = refPos;
	}

	/*-----------------------------------------------------------------------------
	Sets camera look at position - the point at wich the camera is looking at.
	Parameters:
	[in] refLookAt - new target
	-----------------------------------------------------------------------------*/
	void Camera::SetLookAt(glm::vec3& refLookAt) {
		m_lookAt = refLookAt;
		m_look = glm::normalize(m_lookAt-m_position);
	}

}