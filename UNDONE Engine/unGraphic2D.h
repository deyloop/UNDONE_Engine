/******************************************************************************
Project	:	UNDONE Engine
File	:	
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _UN_GRAPHIC2D_H_
#define _UN_GRAPHIC2D_H_

#include "unComponent.h"

namespace UNDONE_ENGINE{
	
	class unTexture;
	
	struct rect {
		float x, y, width, hieght;
	};

	class unGraphic2D {
	public:
		virtual void SetTexture(DPointer<unTexture> ppTex) =0;
		virtual void SetImageRect(rect& rectref)=0;
	};
}
#endif