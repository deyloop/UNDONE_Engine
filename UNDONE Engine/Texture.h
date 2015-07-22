/******************************************************************************
Project	:	UNDONE Engine
File	:	Texture.h
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

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "unTexture.h"
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
		void Unload( );

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

	};
}
#endif
///////////////////////////////////////////////////////////////////////////////