/******************************************************************************
File	:	Application.cpp
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
#include "Application.h"
#include "Maze.h"

#include <glew.h>

#include <UNDONE_DEBUG.h>

#include <ctime>

/*-----------------------------------------------------------------------------
Default Contructor
-----------------------------------------------------------------------------*/
Application::Application(){
	m_pFrameWork			= nullptr;
	m_cam.m_pointer		    = nullptr;
	BlockGroup.m_pointer	= nullptr;
	initialized				= false;
}

/*-----------------------------------------------------------------------------
Default destructor
------------------------------------------------------------------------------*/
void Application::Release(){
	if (initialized) {
		initialized = false;
	}
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
void Application::LoadScene(unObjectBuffer* pObjectBuffer){
	
	pObjectBuffer->SetInitAllocSize(500);
	
	
	Dptr<unShader> shVertex			= pObjectBuffer->CreateNew_Shader();
	Dptr<unShader> shFragment			= pObjectBuffer->CreateNew_Shader();
	Dptr<unShaderProgram> spMain		= pObjectBuffer->CreateNew_ShaderProgram();
	Dptr<unMesh> cube_mesh			= pObjectBuffer->CreateNew_Mesh( );
	Dptr<unMesh> monkey_mesh			= pObjectBuffer->CreateNew_Mesh( );

	Dptr<unGraphicMaterial> Redmaterial	= pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Bluematerial	= pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Greenmaterial = pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Yellowmaterial= pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Pinkmaterial	= pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unTexture> tex = pObjectBuffer->CreateNew_Texture();
    Dptr<unTexture> tex2 = pObjectBuffer->CreateNew_Texture( );

	monkey_mesh->SetModelFile("monkey.obj");
	tex->SetTexture2D("Test_Texture.jpg", true);
    tex2->SetTexture2D( "HOUSE.jpg", true );
	tex->Load();
	tex2->Load();
	shVertex->LoadShader("shader.vert", GL_VERTEX_SHADER);
	shFragment->LoadShader("shader.frag", GL_FRAGMENT_SHADER);
	spMain->AddShaderToProgram(shVertex.ptr());
	spMain->AddShaderToProgram(shFragment.ptr());

	Redmaterial		->	SetShaderProgramToUse(spMain);
	Greenmaterial	->	SetShaderProgramToUse(spMain);
	Yellowmaterial	->	SetShaderProgramToUse(spMain);
	Pinkmaterial	->	SetShaderProgramToUse(spMain);
	Bluematerial	->	SetShaderProgramToUse(spMain);
	
	Bluematerial	->	SetDiffuseColor(0.0f, 0.0f, 1.0f);
	Redmaterial		->	SetDiffuseColor(1.0f, 0.0f, 0.0f);
	Greenmaterial	->	SetDiffuseColor(0.0f, 1.0f, 0.0f);
	Yellowmaterial	->	SetDiffuseColor(1.0f, 1.0f, 0.0f);
	Pinkmaterial	->	SetDiffuseColor(1.0f, 0.0f, 127.0f/255.0f);

    Bluematerial	->	AddTexture(tex,0);
    Redmaterial		->	AddTexture(tex,0);
    Greenmaterial	->	AddTexture(tex,0);
    Yellowmaterial	->	AddTexture(tex2,0);
    Pinkmaterial	->	AddTexture(tex,0);

	vector<Dptr<unGraphicMaterial>> material;
	material.reserve(5);

	material.push_back(Redmaterial);
	material.push_back(Bluematerial);
	material.push_back(Greenmaterial);
	material.push_back(Yellowmaterial);
	material.push_back(Pinkmaterial);


	Dptr<unGraphic2D> _2dgraphic = pObjectBuffer->CreateNew_Graphic2D( );
	Dptr<unGameObject> _2dobj = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unWorldTransform> _2dtrans = pObjectBuffer->CreateNew_WorldTransform( );
	_2dtrans->TranslateAbs(-1.0f, -1.f, 0.0f);
    _2dtrans->ScaleAbs( 0.5, 0.5, 1.0f );
	_2dgraphic->SetTexture(tex);
	//_2dtrans->RotateAbs(0.0f, 0.0f, 45.0f);
	
	rect m;
	m.x = 1.0f;
	m.y = 1.0f;
	m.hieght = 0.5f;
	m.width = 1.0f;

	(_2dgraphic.ptr())->SetImageRect(m);

	_2dobj->AddWorldTransform(_2dtrans);
	_2dobj->AddGraphic2D(_2dgraphic);
	_2dobj->Load();

	srand((unsigned int)time(0));

	BlockGroup = pObjectBuffer->CreateNew_GameObject( );
	BlockGroup2 = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unWorldTransform>	grouTrans2	= pObjectBuffer->CreateNew_WorldTransform( );
	Dptr<unWorldTransform>	grouTrans	= pObjectBuffer->CreateNew_WorldTransform( );
	BlockGroup	->	AddWorldTransform(grouTrans2);
	BlockGroup2	->	AddWorldTransform(grouTrans);
	grouTrans	->	TranslateRel(10.0f, 0.0f, 20.0f);
	BlockGroup	->	AddGameObject(BlockGroup2);
	
#define SIZE 2

	Maze maze;
	maze.Generate(SIZE);

	for (int j = 0; j<SIZE; ++j) {
		for (int i = 0;i<SIZE; ++i) {

			//if (maze.data[i+j*SIZE] == SPACE) continue;

			Dptr<unGameObject> go_scene		= pObjectBuffer->CreateNew_GameObject( );
			Dptr<unWorldTransform> transform1 = pObjectBuffer->CreateNew_WorldTransform( );
			Dptr<unGraphic3D> graphic1		= pObjectBuffer->CreateNew_Graphic3D( );
			
			go_scene	->	Rename((string	("GameObject")	+i+j).c_str());
			transform1	->	Rename((string	("Transform" )	+i+j).c_str());
			graphic1	->	Rename((string	( "Graphic"	 )	+i+j).c_str());
			
			go_scene->AddWorldTransform(transform1);
			go_scene->AddMesh(cube_mesh);
			go_scene->AddGraphicMaterial(material.at(rand()%5));
			go_scene->AddGraphic3D(graphic1);
			
			transform1->TranslateAbs((float)i, 0,(float)j);
			transform1->ScaleAbs(0.5f, (float)1, 0.5f);

			BlockGroup2->AddGameObject(go_scene);
		}
	}
	
	BlockGroup->Load();

	cu = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unWorldTransform>	ct = pObjectBuffer->CreateNew_WorldTransform( );
	Dptr<unGraphic3D>		cg = pObjectBuffer->CreateNew_Graphic3D( );
	//ct->ScaleRel( -0.01f, -0.01f, 0.01f );
    cu->AddWorldTransform(ct);
    
	cu->AddMesh(monkey_mesh);//change to monkey later
	cu->AddGraphicMaterial(Yellowmaterial);
	cu->AddGraphic3D(cg);
	Dptr<unBehaviorAttachement> att = pObjectBuffer->CreateNew_BehaviorAttachement( );
	cu->AddBehaviorAttachement( att );
	att->AddBehavior( "bro", &broscript );
	cu->Load();

	
	
	m_cam = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unWorldTransform> camtransform = pObjectBuffer->CreateNew_WorldTransform( );
	Dptr<unCamera> cam = pObjectBuffer->GetControlCamera( );
	Dptr<unBehaviorAttachement> batt = pObjectBuffer->CreateNew_BehaviorAttachement( );

	m_cam->AddWorldTransform( camtransform );
	m_cam->AddCamera( cam );
	m_cam->AddBehaviorAttachement( batt );
	batt->AddBehavior( "camscript", &camscrpt );
	m_cam->Load();

	cu->GetWorldTransform( )->ScaleAbs( 0.5, 0.5, 0.5 );
	camtransform->TranslateAbs( 0, 2, -3 );
	camscrpt.target = cu;


	InputEvent ExitEvent;
	InputEvent RightKey, LeftKey;
	InputEvent MonkeyMoveF, MonkeyMoveB, MonkeyTurnLeft, MonkeyTurnRight;

	MonkeyMoveF.event.type = EVENT_KEYPRESS;
	MonkeyMoveF.key.keycode = KEY_ARROW_UP;
	InputPair pairMF(MonkeyMoveF,"Move Forward");

	MonkeyMoveB.event.type = EVENT_KEYPRESS;
	MonkeyMoveB.key.keycode = KEY_ARROW_DOWN;
	InputPair pairMB( MonkeyMoveB, "Move Back");

	MonkeyTurnLeft.event.type = EVENT_KEYPRESS;
	MonkeyTurnLeft.key.keycode = KEY_ARROW_LEFT;
	InputPair pairML( MonkeyTurnLeft, "Turn Left");

	MonkeyTurnRight.event.type = EVENT_KEYPRESS;
	MonkeyTurnRight.key.keycode = KEY_ARROW_RIGHT;
	InputPair pairMR( MonkeyTurnRight, "Turn Right");

	RightKey.event.type = EVENT_KEYPRESS;
	RightKey.key.keycode = KEY_D;
	InputPair pairR( RightKey, "Rotate Right");

	LeftKey.event.type = EVENT_KEYPRESS;
	LeftKey.key.keycode = KEY_A;
	InputPair pairL( LeftKey, "Rotate Left");
	
	ExitEvent.event.type		= EVENT_KEYDOWN;
	ExitEvent.key.keycode		= KEY_ESCAPE;
	InputPair pair( ExitEvent, "Exit");
	
	InputContext monkeycontrolcontext;
	monkeycontrolcontext.m_name = "monkey_movement";
	monkeycontrolcontext.m_pairs.push_back(pair);
	monkeycontrolcontext.m_pairs.push_back( pairL );
	monkeycontrolcontext.m_pairs.push_back( pairMR );
	monkeycontrolcontext.m_pairs.push_back( pairMF );
	monkeycontrolcontext.m_pairs.push_back( pairML );
	monkeycontrolcontext.m_pairs.push_back( pairMB );
	monkeycontrolcontext.m_pairs.push_back( pairR );

	m_pFrameWork->Input->AddContext(monkeycontrolcontext);
	m_pFrameWork->Input->ActivateContext("monkey_movement");

	m_pFrameWork->Input->RegisterCallback([=]{SystemComponent::GetInstance()->Post_Quit_Mesage( 0 ); },"Exit");
	initialized = true;
}

/*-----------------------------------------------------------------------------
Updates Application specific things like AI, ui response, etc.
-----------------------------------------------------------------------------*/
void Application::Update(){
	camscrpt.Update( );
	//BlockGroup2->GetWorldTransform()->RotateRel(0,0.5,0 );
	//BlockGroup->GetWorldTransform()->RotateRel(0,-0.7,0 );
}

/*-----------------------------------------------------------------------------
Links this application to the GAme Engine Object, so that they can communicate.
Parameters:
[IN]	pFrameWork	-	the pointer to the Engine to be linked to.
------------------------------------------------------------------------------*/
void Application::LinkToEngine(UnFramework* pFrameWork){
	m_pFrameWork = pFrameWork;
}