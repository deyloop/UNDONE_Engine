/******************************************************************************
Project	:	UNDONE Engine
File	:	Undone_Engine.cpp
Author	:	Anurup Dey

		Copyright (C) 2015 Anurup Dey 
		<anu.rup.dey98@gmail.com>

	This file is part of UNDONE-Engine.

	UNDONE-Engine can not be copied and/or distributed without the express
	permission of Anurup Dey. Unauthorized copying of this file, via any
	medium is strictly prohibited.

	Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Undone_Engine.h"
#include "FrameWork.h"

UNDONE_ENGINE::UnFramework* Create_Un_Framwork_Inst(IApp* pApp){
	return new UNDONE_ENGINE::FrameWork(pApp);
}