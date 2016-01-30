#pragma once
#ifndef _CAMERASCRIPT_H_
#define _CAMERASCRIPT_H_

#include <Undone_Engine.h>
using namespace std;
using namespace UNDONE_ENGINE;

class Camera_Script : public Behavior {
	public:

		float limit_hight;

		void Load( )  {
			limit_hight = 1;
			follow = true;
			Input->RegisterCallback(bind(&Camera_Script::TurnLeft,this ),"Rotate Left");
			Input->RegisterCallback(bind(&Camera_Script::TurnRight,this),"Rotate Right");
			Input->RegisterCallback(bind(&Camera_Script::ToggleFollow,this),"switch_camera_mode" );
			Input->RegisterCallback(bind(&Camera_Script::MoveForward,this),"fly_forward");
			Input->RegisterCallback(bind(&Camera_Script::MoveBackward,this),"fly_back");
			Input->RegisterCallback(bind(&Camera_Script::YawLeft,this),"yaw_left");
			Input->RegisterCallback(bind(&Camera_Script::YawRight,this),"yaw_right");
			Input->RegisterCallback(bind(&Camera_Script::LookUp,this),"yaw_up");
			Input->RegisterCallback(bind(&Camera_Script::LookDown,this),"yaw_down");

		};
		void UnLoad() {};
		
		Dptr<unGameObject> target;

		void YawLeft( ) {
			m_WorldTransform->RotateRel(0,1,0);
		}

		void YawRight( ) {
			m_WorldTransform->RotateRel(0,-1,0);

		}

		void LookUp( ) {
			m_WorldTransform->RotateRel(1,0,0);
		}

		void LookDown( ) {
			m_WorldTransform->RotateRel(-1,0,0);

		}

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

		void ToggleFollow( ) {
			if (follow) {
				follow = false;
				Input->ActivateContext("camera_movement");
			} else {
				follow = true;
				Input->DeactivateContext("camera_movement");
				
			}
		}

		void Update( ) {
			if(!follow) return;
			vec3 pos = m_WorldTransform->GetPosition( );
			if (pos.y <= limit_hight) {
				m_WorldTransform->TranslateAbs(
					pos.x,
					limit_hight, 
					pos.z );
			}

			if (!(distance(target->GetWorldTransform( )->GetPosition( ) , pos) <= 6.0f)) {
				MoveForward( );
			}

			m_Camera->SetLookAt(unvec3(target->GetWorldTransform()->GetPosition()));
		}

private:
	bool follow;
	Dptr<unCamera> cam;
 };

#endif