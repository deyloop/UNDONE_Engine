/******************************************************************************
File	:	_3DGraphic.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "_3DGraphic.h"
#include<glm.hpp>
#include<gtx\projection.hpp>
#include<gtx\transform.hpp>
#include"SystemComponent.h"

/*-----------------------------------------------------------------------------
Default Constructor
-----------------------------------------------------------------------------*/
_3DGraphic::_3DGraphic(){
	m_ppShaderProgram = nullptr;
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
	// Setup pyramid

	// Front face
	fPyramid[0] = 0.0f; fPyramid[1] = 5.0f; fPyramid[2] = 0.0f;
	fPyramid[3] = -3.0f; fPyramid[4] = 0.0f; fPyramid[5] = 3.0f;
	fPyramid[6] = 3.0f; fPyramid[7] = 0.0f; fPyramid[8] = 3.0f;

	// Back face
	fPyramid[9] = 0.0f; fPyramid[10] = 5.0f; fPyramid[11] = 0.0f;
	fPyramid[12] = 3.0f; fPyramid[13] = 0.0f; fPyramid[14] = -3.0f;
	fPyramid[15] = -3.0f; fPyramid[16] = 0.0f; fPyramid[17] = -3.0f;

	// Left face
	fPyramid[18] = 0.0f; fPyramid[19] = 5.0f; fPyramid[20] = 0.0f;
	fPyramid[21] = -3.0f; fPyramid[22] = 0.0f; fPyramid[23] = -3.0f;
	fPyramid[24] = -3.0f; fPyramid[25] = 0.0f; fPyramid[26] = 3.0f;

	// Right face
	fPyramid[27] = 0.0f; fPyramid[28] = 5.0f; fPyramid[29] = 0.0f;
	fPyramid[30] = 3.0f; fPyramid[31] = 0.0f; fPyramid[32] = 3.0f;
	fPyramid[33] = 3.0f; fPyramid[34] = 0.0f; fPyramid[35] = -3.0f;

	// Setup pyramid color

	for (int i = 0; i < 4; i++)
	{
		fPyramidColor[i * 9] = 1.0f; fPyramidColor[i * 9 + 1] = 0.0f; fPyramidColor[i * 9 + 2] = 0.0f;
		if (i < 2)
		{
			fPyramidColor[i * 9 + 1] = 0.0f; fPyramidColor[i * 9 + 4] = 1.0f; fPyramidColor[i * 9 + 5] = 0.0f;
			fPyramidColor[i * 9 + 2] = 0.0f; fPyramidColor[i * 9 + 7] = 0.0f; fPyramidColor[i * 9 + 8] = 1.0f;
		}
		else
		{
			fPyramidColor[i * 9 + 2] = 0.0f; fPyramidColor[i * 9 + 7] = 1.0f; fPyramidColor[i * 9 + 8] = 0.0f;
			fPyramidColor[i * 9 + 1] = 0.0f; fPyramidColor[i * 9 + 4] = 0.0f; fPyramidColor[i * 9 + 5] = 1.0f;
		}
	}

	glGenVertexArrays(1, uiVAO);
	glGenBuffers(2, uiVBO);

	// Setup whole pyramid
	glBindVertexArray(uiVAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), fPyramid, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), fPyramidColor, GL_STATIC_DRAW);
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
	
	GLuint progID = ( *m_ppShaderProgram )->GetProgramID ( );
	
	glBindVertexArray(uiVAO[0]);
	
	int HMVP = glGetUniformLocation ( progID, "gMVP" );

	glm::mat4 mMVP = refRenderParams.View_x_Projection *
					(*(m_worldTransform.GetTransform( )));

	glUniformMatrix4fv(HMVP, 1, GL_FALSE, &mMVP[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 12);

}

/*-----------------------------------------------------------------------------
The = operator which copies the contents of other into this 
-----------------------------------------------------------------------------*/
void _3DGraphic::operator= (_3DGraphic other){
	//copy all pointers around.
	//Mesh, WorldTransfor, ShaderPrograms, etc

	m_worldTransform = other.m_worldTransform;
	m_ppShaderProgram = other.m_ppShaderProgram;
}

/*-----------------------------------------------------------------------------
Sets the shader program which must be used to render the graphic.
Parameters:
[IN]	pProgram	:	the pointer to the program to be used.
-----------------------------------------------------------------------------*/
void _3DGraphic::SetShaderProgramToUse(ShaderProgram** ppProgram){
	m_ppShaderProgram = ppProgram;
}

unsigned int SimpleObject::num_objects = 0;
#define _CRT_SECURE_NO_WARNINGS
/*-----------------------------------------------------------------------------
Default Constructor
-----------------------------------------------------------------------------*/
SimpleObject::SimpleObject(){
	num_objects++;
	sprintf_s(name, "Object_%i", num_objects);
}
