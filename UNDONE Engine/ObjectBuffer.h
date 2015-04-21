/*-----------------------------------------------------------------------------
File	:	ObjectBuffer.h
Author	:	Anurup Dey.
-----------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef _OBJECTBUFFER_H_
#define _OBJECTBUFFER_H_

#include <vector>
#include <list>
#include "SimpleObject.h"
#include "GraphicalObject.h"
#include "_3DGraphic.h"
//#include "../Objects/GraphicalObject/_2DGraphic/"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "UNDONE_Engine_declr.h"
using namespace std;

/*-----------------------------------------------------------------------------
Object buffer is generally a memory manager, you may say. It keeps all concerned
object components at one place, managing memory and contiguity.
-----------------------------------------------------------------------------*/
/*
class ObjectBuffer{
public:	
	ObjectBuffer();
	~ObjectBuffer(){ DeleteAllObjects(); }

	_3DGraphic**		CreateNew3DGraphic();

	Shader**			CreateNewShader();
	ShaderProgram**		CreateNewShaderProgram();

	vector<SimpleObject*>	GetSimpleObjects()	{ return m_SimpleObjects; }
	vector<GraphicalObject*>GetObjectsToDraw()	{ return m_GraphicalObjects; }
	vector<_3DGraphic>&		Get3DObjectsToDraw(){ return m_3DGraphics; }
	Camera&					GetControlCamera( ) { return m_ControlCamera; }

	
	void RemoveObject(_3DGraphic** obj);

	void DeleteShader(Shader** shader);
	void DeleteShaderProgram(ShaderProgram** prog);

	void DeleteAllObjects();

private:
	void AddGraphicalObject(GraphicalObject* obj);
	void AddSimpleObject(SimpleObject* obj);

	void RemoveObject(SimpleObject* obj);
	void RemoveObject(GraphicalObject* obj);

	vector<SimpleObject*>		m_SimpleObjects;
	vector<GraphicalObject*>	m_GraphicalObjects;
	vector<_3DGraphic>			m_3DGraphics;

	vector<Shader>				m_Shaders;
	vector<ShaderProgram>		m_ShaderPrograms;

	list<_3DGraphic*>			m_3DGraphicList;

	list<Shader*>				m_ShaderList;
	list<ShaderProgram*>		m_ShaderProgramList;

	Camera						m_ControlCamera;

};
*/
#endif