#pragma once
#ifndef _CAMERASCRIPT_H_
#define _CAMERASCRIPT_H_

#include <Undone_Engine.h>
using namespace UNDONE_ENGINE;

class Camera_Script : public Behavior {
	public:
		void Load( )  {};
		void UnLoad() {};
		
        Dptr<unGameObject> target;

		void TurnLeft( ) {
            Gameobject->GetWorldTransform( )->TranslateRel( unvec3( (Gameobject->GetWorldTransform( )->GetLeft( )*0.1f) ));
		}

		void TurnRight( ) {
            Gameobject->GetWorldTransform( )->TranslateRel( unvec3( (Gameobject->GetWorldTransform( )->GetRight( )*0.1f) ));

		}

		void MoveBackward( ) {
			Gameobject->GetWorldTransform( )->TranslateRel(unvec3((-Gameobject->GetWorldTransform()->GetForward()*0.05f)));
		}

		void MoveForward( ) {
			Gameobject->GetWorldTransform( )->TranslateRel(unvec3((Gameobject->GetWorldTransform()->GetForward()*0.05f)));

		}

        void Update( ) {
            vec3 pos = Gameobject->GetWorldTransform( )->GetPosition( );
            if (pos.y <= 5) {
                Gameobject->GetWorldTransform( )->TranslateAbs(
                    pos.x,
                    5, 
                    pos.z );
            }

            Gameobject->GetCamera( )->SetLookAt(unvec3(target->GetWorldTransform()->GetPosition()));
        }

private:
    Dptr<unCamera> cam;
 };

#endif