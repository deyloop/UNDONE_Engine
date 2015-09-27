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

namespace UNDONE_ENGINE {

    void BehaviorAttachement::Load( ) {
        //calls the Load() function on all the scripts.
        for (auto& Behavior : m_BehaviorList) {
            //call
        }
    }

    void BehaviorAttachement::Unload( ) {
        //calss the UnLoad() function on all scripts.
         for (auto& Behavior : m_BehaviorList) {
            //call
        }
    }

    void BehaviorAttachement::AddBehavior( const char* script_name,
                                           Behavior * behavior_script ) {
        m_BehaviorList.push_back( behavior_script );
        m_Names.push_back( script_name );

    }

    void BehaviorAttachement::OnParentSet( ) {



    }

}
