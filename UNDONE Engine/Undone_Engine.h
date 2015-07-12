/******************************************************************************
Project	:	UNDONE Engine
File	:	UNDONE_Engine.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _UNDONE_ENGINE_H
#define _UNDONE_ENGINE_H

#include "SystemComponent.h"

#include "UnFramework.h"
#include "UnObjectBuffer.h"

#include "unGameObject.h"
#include "unWorldTransform.h"
#include "unShader.h"
#include "unShaderProgram.h"
#include "unGraphicMaterial.h"
#include "unTexture.h"
#include "unMesh.h"
#include "unGraphic3D.h"
#include "unGraphic2D.h"


#include "unCamera.h"

#include "Camera.h"

UNDONE_API UNDONE_ENGINE::UnFramework* Create_Un_Framwork_Inst(IApp* pAppa);

#define unvec3(vec) vec.x, vec.y, vec.z
#define unvec4(vec) vec.x, vec.y, vec.z, vec.w

#endif
