/******************************************************************************
File	:	Graphic3D.h
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
#ifndef __3DGRAPHIC_H_
#define __3DGRAPHIC_H_

#include "Component.h"			//Graphic3D IS A Component
#include "WorldTransform.h"
#include "Mesh.h"
#include "GraphicMaterial.h"
#include "unGraphic3D.h"
#include "UNDONE_Engine_declr.h"


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
	class Graphic3D : public unGraphic3D, public Component{
	public:
		Graphic3D( );
		~Graphic3D( ) { Release( ); }

		void Release( );
		void Render(RenderParams& refRenderParams);
		void Render( ) { };

		void Load( );
		void Unload( );

		void OnParentAdopted( );
		void OnOrphaned( );

		void OnInit( ) { };
		void OnDestroy( ) { };

	protected:
		Dptr<WorldTransform>	m_ppworldTransform;
		Dptr<Mesh>				m_ppMesh;
		Dptr<GraphicMaterial>	m_ppMaterial;

		void OnParentSet( );
	};
}
#endif
///////////////////////////////////////////////////////////////////////////////