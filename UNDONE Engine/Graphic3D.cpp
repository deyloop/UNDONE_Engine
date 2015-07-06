/******************************************************************************
File	:	Graphic3D.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Graphic3D.h"
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
	Graphic3D::Graphic3D( ) {
		m_ppMaterial.m_pointer = nullptr;
		m_ppworldTransform.m_pointer = nullptr;
		m_ppMesh.m_pointer = nullptr;

	}

	/*------------------------------------------------------------------------------
	Default destructor
	-----------------------------------------------------------------------------*/
	void Graphic3D::Release( ) {

	}

	/*-----------------------------------------------------------------------------
	 Initialize all the graphical resources here.
	 -----------------------------------------------------------------------------*/
	void Graphic3D::Load( ) {

	}

	/*-----------------------------------------------------------------------------
	Release all Graphical resources here.
	-----------------------------------------------------------------------------*/
	void Graphic3D::Unload( ) {

	}

	/*-----------------------------------------------------------------------------
	Renders the _3Dgraphic on the screen.
	-----------------------------------------------------------------------------*/
	void Graphic3D::Render(RenderParams& refRenderParams) {
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
	void Graphic3D::OnParentSet( ) {

		m_ppworldTransform = m_ppParent->GetComponent<WorldTransform>();
		m_ppMesh = m_ppParent->GetComponent<Mesh>();
		m_ppMaterial = m_ppParent->GetComponent< GraphicMaterial>();

		coutput(name+" aquired transformation "+m_ppworldTransform.Obj( ).name+"\n");
		coutput(name+" aquired mesh "+m_ppMesh.Obj( ).name+"\n");
		coutput(name+" aquired material "+m_ppMaterial.Obj( ).name+"\n");

	}

	void Graphic3D::OnParentBeingChilded( ) {
		//We Do Nothing...
	}

	

	
}

///////////////////////////////////////////////////////////////////////////////