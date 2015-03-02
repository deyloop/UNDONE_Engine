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
	struct UNDONE_API Mesh : public Component {
		Mesh( );
		~Mesh( ) { Release( ); }

		
		void Load( );
		
		void Render( );
	
		void Unload( );
		void Release( );

		void OnParentBeingChilded( );
	
	private:
		void OnParentSet( );
		
		UINT uiVBO[2];
		UINT uiVAO[1];
		
		UINT m_num_parents;
		
		bool	mesh_loaded;
		int		m_instances;
		static UINT currently_bound_VAO;
	};
}
#endif