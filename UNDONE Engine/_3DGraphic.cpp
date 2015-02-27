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


/*-----------------------------------------------------------------------------
Default Constructor
-----------------------------------------------------------------------------*/
_3DGraphic::_3DGraphic(){
	m_ppShaderProgram.m_pointer		= nullptr;
	m_ppworldTransform.m_pointer	= nullptr;
	m_ppMesh.m_pointer				= nullptr;
	
}

/*------------------------------------------------------------------------------
Default destructor
-----------------------------------------------------------------------------*/
void _3DGraphic::Release(){

}

/*-----------------------------------------------------------------------------
This callback function is called when the Context is created. Initialize all
the graphical resources here.
-----------------------------------------------------------------------------*/
void _3DGraphic::OnInit(){

}

/*-----------------------------------------------------------------------------
This callback function is called when the context is deleted. Release all 
Graphical resources here.
-----------------------------------------------------------------------------*/
void _3DGraphic::OnDestroy(){

}

/*-----------------------------------------------------------------------------
Renders the _3Dgraphic on the screen.
-----------------------------------------------------------------------------*/
void _3DGraphic::Render(RenderParams& refRenderParams){
	if (m_ppShaderProgram.m_pointer && 
		m_ppworldTransform.m_pointer &&
		m_ppMesh.m_pointer) {
		
		m_ppShaderProgram.ptr( )->UseProgram( );
		GLuint progID = (m_ppShaderProgram.ptr( ))->GetProgramID( );

		int HMVP = glGetUniformLocation(progID, "gMVP");
		int HWORLD = glGetUniformLocation(progID, "gWorld");
		//m_ppworldTransform.Obj( ).RotateRel(0.0f, 0.1f, 0.1f);
		glm::mat4 mMVP = refRenderParams.View_x_Projection*
			(m_ppworldTransform.ptr( )->GetTransform( ));
		
		glUniformMatrix4fv(HMVP, 1, GL_FALSE, &mMVP[0][0]);
		glUniformMatrix4fv(HWORLD, 1, GL_FALSE, &(m_ppworldTransform.Obj( ).GetTransform( ))[0][0]);
		m_ppMesh.ptr( )->Render( );
	
	}

}

/*-----------------------------------------------------------------------------
Sets the shader program which must be used to render the graphic.
Parameters:
[IN]	pProgram	:	the pointer to the program to be used.
-----------------------------------------------------------------------------*/
void _3DGraphic::SetShaderProgramToUse(DPointer<ShaderProgram> ppProgram){
	m_ppShaderProgram = ppProgram;
	if (m_ppShaderProgram.m_pointer!=nullptr) {
		coutput(name+" aquired Shader Program\n");
	}
}

/*-----------------------------------------------------------------------------
Sets the parent of this 3dGraphic Component.
-----------------------------------------------------------------------------*/
void _3DGraphic::SetParent(DPointer<GameObject> ppParent) {
	Component::SetParent(ppParent);
	if (m_ppParent.m_pointer) {
		m_ppworldTransform = (m_ppParent.ptr( ))->worldTransform;
		m_ppMesh = (m_ppParent.ptr( )->mesh);
		coutput(name+" aquired transformation "+m_ppworldTransform.Obj( ).name+"\n");
		coutput(name+" aquired mesh "+m_ppMesh.Obj( ).name+"\n");
	}
}
unsigned int SimpleObject::num_objects = 0;
/*-----------------------------------------------------------------------------
Default Constructor
-----------------------------------------------------------------------------*/
SimpleObject::SimpleObject(){
	
}




string operator +(string lhs, int rhs) {
	char numstr[20];
	sprintf_s(numstr, "%i", rhs);
	return lhs+numstr;
}

string operator +(string lhs, float rhs) {
	char numstr[20];
	sprintf_s(numstr, "%f", rhs);
	return lhs+numstr;
}