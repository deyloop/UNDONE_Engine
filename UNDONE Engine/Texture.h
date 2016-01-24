/******************************************************************************
Project	:	UNDONE Engine
File	:	Texture.h
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

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "unTexture.h"
#include <FreeImage.h>
#include <string>
using std::string;

namespace UNDONE_ENGINE {

	class Texture : public unTexture {
	public:
		Texture( );
		~Texture( ) { Release( ); }

		void Release( ) { };

		void CreateFromData(signed char* data, int width, int height, int BPP, unsigned int format, bool generateMipMaps = false);
		bool SetTexture2D(const char* filename, bool generateMipMaps = false);
		void BindTexture(int textureUnit = 0);

		void Load( );
		void UnLoad( );
		void GPU_Upload();

		void setSamplerParameter(unsigned parameter, unsigned value);
		void setFiltering(int magnification, int minification);

		int GetMinificationFilter( ) { return m_minification; }
		int	GetMagnificationFilter( ) { return m_magnification; }
		int getWidth( ) { return m_width; }
		int getHeight( ) { return m_hieght; }
		int getBPP( ) { return m_bits_per_pixl; }

		void releaseTexture( );

	private:
		
		int m_width, m_hieght, m_bits_per_pixl;
		unsigned m_uiTexture;
		unsigned m_uiSampler;
		bool m_generate_mip_maps;
		bool m_mipmaps_generated;
		bool m_loaded;

		int m_minification, m_magnification;

		string m_filename;
		FIBITMAP* bit_map;

	};
}
#endif
///////////////////////////////////////////////////////////////////////////////