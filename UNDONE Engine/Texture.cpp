/******************************************************************************
Project	:	UNDONE Engine
File	:	Texture.cpp
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
#include "Texture.h"
#include <glew.h>
#include <gl\GL.h>

#include <FreeImage.h>

#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	Default Constructor.
	-----------------------------------------------------------------------------*/
	Texture::Texture( ) {
		m_width				= m_hieght		= m_bits_per_pixl = 0;
		m_uiTexture			= m_uiSampler	= 0;
		m_mipmaps_generated = false;
		m_minification		= 0;
		m_magnification		= 0;
		m_filename			= "no_tex.png";
		m_loaded			= false;
		m_generate_mip_maps = false;
	}

	void Texture::CreateFromData(
		GLbyte * data, 
		int width, int height, 
		int BPP, GLenum format, 
		bool generateMipMaps) 
	{
		// Generate an OpenGL texture ID for this texture
		glGenTextures(1, &m_uiTexture);
		glBindTexture(GL_TEXTURE_2D, m_uiTexture);
		if (format==GL_RGBA||format==GL_BGRA)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// We must handle this because of internal format parameter
		else if (format==GL_RGB||format==GL_BGR)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		if (generateMipMaps)glGenerateMipmap(GL_TEXTURE_2D);
		glGenSamplers(1, &m_uiSampler);

		m_filename = "";
		m_mipmaps_generated = generateMipMaps;
		m_width			= width;
		m_hieght		= height;
		m_bits_per_pixl = BPP;
	}

	/*----------------------------------------------------------------------------
	Called by external agents when the texture requirements are needed to be loaded 
	into Graphics memory. Call before binding the texture.
	---------------------------------------------------------------------------*/
	void Texture::Load( ) {
		if (!m_loaded) {	//we want to load only once.
			FREE_IMAGE_FORMAT image_format = FIF_UNKNOWN;
			FIBITMAP* bit_map(0);

			image_format = FreeImage_GetFileType(m_filename.c_str( ), 0);
			if (image_format==FIF_UNKNOWN) {
				//try to get the format from file extention.
				image_format = FreeImage_GetFIFFromFilename(m_filename.c_str( ));

				if (image_format==FIF_UNKNOWN) {
					//still unkown, can't load file.
					coutput("Texture loading FAILED: file format not supported: "
							+m_filename.c_str( )+"\n");
					return;
				}
			}

			if (FreeImage_FIFSupportsReading(image_format)) {
				bit_map = FreeImage_Load(image_format, m_filename.c_str( ));
				if (!bit_map) {
					coutput("Texture loading FAILED: file format not supported: "
							+m_filename.c_str( )+"\n");
					return;
				}
			}

			BYTE* Dataptr = FreeImage_GetBits(bit_map);

			//set the properties.
			m_width = FreeImage_GetWidth(bit_map);
			m_hieght = FreeImage_GetHeight(bit_map);
			m_bits_per_pixl = FreeImage_GetBPP(bit_map);

			//Genarate OpenGL texture ID for this texture.
			glGenTextures(1, (GLuint*)&m_uiTexture);
			glBindTexture(GL_TEXTURE_2D, m_uiTexture);

			int format = m_bits_per_pixl == 32 ? GL_BGRA :  m_bits_per_pixl==24 ? GL_BGR : m_bits_per_pixl==8 ? GL_LUMINANCE : 0;
			int internalFormat = m_bits_per_pixl == 32 ? GL_RGBA :m_bits_per_pixl==24?GL_RGB:GL_DEPTH_COMPONENT;

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				internalFormat,
				m_width,
				m_hieght,
				0,
				format,
				GL_UNSIGNED_BYTE,
				Dataptr
				);
			if (m_generate_mip_maps) glGenerateMipmap(GL_TEXTURE_2D);

			FreeImage_Unload(bit_map);

			glGenSamplers(1, &m_uiSampler);

			m_mipmaps_generated = m_generate_mip_maps;

			coutput("Image Loaded from file: "+m_filename.c_str( )+"\n");

			m_loaded = true;
		}
	}

	void Texture::Unload( ) {
		if (m_loaded) {
			releaseTexture();
		}
	}

	/*-------------------------------------------------------------------------
	Laods a texture image from file.
	Parameters:
	[IN]	filename		-	filename from which to load the data from.
	[IN]	generateMipmaps	-	flag indicating weather tho generate mipmaps.
	REturns:
	true on successful loading, false on falure.
	-------------------------------------------------------------------------*/
	bool Texture::SetTexture2D(const char* filename, bool generateMipMaps) {
		
		m_filename = filename;
		m_generate_mip_maps = generateMipMaps;
		
		Load( );
		return true;
	}

	/*-------------------------------------------------------------------------
	Sets the Filtering parameters.
	-------------------------------------------------------------------------*/
	void Texture::setFiltering(int magnification, int minification) {
		// Set magnification filter
		if (magnification == TEXTURE_FILTER_MAG_NEAREST)
			glSamplerParameteri(m_uiSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		else if (magnification==TEXTURE_FILTER_MAG_BILINEAR)
			glSamplerParameteri(m_uiSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set minification filter
		if (minification==TEXTURE_FILTER_MIN_NEAREST)
			glSamplerParameteri(m_uiSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		else if (minification==TEXTURE_FILTER_MIN_BILINEAR)
			glSamplerParameteri(m_uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		else if (minification==TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
			glSamplerParameteri(m_uiSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		else if (minification==TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
			glSamplerParameteri(m_uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		else if (minification==TEXTURE_FILTER_MIN_TRILINEAR)
			glSamplerParameteri(m_uiSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		m_minification = minification;
		m_magnification = magnification;
	}

	void Texture::setSamplerParameter(unsigned parameter, unsigned value) {
		glSamplerParameteri(m_uiSampler, parameter, value);
	}

	/*-------------------------------------------------------------------------
	Name:	bindTexture
	Params:	iTextureUnit - texture unit to bind texture to
	Result:	Guess what it does :)
	/*-----------------------------------------------------------------------*/

	void Texture::BindTexture(int iTextureUnit) {
		glActiveTexture(GL_TEXTURE0+iTextureUnit);
		glBindTexture(GL_TEXTURE_2D, m_uiTexture);
		glBindSampler(iTextureUnit, m_uiSampler);
	}

	/*-------------------------------------------------------------------------
	Name:		releaseTexture
	Params:	none
	Result:	Frees all memory used by texture.
	/*-----------------------------------------------------------------------*/
	void Texture::releaseTexture( ) {
		glDeleteSamplers(1, &m_uiSampler);
		glDeleteTextures(1, &m_uiTexture);
	}

}