/******************************************************************************
Project	:	UNDONE Engine
File	:	Texture.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "UNDONE_Engine_declr.h"
#include <string>
using std::string;

namespace UNDONE_ENGINE {

	enum ETextureFiltering {
		TEXTURE_FILTER_MAG_NEAREST = 0,		// Nearest criterion for magnification
		TEXTURE_FILTER_MAG_BILINEAR,		// Bilinear criterion for magnification
		TEXTURE_FILTER_MIN_NEAREST,			// Nearest criterion for minification
		TEXTURE_FILTER_MIN_BILINEAR,		// Bilinear criterion for minification
		TEXTURE_FILTER_MIN_NEAREST_MIPMAP,	// Nearest criterion for minification, but on closest mipmap
		TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
		TEXTURE_FILTER_MIN_TRILINEAR,		// Bilinear criterion for minification on two closest mipmaps, then averaged
	};

	class UNDONE_API Texture {
	public:
		Texture( );
		~Texture( ) { Release( ); }

		void Release( ) { };

		bool LoadTexture2D(string filename, bool generateMipMaps = false);
		void BindTexture(int textureUnit = 0);

		void setSamplerParameter(unsigned parameter, unsigned value);
		void SetFiltering(int magnification, int minification);

		int GetMinificationFilter( ) { return m_minification; }
		int	GetMagnificationFilter( ) { return m_magnification; }
		int getWidth( )		{ return m_width; }
		int getHeight( )	{ return m_hieght; }
		int getBPP( )		{ return m_bits_per_pixl; }

		void releaseTexture( );

	private:
		int m_width, m_hieght, m_bits_per_pixl;
		unsigned m_uiTexture;
		unsigned m_uiSampler;
		bool m_mipmaps_generated;

		int m_minification, m_magnification;

		string m_filename;

	};
}
#endif
///////////////////////////////////////////////////////////////////////////////