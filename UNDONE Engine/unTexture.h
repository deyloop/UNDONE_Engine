/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey

				Copyright (C) 2015  Anurup Dey

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

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
		virtual void CreateFromData(unsigned char* data, int width, int height,
									int BPP, unsigned int format, 
									bool generateMipMaps = false) = 0;
		virtual bool SetTexture2D(const char* filename, bool generateMipMaps = false) = 0;
		virtual void setFiltering(int magnification, int minification) = 0;

		virtual int GetMinificationFilter() = 0;
		virtual int GetMagnificationFilter() = 0;
		virtual int getWidth()	= 0;
		virtual int getHeight() = 0;
		virtual int getBPP()	= 0;

		virtual void Load() = 0;
		virtual void UnLoad() = 0;
	};
}
#endif
///////////////////////////////////////////////////////////////////////////////