/******************************************************************************
Project	:	UNDONE Engine
File	:	Mesh.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Mesh.h" 
#include "UNDONE_DEBUG.h"
#include <glm.hpp>


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

		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > vertices;
		std::vector< glm::vec2 > uvs;
		std::vector< glm::vec3 > normals;

		FILE* file; 
		fopen_s(&file, m_model_file.c_str( ), "r");
		if (file==nullptr) {
			coutput("Unable to open mesh file: "+m_model_file.c_str( )+"\n");
			return;
		}
		while (1) {

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf_s(file, "%s", lineHeader,128);
			if (res==EOF)
				break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader

			if (strcmp(lineHeader, "v")==0) {
				glm::vec3 vertex;
				fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);
			} else if (strcmp(lineHeader, "vt")==0) {
				glm::vec2 uv;
				fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
				uvs.push_back(uv);
			} else if (strcmp(lineHeader, "vn")==0) {
				glm::vec3 normal;
				fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);
			} else if (strcmp(lineHeader, "f")==0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf_s(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0] ,&normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
				if (matches!=6) {
					printf("File can't be read by our simple parser : ( Try exporting with other options)\n");
					return;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				/*
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				*/
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		vector<glm::vec3> verts;
		vector<glm::vec3> vnormals;
		// For each vertex of each triangle
		for (unsigned int i = 0; i<vertexIndices.size( ); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = vertices[vertexIndex-1];
			verts.push_back(vertex);
		}

		for (unsigned int i = 0; i<normalIndices.size( ); i++) {
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = normals[normalIndex-1];
			vnormals.push_back(normal);
		}


		m_num_verts = verts.size( );

		glGenVertexArrays(1, uiVAO);
		glGenBuffers(2, uiVBO);
		// Setup whole cube
		glBindVertexArray(uiVAO[0]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(float)*3, &verts[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, vnormals.size()*sizeof(float)*3, &vnormals[0], GL_STATIC_DRAW);
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