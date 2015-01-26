/*-----------------------------------------------------------------------------
File	:	Application.h
Author	:	Anurup Dey
-----------------------------------------------------------------------------*/
#pragma once

#ifndef _APP_H_
#define _APP_H_
//includes
#include "FrameWork.h"
#include "ShaderProgram.h"


using namespace UNDONE_ENGINE;

class Application : public IApp{
public:
	Application();
	~Application(){ Release();}

	void Release();

	void LinkToEngine(FrameWork* pFrameWork);
	void LoadScene(DObjectBuffer* pObjectBuffer);
	void Update();
protected:
	FrameWork*		m_pFrameWork;
	Camera*			m_pcam;
	vector<Command*> m_Cmds;
};
#endif