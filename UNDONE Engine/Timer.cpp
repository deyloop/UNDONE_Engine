/******************************************************************************
File	:	Timer.cpp
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

		

		m_lastTime = m_currentTime;
	}
    
    const float Timer::GetFPS( ) {
        // Update FPS
		m_numFrames++;
		if (m_currentTime-m_lastFPSUpdate>=m_FPSUpdateInterval) {
			float currentTime = (float)m_currentTime/(float)m_ticksPerSecond;
			float lastTime = (float)m_lastFPSUpdate/(float)m_ticksPerSecond;
			m_fps = (float)m_numFrames/(currentTime-lastTime);

			m_lastFPSUpdate = m_currentTime;
			m_numFrames = 0;
		}
        return m_fps;
    }
}

///////////////////////////////////////////////////////////////////////////////