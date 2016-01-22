/******************************************************************************
Project	:	UNDONE Engine
File	:	UNDONE_Engine.h
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

#ifndef _UNDONE_ENGINE_H
#define _UNDONE_ENGINE_H

#include "SystemComponent.h"

#include "UnFramework.h"

#include "unGameObject.h"
#include "unWorldTransform.h"
#include "unShader.h"
#include "unShaderProgram.h"
#include "unGraphicMaterial.h"
#include "unTexture.h"
#include "unMesh.h"
#include "unGraphic3D.h"
#include "unGraphic2D.h"
#include "unBehaviorAttachement.h"
#include "Behavior.h"
#include "unCamera.h"
#include "InputContext.h"


UNDONE_API UNDONE_ENGINE::UnFramework* Create_Un_Framwork_Inst(IApp* pAppa);

#define unvec3(vec) vec.x, vec.y, vec.z
#define unvec4(vec) vec.x, vec.y, vec.z, vec.w

#define SafelyDelete(x){x->Release();delete x;}

#endif
