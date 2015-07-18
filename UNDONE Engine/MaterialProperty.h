/******************************************************************************
Project	:	UNDONE Engine
File	:	MaterialProperty.h
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