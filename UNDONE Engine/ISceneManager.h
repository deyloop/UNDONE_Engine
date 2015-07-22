/******************************************************************************
Project	:	UNDONE Engine
File	:	ISceneManager.h
Author	:	Anurup Dey

Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>

This file is part of UNDONE-Engine.

UNDONE-Engine can not be copied and/or distributed without the express
permission of Anurup Dey. Unauthorized copying of this file, via any
medium is strictly prohibited.

Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H
namespace UNDONE_ENGINE {
	class Scene;
	/*-------------------------------------------------------------------------
	This interface must be implemented by the user of Scenes.
	(ie, the framework, or the scene manager.)
	------------------------------------------------------------------------*/
	class ISceneManager {
	public:
		virtual void ChangeScene(Scene* pScene) = 0;
	};
}
#endif