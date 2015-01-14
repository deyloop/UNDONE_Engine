/******************************************************************************
File	:	Application.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Application.h"
#include <iostream>

/*-----------------------------------------------------------------------------
Default Contructor
-----------------------------------------------------------------------------*/
Application::Application(){
	m_pFrameWork = nullptr;
	m_pcam = nullptr;
}

/*-----------------------------------------------------------------------------
Default destructor
------------------------------------------------------------------------------*/
void Application::Release(){
	//Again, nothing to do yet.
}

/*-----------------------------------------------------------------------------
Summary:	This function is called by the framework while initialising. Its
			called only at the begining of the runing of the application.
			It is reqiured that the application defines some scene related
			specifications which are reqiured to start the rendering process
			, in this function. These requirements include:
			- defining the screen layout,
			- predine what objects are to be drawn on the screen.
Parameters:
[in,out]	*object_buffer	- The empty Object Buffer to be used in this app
							  and which has to be pre- filled. (pointer)
-------------------------------------------------------------------------------*/
void Application::LoadScene(ObjectBuffer* pObjectBuffer){
	

	

	Shader** shVertex		= pObjectBuffer->CreateNewShader();
	Shader** shFragment		= pObjectBuffer->CreateNewShader();
	ShaderProgram** spMain	= pObjectBuffer->CreateNewShaderProgram();

	(*shVertex)->LoadShader("shader.vert", GL_VERTEX_SHADER);
	(*shFragment)->LoadShader("shader.frag", GL_FRAGMENT_SHADER);

	(*spMain)->CreateProgram();
	(*spMain)->AddShaderToProgram(*shVertex);
	(*spMain)->AddShaderToProgram(*shFragment);

	(*spMain)->LinkProgram();
	(*spMain)->UseProgram();

	_3DGraphic* obj = *pObjectBuffer->CreateNew3DGraphic();
	obj->SetShaderProgramToUse(spMain);
	obj->OnInit();
	_3DGraphic* obj2 = *pObjectBuffer->CreateNew3DGraphic( );
	obj2->SetShaderProgramToUse(spMain);
	obj2->OnInit( );
	//obj2->GetWorldTransform( ).SetYPosition(3.0f);
	obj2->GetWorldTransform( ).SetZPosition(4.0f);
	obj2->GetWorldTransform( ).SetXPosition(4.0f);

	pObjectBuffer->GetControlCamera( ).SetPosition(glm::vec3(10.0f, 10.0f, 10.0f));
	pObjectBuffer->GetControlCamera( ).SetLookAt(glm::vec3(0.0f));
	m_pcam = &(pObjectBuffer->GetControlCamera( ));

	Command* YawLeft = new LeftYawCommand( );
	Command* YawRight = new RightYawCommand( );
	InputEvent KeyEvent;
	KeyEvent.event.type = EVENT_KEYBOARD;
	InputPair pair(KeyEvent, *YawLeft);

	vector<InputContext>& contexts = m_pFrameWork->GetInputContextListForEditing( );
	InputContext cameracontrolcontext;
	cameracontrolcontext.m_pControl = m_pcam;
	cameracontrolcontext.m_pairs.push_back(pair);
	contexts.push_back(cameracontrolcontext);
}

/*-----------------------------------------------------------------------------
Updates Application specific things like AI, ui response, etc.
-----------------------------------------------------------------------------*/
void Application::Update(){

	
	
	//m_pcam->Yaw(0.01f);
	m_pcam->Update( );
	
}

/*-----------------------------------------------------------------------------
Links this application to the GAme Engine Object, so that they can communicate.
Parameters:
[IN]	pFrameWork	-	the pointer to the Engine to be linked to.
------------------------------------------------------------------------------*/
void Application::LinkToEngine(FrameWork* pFrameWork){
	m_pFrameWork = pFrameWork;
}