/******************************************************************************
Project	:	UNDONE Engine
File	:	Undone_Engine.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Undone_Engine.h"
#include "FrameWork.h"

UNDONE_ENGINE::UnFramework* Create_Un_Framwork_Inst(IApp* pApp){
	return new UNDONE_ENGINE::FrameWork(pApp);
}