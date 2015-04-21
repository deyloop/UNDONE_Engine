/******************************************************************************
File	:	_3DGraphic.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "_3DGraphic.h"
#include "GameObject.h"
#include<glm.hpp>
#include<gtx\projection.hpp>
#include<gtx\transform.hpp>
#include "UNDONE_DEBUG.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
unsigned int SimpleObject::num_objects = 0;
/*-----------------------------------------------------------------------------
Default Constructor
-----------------------------------------------------------------------------*/
SimpleObject::SimpleObject( ) {

}

namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	Default Constructor
	-----------------------------------------------------------------------------*/
	_3DGraphic::_3DGraphic( ) {
		m_ppMaterial.m_pointer = nullptr;
		m_ppworldTransform.m_pointer = nullptr;
		m_ppMesh.m_pointer = nullptr;

	}

	/*------------------------------------------------------------------------------
	Default destructor
	-----------------------------------------------------------------------------*/
	void _3DGraphic::Release( ) {

	}

	/*-----------------------------------------------------------------------------
	 Initialize all the graphical resources here.
	 -----------------------------------------------------------------------------*/
	void _3DGraphic::Load( ) {

	}

	/*-----------------------------------------------------------------------------
	Release all Graphical resources here.
	-----------------------------------------------------------------------------*/
	void _3DGraphic::Unload( ) {

	}

	/*-----------------------------------------------------------------------------
	Renders the _3Dgraphic on the screen.
	-----------------------------------------------------------------------------*/
	void _3DGraphic::Render(RenderParams& refRenderParams) {
		if (m_ppMaterial.m_pointer &&
			m_ppworldTransform.m_pointer &&
			m_ppMesh.m_pointer) {

			glm::mat4 Transform = m_ppworldTransform->GetTransform( );
			glm::mat4 mMVP = refRenderParams.View_x_Projection*Transform;

			UniformDataInterface &MatData = m_ppMaterial->GetUniformDataInterface( );
			for (auto& uniform_data_pair:MatData.pairs) {
				switch (uniform_data_pair.uniformType) {
					case UNIFORMTYPE_MODELVIEWPROJECTIONMATRIX:
						uniform_data_pair.data.Data_fp = &mMVP[0][0];
						break;
					case UNIFORMTYPE_WORLDTRANSFORMATIONMATRIX:
						uniform_data_pair.data.Data_fp = &Transform[0][0];
						break;
				}
			}
			m_ppMaterial->ApplyMaterial( );

			m_ppMesh->Render( );

		}

	}

	/*-----------------------------------------------------------------------------
	Sets the parent of this 3dGraphic Component.
	-----------------------------------------------------------------------------*/
	void _3DGraphic::OnParentSet( ) {

		m_ppworldTransform = m_ppParent->worldTransform;
		m_ppMesh = m_ppParent->mesh;
		m_ppMaterial = m_ppParent->graphicMaterial;

		coutput(name+" aquired transformation "+m_ppworldTransform.Obj( ).name+"\n");
		coutput(name+" aquired mesh "+m_ppMesh.Obj( ).name+"\n");
		coutput(name+" aquired material "+m_ppMaterial.Obj( ).name+"\n");

	}

	void _3DGraphic::OnParentBeingChilded( ) {
		//We Do Nothing...
	}

	

	
}

///////////////////////////////////////////////////////////////////////////////