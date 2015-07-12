/******************************************************************************
Project	:	UNDONE Engine
File	:	Mesh.h
Author	:	Anurup Dey
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
using std::string;

typedef  unsigned int UINT;

namespace UNDONE_ENGINE {
	/*----------------------------------------------------------------------------
	A Mesh data structure holds data about geometry. Must be used in conjuction
	with a Graphic3D Compnent to work properly.
	----------------------------------------------------------------------------*/
	class Mesh : public Component, public unMesh {
	public:
		Mesh( );
		~Mesh( ) { Release( ); }

		void SetModelFile(const char* filename) {
			m_model_file = filename; 
		};
		
		void Load( );
		
		void Render( );
	
		void Unload( );
		void Release( );

		void OnParentBeingChilded( );

		static void SetCurrentlyBoundVAO(UINT uiVAOID) { currently_bound_VAO = uiVAOID; };
	
	private:
		void OnParentSet( );
		
		UINT uiVBO[2];
		UINT uiVAO[1];
		
		UINT m_num_parents;
		
		bool		mesh_loaded;
		int			m_instances;
		string		m_model_file;
		unsigned	m_num_verts;
		static UINT currently_bound_VAO;
	};
}
#endif