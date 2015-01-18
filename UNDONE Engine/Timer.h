/******************************************************************************
File	:	Timer.h
Author	:	Anurup Dey
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
		const float GetFPS( ) const { return m_fps; }
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