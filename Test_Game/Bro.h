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
			Gameobject->GetWorldTransform( )->RotateRel( 0.0f, 0.9f, 0.0f );
		}

		void TurnRight( ) {
			Gameobject->GetWorldTransform( )->RotateRel( 0.0f, -0.9f, 0.0f );

		}

		void MoveBackward( ) {
			Gameobject->GetWorldTransform( )->TranslateRel(unvec3((-Gameobject->GetWorldTransform()->GetForward()*0.05f)));
		}

		void MoveForward( ) {
			Gameobject->GetWorldTransform( )->TranslateRel(unvec3((Gameobject->GetWorldTransform()->GetForward()*0.05f)));

		}

 };

#endif