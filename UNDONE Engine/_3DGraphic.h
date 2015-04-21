/******************************************************************************
File	:	_3DGraphic.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#ifndef __3DGRAPHIC_H_
#define __3DGRAPHIC_H_

#include "Component.h"			//_3DGraphic IS A Component
#include "GraphicalObject.h"	//the graphical Object header, the base class.
#include "WorldTransform.h"
#include "Mesh.h"
#include "GraphicMaterial.h"
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
	struct _3DGraphic : public GraphicalObject, public Component {
	public:
		UNDONE_API _3DGraphic( );
		UNDONE_API~_3DGraphic( ) { Release( ); }

		UNDONE_API virtual void Release( );
		UNDONE_API virtual void Render(RenderParams& refRenderParams);
		virtual void Render( ) { };

		UNDONE_API virtual void Load( );
		UNDONE_API virtual void Unload( );

		UNDONE_API void OnParentBeingChilded( );

		void OnInit( ) { };
		void OnDestroy( ) { };

	protected:
		DPointer<WorldTransform>	m_ppworldTransform;
		DPointer<Mesh>				m_ppMesh;
		DPointer<GraphicMaterial>	m_ppMaterial;

		UNDONE_API void OnParentSet( );
	};
}
#endif
///////////////////////////////////////////////////////////////////////////////