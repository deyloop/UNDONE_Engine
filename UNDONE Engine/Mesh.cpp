/******************************************************************************
Project	:	UNDONE Engine
File	:	Mesh.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Mesh.h"

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
		//Define Cube verts.
#define vA 0.0f,0.0f,0.0f
#define vB 1.0f,0.0f,0.0f
#define vC 0.0f,1.0f,0.0f
#define vD 1.0f,1.0f,0.0f
#define vE 1.0f,0.0f,-1.0f
#define vF 1.0f,1.0f,-1.0f
#define vG 0.0f,0.0f,-1.0f
#define vH 0.0f,1.0f,-1.0f
		float fCube[90] = {
			vA, vB, vC,
			vC, vB, vD,
			vD, vB, vE,
			vD, vE, vF,
			vF, vE, vG,
			vF, vG, vH,
			vH, vG, vA,
			vA, vC, vH,
			vC, vF, vH,
			vC, vD, vF
		};

		//Define the normals
#define nU 0.0f,1.0f,0.0f
#define nD 0.0f,-1.0f,0.0f
#define nL -1.0f,0.0f,0.0f
#define nR 1.0f,0.0f,0.0f
#define nF 0.0f,0.0f,1.0f
#define nB 0.0f,0.0f,-1.0f
		float fNormals[90] = {
			nF, nF, nF,
			nF, nF, nF,
			nR, nR, nR,
			nR, nR, nR,
			nB, nB, nB,
			nB, nB, nB,
			nL, nL, nL,
			nL, nL, nL,
			nU, nU, nU,
			nU, nU, nU
		};

		glGenVertexArrays(1, uiVAO);
		glGenBuffers(2, uiVBO);
		// Setup whole cube
		glBindVertexArray(uiVAO[0]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, 90*sizeof(float), fCube, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, 90*sizeof(float), fNormals, GL_STATIC_DRAW);
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
		
		glDrawArrays(GL_LINE_STRIP, 0, 30);
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