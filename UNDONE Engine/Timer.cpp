/******************************************************************************
File	:	Timer.cpp
Author	:	Anurup.Dey

		Copyright (C) 2015 Anurup Dey 
		<anu.rup.dey98@gmail.com>

	This file is part of UNDONE-Engine.

	UNDONE-Engine can not be copied and/or distributed without the express
	permission of Anurup Dey. Unauthorized copying of this file, via any
	medium is strictly prohibited.

	Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Timer.h"

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	Summary:	Default Constructor.
	-----------------------------------------------------------------------------*/
	Timer::Timer( ) {
		m_pSystem = SystemComponent::GetInstance( );
		m_ticksPerSecond = m_pSystem->GetSystemTickRate( );

		m_currentTime = m_lastTime = m_lastFPSUpdate = 0;
		m_numFrames = 0;
		m_runningTime = m_timeElapsed = m_fps = 0.0f;
		m_FPSUpdateInterval = m_ticksPerSecond>>1;
		m_timerStopped = true;
	}

	/*-----------------------------------------------------------------------------
	Summary:	Starts the timer.
	-----------------------------------------------------------------------------*/
	void Timer::Start( ) {
		if (!m_timerStopped) {
			// Already started
			return;
		}
		m_lastTime = m_pSystem->GetCurrentTickCount( );
		m_timerStopped = false;
	}

	/*-----------------------------------------------------------------------------
	Summary:	Stops the timer.
	-----------------------------------------------------------------------------*/
	void Timer::Stop( ) {
		if (m_timerStopped) {
			// Already stopped
			return;
		}
		__int64 stopTime = 0;
		stopTime = m_pSystem->GetCurrentTickCount( );
		m_runningTime += (float)(stopTime-m_lastTime)/(float)m_ticksPerSecond;
		m_timerStopped = true;
	}

	/*-----------------------------------------------------------------------------
	Summary:	Updates the timer. Calculates the time elsapsed since the last Update
	call. Updates the frames per second and updates the total running
	time.
	-----------------------------------------------------------------------------*/
	void Timer::Update( ) {
		if (m_timerStopped) {
			return;
		}

		// Get the current time
		m_currentTime = m_pSystem->GetCurrentTickCount( );

		m_timeElapsed = (float)(m_currentTime-m_lastTime)/(float)m_ticksPerSecond;
		m_runningTime += m_timeElapsed;

		// Update FPS
		m_numFrames++;
		if (m_currentTime-m_lastFPSUpdate>=m_FPSUpdateInterval) {
			float currentTime = (float)m_currentTime/(float)m_ticksPerSecond;
			float lastTime = (float)m_lastFPSUpdate/(float)m_ticksPerSecond;
			m_fps = (float)m_numFrames/(currentTime-lastTime);

			m_lastFPSUpdate = m_currentTime;
			m_numFrames = 0;
		}

		m_lastTime = m_currentTime;
	}
}

///////////////////////////////////////////////////////////////////////////////