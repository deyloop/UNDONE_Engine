/*-----------------------------------------------------------------------------
File	:	Application.h
Author	:	Anurup Dey
-----------------------------------------------------------------------------*/
#pragma once

#ifndef _APP_H_
#define _APP_H_

#include <vector>
#include <Undone_Engine.h>
using namespace UNDONE_ENGINE;
using namespace std;

class Application : public IApp{
public:
	Application();
	~Application(){ Release();}

	void Release();

	void LinkToEngine(UnFramework* pFrameWork);
	void LoadScene(DObjectBuffer* pObjectBuffer);
	void Update();
protected:
	UnFramework*		m_pFrameWork;
	Camera*				m_pcam;
	vector<Command*>	m_Cmds;
	DPointer<GameObject> BlockGroup;

	bool initialized;

	Command* Yaw_Pitch ;
	Command* Exit ;
	Command* Move_Forward ;
	Command* Move_Backward ;
	Command* Enable_Mouse ;
	Command* Disable_Mouse ;
};
#endif