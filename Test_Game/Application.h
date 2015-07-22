/*-----------------------------------------------------------------------------
File	:	Application.h
Author	:	Anurup Dey

	Copyright (C) 2015 Anurup Dey <anu.rup.dey98@gmail.com>
 
	This file is part of UNDONE-Engine.
  
    UNDONE-Engine can not be copied and/or distributed without the express
	permission of Anurup Dey. Unauthorized copying of this file, via any 
	medium is strictly prohibited.
	
	Proprietary and confidential.

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
	void LoadScene(UnObjectBuffer* pObjectBuffer);
	void Update();
protected:
	UnFramework*		m_pFrameWork;
	Camera*				m_pcam;
	vector<Command*>	m_Cmds;
	Dptr<unGameObject> BlockGroup;

	bool initialized;

	Command* Yaw_Pitch ;
	Command* Exit ;
	Command* Move_Forward ;
	Command* Move_Backward ;
	Command* Enable_Mouse ;
	Command* Disable_Mouse ;
};
#endif