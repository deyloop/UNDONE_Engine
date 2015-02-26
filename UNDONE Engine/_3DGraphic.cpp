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
	glBufferData(GL_ARRAY_BUFFER, 90 * sizeof(float), fCube, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 90 * sizeof(float), fNormals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

/*-----------------------------------------------------------------------------
This callback function is called when the context is deleted. Release all 
Graphical resources here.
-----------------------------------------------------------------------------*/
void _3DGraphic::OnDestroy(){
	glDeleteBuffers(2, uiVBO);
	glDeleteVertexArrays(1, uiVAO);
}

/*-----------------------------------------------------------------------------
Renders the _3Dgraphic on the screen.
-----------------------------------------------------------------------------*/
void _3DGraphic::Render(RenderParams& refRenderParams){
	if (m_ppShaderProgram.m_pointer && m_ppworldTransform.m_pointer) {
		GLuint progID = (m_ppShaderProgram.ptr( ))->GetProgramID( );

		glBindVertexArray(uiVAO[0]);
		
		int HMVP = glGetUniformLocation(progID, "gMVP");
		m_ppworldTransform.Obj( ).RotateRel(0.0f, 0.1f, 0.0f);
		glm::mat4 mMVP = refRenderParams.View_x_Projection*
			(m_ppworldTransform.ptr( )->GetTransform( ));

		glUniformMatrix4fv(HMVP, 1, GL_FALSE, &mMVP[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 30);
	
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
		coutput(name+" aquiring transformation from "+m_ppParent.Obj( ).name+"\n");
		m_ppworldTransform = (m_ppParent.ptr( ))->GetComponent<WorldTransform>( );
		coutput(name+" aquired transformation "+m_ppworldTransform.Obj( ).name+"\n");
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