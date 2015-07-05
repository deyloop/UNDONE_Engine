/******************************************************************************
File	:	Graphic3D.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#ifndef __3DGRAPHIC_H_
#define __3DGRAPHIC_H_

#include "Component.h"			//Graphic3D IS A Component
#include "GraphicalObject.h"	//the graphical Object header, the base class.
#include "WorldTransform.h"
#include "Mesh.h"
#include "GraphicMaterial.h"
#include "unGraphic3D.h"
#include "UNDONE_Engine_declr.h"

#include <glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

namespace UNDONE_ENGINE {

	/*-----------------------------------------------------------------------------
	This struct represents data that is passed on to each 3d graphic on rendering.
	-----------------------------------------------------------------------------*/
	struct RenderParams {
		glm::mat4 View_x_Projection;
	};

	/*-----------------------------------------------------------------------------
	This class represents a 3D graphical Object. Inherits most of its props
	from the GraphicalObject. NOTE: All 3D graphics behave alike.
	-----------------------------------------------------------------------------*/
	class Graphic3D : public Component , public unGraphic3D{
	public:
		Graphic3D( );
		~Graphic3D( ) { Release( ); }

		void Release( );
		void Render(RenderParams& refRenderParams);
		void Render( ) { };

		void Load( );
		void Unload( );

		void OnParentBeingChilded( );

		void OnInit( ) { };
		void OnDestroy( ) { };

	protected:
		DPointer<WorldTransform>	m_ppworldTransform;
		DPointer<Mesh>				m_ppMesh;
		DPointer<GraphicMaterial>	m_ppMaterial;

		void OnParentSet( );
	};
}
#endif
///////////////////////////////////////////////////////////////////////////////