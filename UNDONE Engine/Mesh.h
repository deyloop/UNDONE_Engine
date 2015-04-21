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
#include "UNDONE_Engine_declr.h"

#include "Component.h"		//Mesh IS a component 			
#include <glew.h>			//used for the VAOs and the VBOs
#include <gl\GL.h>
#include <gl\GLU.h>

   


typedef  unsigned int UINT;

namespace UNDONE_ENGINE {
	/*----------------------------------------------------------------------------
	A Mesh data structure holds data about geometry. Must be used in conjuction
	with a _3DGraphic Compnent to work properly.
	----------------------------------------------------------------------------*/
	struct Mesh : public Component {
		UNDONE_API Mesh( );
		UNDONE_API ~Mesh( ) { Release( ); }

		UNDONE_API void SetModelFile(string filename) { m_model_file = filename; };
		
		UNDONE_API void Load( );
		
		void Render( );
	
		UNDONE_API void Unload( );
		void Release( );

		UNDONE_API void OnParentBeingChilded( );

		static void SetCurrentlyBoundVAO(UINT uiVAOID) { currently_bound_VAO = uiVAOID; };
	
	private:
		UNDONE_API void OnParentSet( );
		
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