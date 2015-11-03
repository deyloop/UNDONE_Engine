#pragma once

#ifndef _BRO_H_
#define _BRO_H_

#include <Undone_Engine.h>
using namespace UNDONE_ENGINE;

class bro : public Behavior {
	public:
		void Load( )  {};
		void UnLoad() {};
		
		void TurnLeft( ) {
			m_WorldTransform->RotateRel( 0.0f, 0.9f, 0.0f );
		}

		void TurnRight( ) {
			m_WorldTransform->RotateRel( 0.0f, -0.9f, 0.0f );

		}

		void MoveBackward( ) {
			m_WorldTransform->TranslateRel(unvec3((-m_WorldTransform->GetForward()*0.05f)));
		}

		void MoveForward( ) {
			m_WorldTransform->TranslateRel(unvec3((m_WorldTransform->GetForward()*0.05f)));

		}

 };

#endif