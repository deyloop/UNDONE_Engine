/******************************************************************************
Project	:	UNDONE Engine
File	:	Mesh.cpp
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
#include "Mesh.h" 
#include "UNDONE_DEBUG.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <glm.hpp>
#include<vector>
using namespace std;


namespace UNDONE_ENGINE {

	UINT Mesh::currently_bound_VAO = 0;

	/*-------------------------------------------------------------------------
	Default constructor.
	-------------------------------------------------------------------------*/
	Mesh::Mesh( ) {
		uiVBO[0] = uiVBO[1] = 0;
		uiVAO[0] = 0;
		m_num_parents	= 0;
		mesh_loaded		= false;
		m_instances		= 0;
		m_num_verts		= 0;
		m_model_file = "cube.obj";
	}

	/*----------------------------------------------------------------------------
	Default destructor.
	----------------------------------------------------------------------------*/
	void Mesh::Release( ) {
		Unload( );
	}

	/*----------------------------------------------------------------------------
	Loads the Mesh from file or otherwise. (At the current momment, this simply 
	sets up geometry for a cube.
	----------------------------------------------------------------------------*/
	void Mesh::Load( ) {
		if(mesh_loaded) return; //already loaded.

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_model_file.c_str(),
										aiProcess_Triangulate|
										aiProcess_SortByPType);
		if (!scene) return;

		m_num_verts = 0;

		aiMesh* mesh = scene->mMeshes[0];
		int iMeshFaces = mesh->mNumFaces;
		for (int j = 0; j<iMeshFaces; ++j) {
			const aiFace& face = mesh->mFaces[j];
			for (int k = 0; k<3; ++k) {
				aiVector3D pos = mesh->mVertices[face.mIndices[k]];
                aiVector3D uv = mesh->HasTextureCoords( 0 ) ? mesh->mTextureCoords[0][face.mIndices[k]] : aiVector3D( 1.0f );
				aiVector3D normal = mesh->HasNormals( ) ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f);
				mesh_data.vertices.push_back(pos.x);
				mesh_data.vertices.push_back(pos.y);
				mesh_data.vertices.push_back(pos.z);
				mesh_data.uvs.push_back( uv.y );
                mesh_data.uvs.push_back( uv.x );
				mesh_data.normals.push_back(normal.x);
				mesh_data.normals.push_back(normal.y);
				mesh_data.normals.push_back(normal.z);
				++m_num_verts;
			}
		}
		
		mesh_loaded = true;
	}

	void Mesh::GPU_Upload( ) {
		if(!mesh_loaded) return;
		glGenVertexArrays(1, uiVAO);
		glGenBuffers(3, uiVBO);
		// Setup whole cube
		glBindVertexArray(uiVAO[0]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, mesh_data.vertices.size()*sizeof(float), &mesh_data.vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, mesh_data.uvs.size()*sizeof(float), &mesh_data.uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, mesh_data.normals.size()*sizeof(float), &mesh_data.normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//delete all the data from the client side.
		mesh_data.vertices.clear();
		mesh_data.uvs.clear();
		mesh_data.normals.clear();
	}

	/*----------------------------------------------------------------------------
	UNloads any geometry loaded earlier.
	----------------------------------------------------------------------------*/
	void Mesh::Unload( ) {
		if (m_num_parents>0) return;

		if (mesh_loaded) {
			glDeleteBuffers(3, uiVBO);
			glDeleteVertexArrays(1, uiVAO);
			mesh_loaded = false;
		}

	}

	/*----------------------------------------------------------------------------
	Renders the mesh on to the screen.
	----------------------------------------------------------------------------*/
	void Mesh::Render( ) {
		if (currently_bound_VAO!=uiVAO[0]) { 
			glBindVertexArray(uiVAO[0]);
			currently_bound_VAO = uiVAO[0];
		}
		
		glDrawArrays(GL_TRIANGLES, 0, m_num_verts);
	}

	/*----------------------------------------------------------------------------
	Mesh keeps count of how many parents it has. If no parents are using it, It
	unloads itself, or does not load.
	----------------------------------------------------------------------------*/
	void Mesh::OnParentSet() {
		if (m_num_parents == 0) {
			++m_num_parents;
			return;
		} else {

			++m_num_parents;
		}
		
	}

	void Mesh::OnParentAdopted( ) {
		//Honestly, we don't care.
	}
}