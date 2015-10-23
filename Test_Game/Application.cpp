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
	m_pcam					= nullptr;
	BlockGroup.m_pointer	= nullptr;
	initialized				= false;
}

/*-----------------------------------------------------------------------------
Default destructor
------------------------------------------------------------------------------*/
void Application::Release(){
	if (initialized) {
		delete Yaw_Pitch;
		delete Exit;
		delete Move_Forward;
		delete Move_Backward;
		delete Enable_Mouse;
		delete Disable_Mouse;
		initialized = false;
	}
}

class ExitCommand : public Command {
public:
	SystemComponent* m_pcomp;
	ExitCommand(SystemComponent* b) :m_pcomp(b) { };
	virtual void execute(InputControl* control, InputEvent& given_event) {
		m_pcomp->Post_Quit_Mesage(0);
	}
};

 class bro : public Behavior {
	public:
		void Load( )  {};
		void UnLoad() {};
		void Left( ) {
			Gameobject->GetWorldTransform( )->TranslateRel( -0.01f, 0.0f, 0.0f );
		}
 };

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
	Dptr<unGraphic2D> _2dgraphic = pObjectBuffer->CreateNew_Graphic2D( );
	tex->SetTexture2D("HOUSE.png", true);
	_2dgraphic->SetTexture(tex);
	Dptr<unGameObject> _2dobj = pObjectBuffer->CreateNew_GameObject( );
	Dptr<unWorldTransform> _2dtrans = pObjectBuffer->CreateNew_WorldTransform( );
	//_2dtrans->TranslateAbs(1.0f, 1.f, 0.0f);
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
	cu->AddWorldTransform(ct);
	cu->AddMesh(monkey_mesh);//change to monkey later
	cu->AddGraphicMaterial(material[rand() % 5]);
	cu->AddGraphic3D(cg);
	Dptr<unBehaviorAttachement> att = pObjectBuffer->CreateNew_BehaviorAttachement( );
	cu->AddBehaviorAttachement( att );
	
	bro* broscript = new bro( );

	att->AddBehavior( "bro", broscript );

	cu->GetWorldTransform( )->ScaleAbs( 0.5, 0.5, 0.5 );
	pObjectBuffer->GetControlCamera( ).SetPosition(glm::vec3(-2.01f, 2.0f, -2.0f));
	pObjectBuffer->GetControlCamera( ).SetLookAt(glm::vec3(0.0f));
	m_pcam = &(pObjectBuffer->GetControlCamera( ));

	Yaw_Pitch		= new Yaw_PitchCommand( );
	Exit			= new ExitCommand(SystemComponent::GetInstance() );
	Move_Forward	= new MoveForwardCommand( );
	Move_Backward	= new MoveBackwardCommand( );
	Enable_Mouse	= new Enable_Yaw_Pitch_Command( );
	Disable_Mouse	= new Disable_Yaw_Pitch_Command( );

	InputEvent KeyEventL,ExitEvent,MoveFEvnt,MoveBEvnt,MBDEvnt,MBUEvnt;
	InputEvent RightKey, LeftKey;
	InputEvent MonkeyMoveF, MonkeyMoveB, MonkeyTurnLeft, MonkeyTurnRight;
	
	forward = vec3( 0.0f, 0.0f, 0.05f );

	MonkeyMoveF.event.type = EVENT_KEYPRESS;
	MonkeyMoveF.key.keycode = KEY_ARROW_UP;
	InputPair pairMF( MonkeyMoveF, [&] {cu->GetWorldTransform( )->TranslateRel(unvec3((forward*0.5f))); } );

	MonkeyMoveB.event.type = EVENT_KEYPRESS;
	MonkeyMoveB.key.keycode = KEY_ARROW_DOWN;
	InputPair pairMB( MonkeyMoveB, [&] {cu->GetWorldTransform( )->TranslateRel(unvec3((-forward*0.5f))); } );

	MonkeyTurnLeft.event.type = EVENT_KEYPRESS;
	MonkeyTurnLeft.key.keycode = KEY_ARROW_LEFT;
	InputPair pairML( MonkeyTurnLeft, /*[&] {cu->GetWorldTransform( )->RotateRel( 0.0f, 0.9f, 0.0f ); 
										  glm::mat4 rot = glm::rotate( 0.9f, vec3(0.0f,1.0f,0.0f ));
											forward = mat3(rot) * forward ;}*/bind(&bro::Left,broscript) );

	MonkeyTurnRight.event.type = EVENT_KEYPRESS;
	MonkeyTurnRight.key.keycode = KEY_ARROW_RIGHT;
	InputPair pairMR( MonkeyTurnRight, [&] {cu->GetWorldTransform( )->RotateRel( 0.0f, -0.9f, 0.0f ); 
											glm::mat4 rot = glm::rotate( -0.9f, vec3(0.0f,1.0f,0.0f ));
											forward = mat3(rot) * forward ; } );

	RightKey.event.type = EVENT_KEYPRESS;
	RightKey.key.keycode = KEY_D;
	InputPair pairR( RightKey, [=] {m_pcam->Strafe( -0.1f ); } );

	LeftKey.event.type = EVENT_KEYPRESS;
	LeftKey.key.keycode = KEY_A;
	InputPair pairL( LeftKey, [=] {m_pcam->Strafe( 0.1f ); } );

	ExitEvent.event.type		= EVENT_KEYDOWN;
	ExitEvent.key.keycode		= KEY_ESCAPE;
	InputPair pair( ExitEvent, [=]{SystemComponent::GetInstance()->Post_Quit_Mesage( 0 ); } );

	KeyEventL.event.type = EVENT_MOUSEMOVE;
	InputPair pair2( KeyEventL, [&](float x, float y) {Yaw_Pitch->execute( m_pcam, x ,y); },0);

	MBDEvnt.event.type			= EVENT_MOUSEBUTTONDOWN;
	MBDEvnt.mouse_button.button = MOUSE_BUTTON_L;
	InputPair pairMBD(MBDEvnt, [&] {Enable_Mouse->execute( m_pcam, KeyEventL ); });
	
	MBUEvnt.event.type			= EVENT_MOUSEBUTTONUP;
	MBUEvnt.mouse_button.button = MOUSE_BUTTON_L;
	InputPair pairMBU(MBUEvnt, [&] {Disable_Mouse->execute( m_pcam, KeyEventL ); });
	
	MoveFEvnt.event.type	 = EVENT_KEYPRESS;
	MoveFEvnt.key.keycode	 = KEY_W;
	InputPair pairW(MoveFEvnt, [&] {Move_Forward->execute( m_pcam, KeyEventL ); } );

	MoveBEvnt.event.type	= EVENT_KEYPRESS;
	MoveBEvnt.key.keycode	= KEY_S;
	InputPair pairS(MoveBEvnt,  [&] {Move_Backward->execute( m_pcam, KeyEventL ); });

	vector<InputContext>& contexts = m_pFrameWork->GetInputContextListForEditing( );
	InputContext cameracontrolcontext;
	cameracontrolcontext.m_pControl = m_pcam;
	cameracontrolcontext.m_pairs.push_back(pair);
	cameracontrolcontext.m_pairs.push_back(pair2);
	cameracontrolcontext.m_pairs.push_back(pairW);
	cameracontrolcontext.m_pairs.push_back(pairS);
	cameracontrolcontext.m_pairs.push_back(pairMBD);
	cameracontrolcontext.m_pairs.push_back(pairMBU);
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

	//BlockGroup->GetWorldTransform()->RotateRel(0.0f, 0.3f, 0.0f);
	m_pcam->SetLookAt( cu->GetWorldTransform( )->GetPosition( ) );
   // m_pcam->SetPosition( cu->GetWorldTransform( )->GetPosition( ) + vec3( 10.0f, 10.0f, 0.0f ) );
	//cout<<"FrameRate: "<<m_pFrameWork->GetFPS( )<<"\n";
	//m_pcam->Yaw(0.01f);
	m_pcam->Update( );
	
}

/*-----------------------------------------------------------------------------
Links this application to the GAme Engine Object, so that they can communicate.
Parameters:
[IN]	pFrameWork	-	the pointer to the Engine to be linked to.
------------------------------------------------------------------------------*/
void Application::LinkToEngine(UnFramework* pFrameWork){
	m_pFrameWork = pFrameWork;
}