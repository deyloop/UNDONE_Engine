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
	BlockMaze.m_pointer	= nullptr;
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
void Application::LoadScene(){
	
	unObjectBuffer* pObjects = m_pFrameWork->Objectbuffer;
	pObjects->SetInitAllocSize(500);
	
	
	Dptr<unShader> shVertex			= pObjects->CreateNew_Shader();
	Dptr<unShader> shFragment			= pObjects->CreateNew_Shader();
	Dptr<unShaderProgram> spMain		= pObjects->CreateNew_ShaderProgram();
	Dptr<unMesh> cube_mesh			= pObjects->CreateNew_Mesh( );
	Dptr<unMesh> monkey_mesh			= pObjects->CreateNew_Mesh( );

	Dptr<unGraphicMaterial> Redmaterial	= pObjects->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Bluematerial	= pObjects->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Greenmaterial = pObjects->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Yellowmaterial= pObjects->CreateNew_GraphicMaterial( );
	Dptr<unGraphicMaterial> Pinkmaterial	= pObjects->CreateNew_GraphicMaterial( );
	Dptr<unTexture> tex = pObjects->CreateNew_Texture();
    Dptr<unTexture> tex2 = pObjects->CreateNew_Texture( );

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


	Dptr<unGameObject> Texture_Display = pObjects->CreateNew_GameObject( );
	Dptr<unGraphic2D> Texture_Display_Graphic = pObjects->CreateNew_Graphic2D( );
	Dptr<unWorldTransform> Texture_Display_Transform = pObjects->CreateNew_WorldTransform( );
	Texture_Display_Transform->TranslateAbs(-1.0f, -1.f, 0.0f);
    Texture_Display_Transform->ScaleAbs( 0.5, 0.5, 1.0f );
	Texture_Display_Graphic->SetTexture(tex);
	Texture_Display->AddWorldTransform(Texture_Display_Transform);
	Texture_Display->AddGraphic2D(Texture_Display_Graphic);
	Texture_Display->Load();

	srand((unsigned int)time(0));

	
	BlockMaze = pObjects->CreateNew_GameObject( );
	Dptr<unWorldTransform>	Maze_Transform	= pObjects->CreateNew_WorldTransform( );
	BlockMaze	->	AddWorldTransform(Maze_Transform);

#define SIZE 30

	Dptr<unGameObject> Floor				= pObjects->CreateNew_GameObject( );
	Dptr<unWorldTransform> Floor_Transform	= pObjects->CreateNew_WorldTransform( );
	Dptr<unGraphic3D> Floor_Graphic			= pObjects->CreateNew_Graphic3D( );
	
	Floor->AddWorldTransform(Floor_Transform);
	Floor->AddMesh(cube_mesh);
	Floor->AddGraphicMaterial(material.at(rand()%5));
	Floor->AddGraphic3D(Floor_Graphic);
	
	Floor_Transform->ScaleAbs(SIZE*2, 0.05, SIZE*2);
	Floor_Transform->TranslateAbs(0,-0.5,0 );

	BlockMaze->AddGameObject(Floor);

	Maze maze;
	maze.Generate(SIZE);

	for (int j = 0; j<SIZE; ++j) {
		for (int i = 0;i<SIZE; ++i) {

			if (maze.data[i+j*SIZE] == SPACE) continue;

			Dptr<unGameObject> go_scene		= pObjects->CreateNew_GameObject( );
			Dptr<unWorldTransform> transform1 = pObjects->CreateNew_WorldTransform( );
			Dptr<unGraphic3D> graphic1		= pObjects->CreateNew_Graphic3D( );
			
			go_scene->AddWorldTransform(transform1);
			go_scene->AddMesh(cube_mesh);
			go_scene->AddGraphicMaterial(material.at(rand()%5));
			go_scene->AddGraphic3D(graphic1);
			
			transform1->TranslateAbs((-SIZE)/2+(float)i, 0,(float)j-SIZE/2);
			transform1->ScaleAbs(0.5f, (float)1, 0.5f);

			BlockMaze->AddGameObject(go_scene);
		}
	}
	
	BlockMaze->Load();
	//pObjects->Delete_GameObject(Floor);


	Monkey = pObjects->CreateNew_GameObject( );
	Dptr<unWorldTransform>	ct = pObjects->CreateNew_WorldTransform( );
	Dptr<unGraphic3D>		cg = pObjects->CreateNew_Graphic3D( );
	Dptr<unBehaviorAttachement> att = pObjects->CreateNew_BehaviorAttachement( );
	
    Monkey->AddWorldTransform(ct);
    
	Monkey->AddMesh(monkey_mesh);
	Monkey->AddGraphicMaterial(Yellowmaterial);
	Monkey->AddGraphic3D(cg);
	Monkey->AddBehaviorAttachement( att );
	att->AddBehavior( "bro", &broscript );
	Monkey->Load();

	m_cam = pObjects->CreateNew_GameObject( );
	Dptr<unWorldTransform> camtransform = pObjects->CreateNew_WorldTransform( );
	Dptr<unCamera> cam = pObjects->GetControlCamera( );
	Dptr<unBehaviorAttachement> batt = pObjects->CreateNew_BehaviorAttachement( );

	m_cam->AddWorldTransform( camtransform );
	m_cam->AddCamera( cam );
	m_cam->AddBehaviorAttachement( batt );
	batt->AddBehavior( "camscript", &camscrpt );
	m_cam->Load();
	camscrpt.limit_hight = 5;

	Monkey->GetWorldTransform( )->ScaleAbs( 0.5, 0.5, 0.5 );
	camtransform->TranslateAbs( 0, 2, -3 );
	camscrpt.target = Monkey;

	m_pFrameWork->Input->LoadContexts("../Data/input_contexts.unconfig");
	m_pFrameWork->Input->ActivateContext("monkey_movement");
	m_pFrameWork->Input->ActivateContext("system_control");

	m_pFrameWork->Input->RegisterCallback([=]{SystemComponent::GetInstance()->Post_Quit_Mesage( 0 ); },"Exit");
	initialized = true;
}

/*-----------------------------------------------------------------------------
Updates Application specific things like AI, ui response, etc.
-----------------------------------------------------------------------------*/
void Application::Update(){
	camscrpt.Update( );
	
	//BlockMaze->GetWorldTransform()->RotateRel(0,-0.07,0 );
}

/*-----------------------------------------------------------------------------
Links this application to the GAme Engine Object, so that they can communicate.
Parameters:
[IN]	pFrameWork	-	the pointer to the Engine to be linked to.
------------------------------------------------------------------------------*/
void Application::LinkToEngine(UnFramework* pFrameWork){
	m_pFrameWork = pFrameWork;
}