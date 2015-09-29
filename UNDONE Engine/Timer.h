/******************************************************************************
File	:	Timer.h
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
#pragma once

#ifndef _UNDONE_TIMER_H_
#define _UNDONE_TIMER_H_
//Includes:
#include "SystemComponent.h"		//For the quarying the system timer.

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	Summary:	The timer class is resposible for handelling all timing
	related opperations.
	-----------------------------------------------------------------------------*/
	class Timer {
	public:
		Timer( );
		void Start( );
		void Stop( );
		void Update( );

		const bool IsStopped( ) const { return m_timerStopped; }
        const float GetFPS( );
		const float GetRunningTime( ) const { return m_runningTime; }
		const float GetElapsedTime( ) const { return m_timerStopped ? 0.0f: m_timeElapsed; }

	private:
		__int64				m_ticksPerSecond;
		__int64				m_currentTime;
		__int64				m_lastTime;
		__int64				m_lastFPSUpdate;
		__int64				m_FPSUpdateInterval;
		unsigned			m_numFrames;
		float				m_runningTime;
		float				m_timeElapsed;
		float				m_fps;
		bool				m_timerStopped;
		SystemComponent*	m_pSystem;
	}; // end of Timer class
}
#endif //_UNDONE_TIMER_H