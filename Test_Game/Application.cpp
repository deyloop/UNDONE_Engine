/******************************************************************************
File	:	Application.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Application.h"
#include "_3DGraphic.h"
#include "DObjectBuffer.h"
#include "GameObject.h"
#include <ctime>
#include "UNDONE_DEBUG.h"
#include <Texture.h>
#include <_2DGraphic.h>
#include <iostream>

typedef DPointer<Shader> shaderptr;

/*-----------------------------------------------------------------------------
Default Contructor
-----------------------------------------------------------------------------*/
Application::Application(){
	m_pFrameWork = nullptr;
	m_pcam = nullptr;
	BlockGroup.m_pointer = nullptr;
	initialized = false;
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
void Application::LoadScene(DObjectBuffer* pObjectBuffer){
	
	//pObjectBuffer->SetInitAllocSize(100);
	

	DPointer<Shader> shVertex			= pObjectBuffer->CreateNew<Shader>();
	DPointer<Shader> shFragment			= pObjectBuffer->CreateNew<Shader>();
	DPointer<ShaderProgram> spMain		= pObjectBuffer->CreateNew<ShaderProgram>();
	DPointer<Mesh> cube_mesh			= pObjectBuffer->CreateNew<Mesh>( );
	DPointer<Mesh> monkey_mesh			= pObjectBuffer->CreateNew<Mesh>( );
	monkey_mesh->SetModelFile("monkey.obj");
	
	DPointer<GraphicMaterial> Redmaterial	= pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<GraphicMaterial> Bluematerial	= pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<GraphicMaterial> Greenmaterial = pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<GraphicMaterial> Yellowmaterial= pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<GraphicMaterial> Pinkmaterial	= pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<Texture> tex = pObjectBuffer->CreateNew<Texture>( );
	DPointer<_2DGraphic> _2dgraphic = pObjectBuffer->CreateNew<_2DGraphic>( );
	tex->LoadTexture2D("Test_Texture.jpg", true);
	_2dgraphic->SetTexture(tex);
	DPointer<GameObject> _2dobj = pObjectBuffer->CreateNew<GameObject>( );
	DPointer<WorldTransform> _2dtrans = pObjectBuffer->CreateNew<WorldTransform>( );
	_2dtrans->TranslateAbs(0.25f, 0.5f, 0.0f);
	_2dtrans->RotateAbs(45.0f, 0.0f, 0.0f);
	_2dtrans->ScaleAbs(0.5f, 1.0f, 0.0f);
	_2dobj->AddComponent<WorldTransform>(_2dtrans);
	_2dobj->AddComponent<_2DGraphic>(_2dgraphic);

	shVertex->LoadShader("shader.vert", GL_VERTEX_SHADER);
	shFragment->LoadShader("shader.frag", GL_FRAGMENT_SHADER);

	spMain->CreateProgram();
	spMain->AddShaderToProgram(shVertex.ptr());
	spMain->AddShaderToProgram(shFragment.ptr());

	spMain->LinkProgram();
	
	Redmaterial->Rename("RedMaterial");
	Bluematerial->Rename("BlueMaterial");
	
	Redmaterial->SetShaderProgramToUse(spMain);
	Greenmaterial->SetShaderProgramToUse(spMain);
	Yellowmaterial->SetShaderProgramToUse(spMain);
	Pinkmaterial->SetShaderProgramToUse(spMain);
	Bluematerial->SetShaderProgramToUse(spMain);
	
	Bluematerial->SetDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
	Redmaterial->SetDiffuseColor(glm::vec3(1.0f, 0.0f, 0.0f));
	Greenmaterial->SetDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
	Yellowmaterial->SetDiffuseColor(glm::vec3(1.0f, 1.0f, 0.0f));
	Pinkmaterial->SetDiffuseColor(glm::vec3(1.0f, 0.0f, 127.0f/255.0f));
	
	cube_mesh->Rename("CubeMesh");
	
	vector<DPointer<GraphicMaterial>> material;
	material.reserve(5);

	material.push_back(Redmaterial);
	material.push_back(Bluematerial);
	material.push_back(Greenmaterial);
	material.push_back(Yellowmaterial);
	material.push_back(Pinkmaterial);
	
	srand(time(0));

	BlockGroup = pObjectBuffer->CreateNew<GameObject>( );
	DPointer<GameObject> BlockGroup2 = pObjectBuffer->CreateNew<GameObject>( );
	DPointer<WorldTransform> grouTrans2 = pObjectBuffer->CreateNew<WorldTransform>( );
	DPointer<WorldTransform> grouTrans = pObjectBuffer->CreateNew<WorldTransform>( );
	BlockGroup->AddComponent<WorldTransform>(grouTrans2);
	BlockGroup2->AddComponent<WorldTransform>(grouTrans);
	grouTrans->TranslateRel(10.0f, 0.0f, 0.0f);
	BlockGroup->AddComponent<GameObject>(BlockGroup2);

#define SIZE 6

	for (int j = 0; j<SIZE; ++j) {
		for (int i = 0;i<SIZE; ++i) {

			if ((rand( )%4+2)> 3) continue;

			cout<<"\n";
			DPointer<GameObject> go_scene = pObjectBuffer->CreateNew<GameObject>( );
			go_scene->Rename((string("GameObject")+i)+j);
			DPointer<WorldTransform> transform1 = pObjectBuffer->CreateNew<WorldTransform>( );
			transform1->Rename((string("Transform")+i)+j);
			DPointer<_3DGraphic> graphic1 = pObjectBuffer->CreateNew<_3DGraphic>( );
			graphic1->Rename((string("Graphic")+i)+j);
			graphic1->OnInit( );
			go_scene->AddComponent<WorldTransform>(transform1);
			go_scene->AddComponent<Mesh>(cube_mesh);
			
			go_scene->AddComponent<GraphicMaterial>(material.at(rand()%5));
			
			go_scene->AddComponent<_3DGraphic>(graphic1);
			
			transform1->TranslateAbs(i, 0, j);
			//transform1.ptr( )->RotateAbs(1.0f, 45.0f,i*10+ 0.0f);
			transform1->ScaleAbs(0.5f, rand()%25+1, 0.5f);

			BlockGroup2->AddComponent<GameObject>(go_scene);
		}
	}

	DPointer<GameObject> cu = pObjectBuffer->CreateNew<GameObject>( );
	DPointer<WorldTransform> ct = pObjectBuffer->CreateNew<WorldTransform>( );
	cu->AddComponent<WorldTransform>(ct);
	cu->AddComponent<Mesh>(monkey_mesh);
	cu->AddComponent<GraphicMaterial>(Greenmaterial);
	DPointer<_3DGraphic> cg = pObjectBuffer->CreateNew<_3DGraphic>( );
	cu->AddComponent<_3DGraphic>(cg);
	//BlockGroup->AddComponent<GameObject>(cu);


	pObjectBuffer->GetControlCamera( ).SetPosition(glm::vec3(0.01f, 20.0f, 5.0f));
	pObjectBuffer->GetControlCamera( ).SetLookAt(glm::vec3(0.0f));
	m_pcam = &(pObjectBuffer->GetControlCamera( ));

	Yaw_Pitch = new Yaw_PitchCommand( );
	Exit = new ExitCommand(SystemComponent::GetInstance() );
	Move_Forward = new MoveForwardCommand( );
	Move_Backward = new MoveBackwardCommand( );
	Enable_Mouse = new Enable_Yaw_Pitch_Command( );
	Disable_Mouse = new Disable_Yaw_Pitch_Command( );

	InputEvent KeyEventL,ExitEvent,MoveFEvnt,MoveBEvnt,MBDEvnt,MBUEvnt;
	
	ExitEvent.event.type = EVENT_KEYDOWN;
	ExitEvent.key.keycode = KEY_ESCAPE;
	InputPair pair2(ExitEvent, *Exit);

	KeyEventL.event.type = EVENT_MOUSEMOVE;
	InputPair pair(KeyEventL, *Yaw_Pitch);

	MBDEvnt.event.type = EVENT_MOUSEBUTTONDOWN;
	MBDEvnt.mouse_button.button = MOUSE_BUTTON_L;
	InputPair pairMBD(MBDEvnt, *Enable_Mouse);
	
	MBUEvnt.event.type = EVENT_MOUSEBUTTONUP;
	MBUEvnt.mouse_button.button = MOUSE_BUTTON_L;
	InputPair pairMBU(MBUEvnt, *Disable_Mouse);
	
	MoveFEvnt.event.type = EVENT_KEYDOWN;
	MoveFEvnt.key.keycode = KEY_W;
	InputPair pairW(MoveFEvnt, *Move_Forward);

	MoveBEvnt.event.type = EVENT_KEYDOWN;
	MoveBEvnt.key.keycode = KEY_S;
	InputPair pairS(MoveBEvnt, *Move_Backward);

	vector<InputContext>& contexts = m_pFrameWork->GetInputContextListForEditing( );
	InputContext cameracontrolcontext;
	cameracontrolcontext.m_pControl = m_pcam;
	cameracontrolcontext.m_pairs.push_back(pair);
	cameracontrolcontext.m_pairs.push_back(pair2);
	cameracontrolcontext.m_pairs.push_back(pairW);
	cameracontrolcontext.m_pairs.push_back(pairS);
	cameracontrolcontext.m_pairs.push_back(pairMBD);
	cameracontrolcontext.m_pairs.push_back(pairMBU);
	contexts.push_back(cameracontrolcontext);

	pObjectBuffer->SortByPriority<_3DGraphic>( );

	initialized = true;
}

/*-----------------------------------------------------------------------------
Updates Application specific things like AI, ui response, etc.
-----------------------------------------------------------------------------*/
void Application::Update(){

	BlockGroup->worldTransform->RotateRel(0.0f, 0.1f, 0.0f);
	cout<<"FrameRate: "<<m_pFrameWork->GetFPS( )<<"\n";
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