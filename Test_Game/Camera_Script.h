#pragma once
#ifndef _CAMERASCRIPT_H_
#define _CAMERASCRIPT_H_

#include <Undone_Engine.h>
using namespace std;
using namespace UNDONE_ENGINE;

class Camera_Script : public Behavior {
	public:
		void Load( )  {
			Input->RegisterCallback(bind(&Camera_Script::TurnLeft,this ),"Rotate Left");
			Input->RegisterCallback(bind(&Camera_Script::TurnRight,this),"Rotate Right");
		};
		void UnLoad() {};
		
		Dptr<unGameObject> target;

		void TurnLeft( ) {
			m_WorldTransform->TranslateRel( unvec3( (m_WorldTransform->GetLeft( )*0.1f) ));
		}

		void TurnRight( ) {
			m_WorldTransform->TranslateRel( unvec3( (m_WorldTransform->GetRight( )*0.1f) ));

		}

		void MoveBackward( ) {
			m_WorldTransform->TranslateRel(unvec3((-m_WorldTransform->GetForward()*0.05f)));
		}

		void MoveForward( ) {
			m_WorldTransform->TranslateRel(unvec3((m_WorldTransform->GetForward()*0.05f)));

		}

		void Update( ) {
			vec3 pos = m_WorldTransform->GetPosition( );
			if (pos.y <= 5) {
				m_WorldTransform->TranslateAbs(
					pos.x,
					5, 
					pos.z );
			}

			if (!(distance(target->GetWorldTransform( )->GetPosition( ) , pos) <= 6.0f)) {
				MoveForward( );
			}

			m_Camera->SetLookAt(unvec3(target->GetWorldTransform()->GetPosition()));
		}

private:
	Dptr<unCamera> cam;
 };

#endif