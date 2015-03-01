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
#include <iostream>

typedef DPointer<Shader> shaderptr;

/*-----------------------------------------------------------------------------
Default Contructor
-----------------------------------------------------------------------------*/
Application::Application(){
	m_pFrameWork = nullptr;
	m_pcam = nullptr;
	BlockGroup.m_pointer = nullptr;
}

/*-----------------------------------------------------------------------------
Default destructor
------------------------------------------------------------------------------*/
void Application::Release(){
	//Again, nothing to do yet.
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
	
	DPointer<GraphicMaterial> Redmaterial	= pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<GraphicMaterial> Bluematerial	= pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<GraphicMaterial> Greenmaterial = pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<GraphicMaterial> Yellowmaterial= pObjectBuffer->CreateNew<GraphicMaterial>( );
	DPointer<GraphicMaterial> Pinkmaterial	= pObjectBuffer->CreateNew<GraphicMaterial>( );
	

	shVertex.ptr()->LoadShader("shader.vert", GL_VERTEX_SHADER);
	shFragment.ptr()->LoadShader("shader.frag", GL_FRAGMENT_SHADER);

	spMain.ptr()->CreateProgram();
	spMain.ptr()->AddShaderToProgram(shVertex.ptr());
	spMain.ptr()->AddShaderToProgram(shFragment.ptr());

	spMain.ptr()->LinkProgram();
	
	Redmaterial.ptr( )->Rename("RedMaterial");
	Bluematerial.ptr( )->Rename("BlueMaterial");
	
	Redmaterial.ptr( )->SetShaderProgramToUse(spMain);
	Greenmaterial.ptr( )->SetShaderProgramToUse(spMain);
	Yellowmaterial.ptr( )->SetShaderProgramToUse(spMain);
	Pinkmaterial.ptr( )->SetShaderProgramToUse(spMain);
	Bluematerial.ptr( )->SetShaderProgramToUse(spMain);
	
	Bluematerial.ptr( )->SetDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
	Redmaterial.ptr( )->SetDiffuseColor(glm::vec3(1.0f, 0.0f, 0.0f));
	Greenmaterial.ptr( )->SetDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
	Yellowmaterial.ptr( )->SetDiffuseColor(glm::vec3(1.0f, 1.0f, 0.0f));
	Pinkmaterial.ptr( )->SetDiffuseColor(glm::vec3(1.0f, 0.0f, 127.0f/255.0f));
	
	cube_mesh.ptr( )->Rename("CubeMesh");
	
	vector<DPointer<GraphicMaterial>> material;
	material.reserve(5);

	material.push_back(Redmaterial);
	material.push_back(Bluematerial);
	material.push_back(Greenmaterial);
	material.push_back(Yellowmaterial);
	material.push_back(Pinkmaterial);
	
	srand(time(0));

	BlockGroup = pObjectBuffer->CreateNew<GameObject>( );
	DPointer<WorldTransform> grouTrans = pObjectBuffer->CreateNew<WorldTransform>( );
	BlockGroup.Obj( ).AddComponent<WorldTransform>(grouTrans);
	grouTrans.ptr( )->TranslateRel(10.0f, 0.0f, 0.0f);

#define SIZE 10

	for (int j = 0; j<SIZE; ++j) {
		for (int i = 0;i<SIZE; ++i) {

			if ((rand( )%4+2)> 3) continue;

			cout<<"\n";
			DPointer<GameObject> go_scene = pObjectBuffer->CreateNew<GameObject>( );
			go_scene.ptr( )->Rename((string("GameObject")+i)+j);
			DPointer<WorldTransform> transform1 = pObjectBuffer->CreateNew<WorldTransform>( );
			transform1.ptr( )->Rename((string("Transform")+i)+j);
			DPointer<_3DGraphic> graphic1 = pObjectBuffer->CreateNew<_3DGraphic>( );
			graphic1.ptr( )->Rename((string("Graphic")+i)+j);
			graphic1.ptr( )->OnInit( );
			go_scene.ptr( )->AddComponent<WorldTransform>(transform1);
			go_scene.ptr( )->AddComponent<Mesh>(cube_mesh);
			
			go_scene.ptr( )->AddComponent<GraphicMaterial>(material.at(rand()%5));
			
			go_scene.ptr( )->AddComponent<_3DGraphic>(graphic1);
			
			transform1.ptr( )->TranslateAbs(i, 0, j);
			//transform1.ptr( )->RotateAbs(1.0f, 45.0f,i*10+ 0.0f);
			transform1.ptr( )->ScaleAbs(1, rand()%25+1, 1);

			BlockGroup.Obj( ).AddComponent<GameObject>(go_scene);
		}
	}

	pObjectBuffer->GetControlCamera( ).SetPosition(glm::vec3(0.01f, 50.0f, 5.0f));
	pObjectBuffer->GetControlCamera( ).SetLookAt(glm::vec3(0.0f));
	m_pcam = &(pObjectBuffer->GetControlCamera( ));

	Command* Yaw_Pitch = new Yaw_PitchCommand( );
	Command* Exit = new ExitCommand(SystemComponent::GetInstance() );
	Command* Move_Forward = new MoveForwardCommand( );
	Command* Move_Backward = new MoveBackwardCommand( );
	Command* Enable_Mouse = new Enable_Yaw_Pitch_Command( );
	Command* Disable_Mouse = new Disable_Yaw_Pitch_Command( );

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
}

/*-----------------------------------------------------------------------------
Updates Application specific things like AI, ui response, etc.
-----------------------------------------------------------------------------*/
void Application::Update(){

	BlockGroup.ptr( )->worldTransform.ptr( )->RotateRel(0.0f, 0.1f, 0.0f);
	//cout<<"FrameRate: "<<m_pFrameWork->GetFPS( )<<"\n";
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