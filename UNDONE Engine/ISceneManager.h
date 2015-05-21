/******************************************************************************
Project	:	UNDONE Engine
File	:	ISceneManager.h
Author	:	Anurup Dey
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