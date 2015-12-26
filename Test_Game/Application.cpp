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

#include <iostream>
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
	monkey_mesh->SetModelFile("monkey.obj");
	
	Dptr<unGraphicMaterial> Redmaterial	= pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Bluematerial	= pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Greenmaterial = pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Yellowmaterial= pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Pinkmaterial	= pObjectBuffer->CreateNew_GraphicMaterial( );
	Dptr<unTexture> tex = pObjectBuffer->CreateNew_Texture();
    Dptr<unTexture> tex2 = pObjectBuffer->CreateNew_Texture( );
	Dptr<unGraphic2D> _2dgraphic = pObjectBuffer->CreateNew_Graphic2D( );
	tex->SetTexture2D("Test_Texture.jpg", true);
    tex2->SetTexture2D( "HOUSE.jpg", true );
	_2dgraphic->SetTexture(tex);
	Dptr<unGameObject> _2dobj = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unWorldTransform> _2dtrans = pObjectBuffer->CreateNew_WorldTransform( );
	_2dtrans->TranslateAbs(-1.0f, -1.f, 0.0f);
    _2dtrans->ScaleAbs( 0.5, 0.5, 1.0f );
	//_2dtrans->RotateAbs(0.0f, 0.0f, 45.0f);
	
	rect m;
	m.x = 1.0f;
	m.y = 1.0f;
	m.hieght = 0.5f;
	m.width = 1.0f;

	(_2dgraphic.ptr())->SetImageRect(m);

	_2dobj.Obj().AddWorldTransform(_2dtrans);
	_2dobj->AddGraphic2D(_2dgraphic);
	
	shVertex->LoadShader("shader.vert", GL_VERTEX_SHADER);
	shFragment->LoadShader("shader.frag", GL_FRAGMENT_SHADER);

	spMain->CreateProgram();
	spMain->AddShaderToProgram(shVertex.ptr());
	spMain->AddShaderToProgram(shFragment.ptr());

	spMain->LinkProgram();
	
	Redmaterial	->Rename("RedMaterial");
	Bluematerial->Rename("BlueMaterial");
	
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
	
	cube_mesh->Rename("CubeMesh");
	
	vector<Dptr<unGraphicMaterial>> material;
	material.reserve(5);

	material.push_back(Redmaterial);
	material.push_back(Bluematerial);
	material.push_back(Greenmaterial);
	material.push_back(Yellowmaterial);
	material.push_back(Pinkmaterial);
	
	srand((unsigned int)time(0));

	BlockGroup = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unGameObject>		BlockGroup2 = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unWorldTransform>	grouTrans2	= pObjectBuffer->CreateNew_WorldTransform( );
	Dptr<unWorldTransform>	grouTrans	= pObjectBuffer->CreateNew_WorldTransform( );
	BlockGroup	->	AddWorldTransform(grouTrans2);
	BlockGroup2	->	AddWorldTransform(grouTrans);
	grouTrans	->	TranslateRel(10.0f, 0.0f, 0.0f);
	BlockGroup	->	AddGameObject(BlockGroup2);
	
#define SIZE 30
	Maze maze;
	maze.Generate(SIZE);

	for (int j = 0; j<SIZE; ++j) {
		for (int i = 0;i<SIZE; ++i) {

			if (maze.data[i+j*SIZE] == SPACE) continue;

			cout<<"\n";
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

	m_cam = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unWorldTransform> camtransform = pObjectBuffer->CreateNew_WorldTransform( );
	Dptr<unCamera> cam = pObjectBuffer->GetControlCamera( );
	Dptr<unBehaviorAttachement> batt = pObjectBuffer->CreateNew_BehaviorAttachement( );

	m_cam->AddWorldTransform( camtransform );
	m_cam->AddCamera( cam );
	m_cam->AddBehaviorAttachement( batt );
	batt->AddBehavior( "camscript", &camscrpt );

	cu->GetWorldTransform( )->ScaleAbs( 0.5, 0.5, 0.5 );
	camtransform->TranslateAbs( 0, 2, -3 );
	camscrpt.target = cu;

	InputEvent ExitEvent;
	InputEvent RightKey, LeftKey;
	InputEvent MonkeyMoveF, MonkeyMoveB, MonkeyTurnLeft, MonkeyTurnRight;

	MonkeyMoveF.event.type = EVENT_KEYPRESS;
	MonkeyMoveF.key.keycode = KEY_ARROW_UP;
	InputPair pairMF( MonkeyMoveF, bind(&bro::MoveForward,&broscript ));

	MonkeyMoveB.event.type = EVENT_KEYPRESS;
	MonkeyMoveB.key.keycode = KEY_ARROW_DOWN;
	InputPair pairMB( MonkeyMoveB, bind(&bro::MoveBackward,&broscript ));

	MonkeyTurnLeft.event.type = EVENT_KEYPRESS;
	MonkeyTurnLeft.key.keycode = KEY_ARROW_LEFT;
	InputPair pairML( MonkeyTurnLeft, bind((&bro::TurnLeft),&broscript));

	MonkeyTurnRight.event.type = EVENT_KEYPRESS;
	MonkeyTurnRight.key.keycode = KEY_ARROW_RIGHT;
	InputPair pairMR( MonkeyTurnRight, bind(&bro::TurnRight,&broscript ));

	RightKey.event.type = EVENT_KEYPRESS;
	RightKey.key.keycode = KEY_D;
	InputPair pairR( RightKey, bind(&Camera_Script::TurnRight,&camscrpt ) );

	LeftKey.event.type = EVENT_KEYPRESS;
	LeftKey.key.keycode = KEY_A;
	InputPair pairL( LeftKey, bind(&Camera_Script::TurnLeft,&camscrpt ) );

	ExitEvent.event.type		= EVENT_KEYDOWN;
	ExitEvent.key.keycode		= KEY_ESCAPE;
	InputPair pair( ExitEvent, [=]{SystemComponent::GetInstance()->Post_Quit_Mesage( 0 ); } );


	vector<InputContext>& contexts = m_pFrameWork->GetInputContextListForEditing( );
	InputContext cameracontrolcontext;
	cameracontrolcontext.m_pairs.push_back(pair);
	cameracontrolcontext.m_pairs.push_back( pairL );
	cameracontrolcontext.m_pairs.push_back( pairMR );
	cameracontrolcontext.m_pairs.push_back( pairMF );
	cameracontrolcontext.m_pairs.push_back( pairML );
	cameracontrolcontext.m_pairs.push_back( pairMB );
	cameracontrolcontext.m_pairs.push_back( pairR );

	contexts.push_back(cameracontrolcontext);

	initialized = true;
}

/*-----------------------------------------------------------------------------
Updates Application specific things like AI, ui response, etc.
-----------------------------------------------------------------------------*/
void Application::Update(){
	camscrpt.Update( );
}

/*-----------------------------------------------------------------------------
Links this application to the GAme Engine Object, so that they can communicate.
Parameters:
[IN]	pFrameWork	-	the pointer to the Engine to be linked to.
------------------------------------------------------------------------------*/
void Application::LinkToEngine(UnFramework* pFrameWork){
	m_pFrameWork = pFrameWork;
}