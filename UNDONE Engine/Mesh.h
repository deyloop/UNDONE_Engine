/******************************************************************************
Project	:	UNDONE Engine
File	:	Mesh.h
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

#ifndef _MESH_H_
#define _MESH_H_

//includes
#include "Component.h"		//Mesh IS a component
#include "unMesh.h"
#include <glew.h>			//used for the VAOs and the VBOs
#include <gl\GL.h>
#include <gl\GLU.h>

#include <string>
#include <vector>
using std::vector;
using std::string;

typedef  unsigned int UINT;

namespace UNDONE_ENGINE {
	/*----------------------------------------------------------------------------
	A Mesh data structure holds data about geometry. Must be used in conjuction
	with a Graphic3D Compnent to work properly.
	----------------------------------------------------------------------------*/
	class Mesh : public unMesh, public Component {
	public:
		Mesh( );
		~Mesh( ) { Release( ); }

		void SetModelFile(const char* filename) {
			m_model_file = filename; 
		};
		
		void Load( );
		void GPU_Upload();
		
		void Render( );
	
		void Unload( );
		void Release( );

		void OnParentAdopted( );

		static void SetCurrentlyBoundVAO(UINT uiVAOID) { currently_bound_VAO = uiVAOID; };
	
	private:
		void OnParentSet( );
		
		UINT uiVBO[3];
		UINT uiVAO[1];
		
		UINT m_num_parents;
		
		bool		mesh_loaded;
		int			m_instances;
		string		m_model_file;
		unsigned	m_num_verts;
		static UINT currently_bound_VAO;
		struct mesh_data{
			vector< float > vertices,
				            uvs,
							normals;
		} mesh_data;
	};
}
#endif