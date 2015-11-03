/******************************************************************************
Project	:	UNDONE Engine
File	:   BehaviorAttachment.cpp
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
#include "BehaviorAttachement.h"
#include "UnFramework.h"
#include "Behavior.h"
#include "GameObject.h"

namespace UNDONE_ENGINE {

    //static subsystem pointers for behaviors
    unInput*        Behavior::Input        = nullptr;
    unGraphics*     Behavior::Graphics     = nullptr;
    unObjectBuffer* Behavior::Objectbuffer = nullptr;

    void BehaviorAttachement::setFramework( UnFramework* pFramework ) {
        Behavior::Graphics     = pFramework->Graphics;
        Behavior::Input        = pFramework->Input;
        Behavior::Objectbuffer = pFramework->Objectbuffer;
    }

    void BehaviorAttachement::Load( ) {
        //calls the Load() function on all the scripts.
        for (auto& behavior : m_BehaviorList) {
            //call
            behavior->Load( );
        }
    }

    void BehaviorAttachement::Unload( ) {
        //calss the UnLoad() function on all scripts.
         for (auto& behavior : m_BehaviorList) {
            //call
             behavior->UnLoad( );
        }
    }

    void BehaviorAttachement::AddBehavior( const char* script_name,
                                           Behavior * behavior_script ) {
        m_BehaviorList.push_back( behavior_script );
        m_Names.push_back( script_name );
        behavior_script->m_GameObject = dcast<unGameObject, GameObject>(m_ppParent);
        
        #define _GEN_DEF_BEHAVIOR_ATT_CPP_
        #include "GENERATE_FUNCTIONS.h"
        GEN_FUNCTIONS_ONLY_COMPS_NO_GAMEOBJECT()

    }

    void BehaviorAttachement::OnParentSet( ) {



    }

}
