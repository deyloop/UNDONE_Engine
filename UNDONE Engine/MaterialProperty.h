/******************************************************************************
Project	:	UNDONE Engine
File	:	MaterialProperty.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _MATERIAL_PROPERTY_H
#define _MATERIAL_PROPERTY_H

#include	"UniformType.h"
#include	<glew.h>
#include	<string>
using std::string;

namespace UNDONE_ENGINE {
	struct MaterialProperty {
		MaterialProperty( ) {
			name		= "";
			datalength	= 0;
			in_interface = false;
		};

		string			name;
		UniformType		type;
		GLenum			gl_type;
		GLsizei			datalength;
		int				uniform_data_location;
		bool			in_interface;
		union data {
			float	Data_f;
			float*	Data_fp;
			int		Data_i;
			bool	Data_b;
		} data;
	};
}

#endif