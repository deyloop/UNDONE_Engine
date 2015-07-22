/******************************************************************************
Project	:	UNDONE Engine
File	:
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

#ifndef _UN_TEXTURE_H_
#define _UN_TEXTURE_H_

namespace UNDONE_ENGINE{
	enum ETextureFiltering {
		TEXTURE_FILTER_MAG_NEAREST = 0,		// Nearest criterion for magnification
		TEXTURE_FILTER_MAG_BILINEAR,		// Bilinear criterion for magnification
		TEXTURE_FILTER_MIN_NEAREST,			// Nearest criterion for minification
		TEXTURE_FILTER_MIN_BILINEAR,		// Bilinear criterion for minification
		TEXTURE_FILTER_MIN_NEAREST_MIPMAP,	// Nearest criterion for minification, but on closest mipmap
		TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
		TEXTURE_FILTER_MIN_TRILINEAR,		// Bilinear criterion for minification on two closest mipmaps, then averaged
	};

	class unTexture{
	public:
		virtual void CreateFromData(signed char* data, int width, int height,
									int BPP, unsigned int format, 
									bool generateMipMaps = false) = 0;
		virtual bool SetTexture2D(const char* filename, bool generateMipMaps = false) = 0;
		virtual void setFiltering(int magnification, int minification) = 0;

		virtual int GetMinificationFilter() = 0;
		virtual int GetMagnificationFilter() = 0;
		virtual int getWidth()	= 0;
		virtual int getHeight() = 0;
		virtual int getBPP()	= 0;
	};
}
#endif
///////////////////////////////////////////////////////////////////////////////