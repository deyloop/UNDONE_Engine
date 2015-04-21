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

	class Texture {
	public:
		UNDONE_API Texture( );
		UNDONE_API ~Texture( ) { Release( ); }

		void Release( ) { };

		UNDONE_API void CreateFromData(signed char* data, int width, int height, int BPP, unsigned int format, bool generateMipMaps = false);
		UNDONE_API bool SetTexture2D(string filename, bool generateMipMaps = false);
		void BindTexture(int textureUnit = 0);

		void Load( );
		void Unload( );

		void setSamplerParameter(unsigned parameter, unsigned value);
		UNDONE_API void SetFiltering(int magnification, int minification);

		UNDONE_API int GetMinificationFilter( ) { return m_minification; }
		UNDONE_API int	GetMagnificationFilter( ) { return m_magnification; }
		UNDONE_API int getWidth( ) { return m_width; }
		UNDONE_API int getHeight( ) { return m_hieght; }
		UNDONE_API int getBPP( ) { return m_bits_per_pixl; }

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