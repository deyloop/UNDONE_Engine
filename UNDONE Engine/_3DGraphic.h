/******************************************************************************
File	:	_3DGraphic.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#ifndef __3DGRAPHIC_H_
#define __3DGRAPHIC_H_

#include "GraphicalObject.h"	//the graphical Object header, the base class.
#include "WorldTransform.h"
#include "ShaderProgram.h"
#include "UNDONE_Engine_declr.h"

#include <glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

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
struct UNDONE_API _3DGraphic : public GraphicalObject {
public:
	_3DGraphic();
	~_3DGraphic(){ Release(); }

	virtual void Release();
	virtual void Render(RenderParams& refRenderParams);
	virtual void Render ( ) { };

	virtual void OnInit();
	virtual void OnDestroy();

	void operator= (_3DGraphic other);

	WorldTransform& GetWorldTransform() { return m_worldTransform; }
	ShaderProgram**  GetShaderProgram() { return m_ppShaderProgram; }
	
	void SetShaderProgramToUse(ShaderProgram** ppProgram);

protected:
	WorldTransform	m_worldTransform;
	ShaderProgram**	m_ppShaderProgram;

	float fPyramid[36]; // Data to render triangle (3 vertices, each has 3 floats)
	
	float fPyramidColor[36];

	UINT uiVBO[2];
	UINT uiVAO[1];
	//Mesh, WorldTransfor, ShaderPrograms, etc	
};
#endif
///////////////////////////////////////////////////////////////////////////////