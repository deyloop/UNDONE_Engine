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

#include "Component.h"
#include "GameObject.h"
#include "WorldTransform.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "GraphicMaterial.h"
#include "Texture.h"
#include "Mesh.h"
#include "_3DGraphic.h"
#include "_2DGraphic.h"


#include "Camera.h"

UNDONE_API UNDONE_ENGINE::UnFramework* Create_Un_Framwork_Inst(IApp* pAppa);

#endif
