/******************************************************************************
Project	:	UNDONE Engine
File	:	Mesh.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Mesh.h" 
#include "UNDONE_DEBUG.h"
#include <assimp/Importer.hpp>
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

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_model_file.c_str(),
										aiProcess_Triangulate|
										aiProcess_SortByPType);
		if (!scene) return;
		std::vector< float > vertices;
		std::vector< float > uvs;
		std::vector< float > normals;

		m_num_verts = 0;

		aiMesh* mesh = scene->mMeshes[0];
		int iMeshFaces = mesh->mNumFaces;
		for (int j = 0; j<iMeshFaces; ++j) {
			const aiFace& face = mesh->mFaces[j];
			for (int k = 0; k<3; ++k) {
				aiVector3D pos = mesh->mVertices[face.mIndices[k]];
				//aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];
				aiVector3D normal = mesh->HasNormals( ) ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);
				vertices.push_back(pos.x);
				vertices.push_back(pos.y);
				vertices.push_back(pos.z);
				//uvs.push_back(uv);
				normals.push_back(normal.x);
				normals.push_back(normal.y);
				normals.push_back(normal.z);
				++m_num_verts;
			}
		}
		
		glGenVertexArrays(1, uiVAO);
		glGenBuffers(2, uiVBO);
		// Setup whole cube
		glBindVertexArray(uiVAO[0]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(float), &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		mesh_loaded = true;
	}

	/*----------------------------------------------------------------------------
	UNloads any geometry loaded earlier.
	----------------------------------------------------------------------------*/
	void Mesh::Unload( ) {
		if (m_num_parents>0) return;

		if (mesh_loaded) {
			glDeleteBuffers(2, uiVBO);
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
			Load( );
			return;
		} else {

			++m_num_parents;
		}
		
	}

	void Mesh::OnParentBeingChilded( ) {
		//Honestly, we don't care.
	}
}