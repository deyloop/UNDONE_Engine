/******************************************************************************
Project	:	UNDONE Engine
File	:	Texture.cpp
Author	:	Anurup Dey
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
	}

	/*-------------------------------------------------------------------------
	Laods a texture image from file.
	Parameters:
	[IN]	filename		-	filename from which to load the data from.
	[IN]	generateMipmaps	-	flag indicating weather tho generate mipmaps.
	REturns:
	true on successful loading, false on falure.
	-------------------------------------------------------------------------*/
	bool Texture::LoadTexture2D(string filename, bool generateMipMaps) {
		FREE_IMAGE_FORMAT image_format = FIF_UNKNOWN;
		FIBITMAP* bit_map(0);

		image_format = FreeImage_GetFileType(filename.c_str( ), 0);
		if (image_format==FIF_UNKNOWN) {
			//try to get the format from file extention.
			image_format = FreeImage_GetFIFFromFilename(filename.c_str( ));

			if (image_format==FIF_UNKNOWN) {
				//still unkown, can't load file.
				coutput("Texture loading FAILED: file format not supported: "
						+filename.c_str( )+"\n");
				return false;
			}
		}

		if (FreeImage_FIFSupportsReading(image_format)) {
			bit_map = FreeImage_Load(image_format, filename.c_str( ));
			if (!bit_map) return false;
		}

		BYTE* Dataptr = FreeImage_GetBits(bit_map);

		//set the properties.
		m_width = FreeImage_GetWidth(bit_map);
		m_hieght = FreeImage_GetHeight(bit_map);
		m_bits_per_pixl = FreeImage_GetBPP(bit_map);
		m_filename = filename;
		
		//Genarate OpenGL texture ID for this texture.
		glGenTextures(1, (GLuint*)&m_uiTexture);
		glBindTexture(GL_TEXTURE_2D, m_uiTexture);

		int format = m_bits_per_pixl==24 ? GL_BGR : m_bits_per_pixl==8 ? GL_LUMINANCE : 0;
		int internalFormat = m_bits_per_pixl==24?GL_RGB:GL_DEPTH_COMPONENT;

		glTexImage2D(
						GL_TEXTURE_2D,
						0,
						GL_RGB,
						m_width,
						m_hieght,
						0,
						format,
						GL_UNSIGNED_BYTE,
						Dataptr
					);
		if (generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);

		FreeImage_Unload(bit_map);

		glGenSamplers(1, &m_uiSampler);

		m_mipmaps_generated = generateMipMaps;

		coutput("Image Loaded from file: "+filename.c_str( )+"\n");
		return true;
	}

	/*-------------------------------------------------------------------------
	Sets the Filtering parameters.
	-------------------------------------------------------------------------*/
	void Texture::SetFiltering(int magnification, int minification) {
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