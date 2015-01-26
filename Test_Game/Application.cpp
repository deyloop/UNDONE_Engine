/******************************************************************************
File	:	Application.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "Application.h"
#include "_3DGraphic.h"
#include "DObjectBuffer.h"
#include <iostream>
/*namespace UNDONE_ENGINE {
	template <typename T>
	struct UNDONE_API DPointer {
		T** m_pointer;
		T* ptr( ) { return *m_pointer; }
		T&  Obj( ) { return *(*m_pointer); }
	};
}*/
typedef DPointer<Shader> shaderptr;

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
	

	

	DPointer<Shader> shVertex		= pObjectBuffer->CreateNew<Shader>();
	DPointer<Shader> shFragment		= pObjectBuffer->CreateNew<Shader>();
	DPointer<ShaderProgram> spMain	= pObjectBuffer->CreateNew<ShaderProgram>();

	shVertex.ptr()->LoadShader("shader.vert", GL_VERTEX_SHADER);
	shFragment.ptr()->LoadShader("shader.frag", GL_FRAGMENT_SHADER);

	spMain.ptr()->CreateProgram();
	spMain.ptr()->AddShaderToProgram(shVertex.ptr());
	spMain.ptr()->AddShaderToProgram(shFragment.ptr());

	spMain.ptr()->LinkProgram();
	spMain.ptr()->UseProgram();

	DPointer<_3DGraphic> obj = pObjectBuffer->CreateNew<_3DGraphic>();
	obj.ptr()->SetShaderProgramToUse(spMain.m_pointer);
	obj.ptr()->OnInit();
	DPointer<_3DGraphic> obj2 = pObjectBuffer->CreateNew<_3DGraphic>( );
	obj2.ptr()->SetShaderProgramToUse(spMain.m_pointer);
	obj2.ptr()->OnInit( );
	//obj2->GetWorldTransform( ).SetYPosition(3.0f);
	obj2.ptr()->GetWorldTransform( ).SetZPosition(4.0f);
	obj2.ptr()->GetWorldTransform( ).SetXPosition(4.0f);

	pObjectBuffer->GetControlCamera( ).SetPosition(glm::vec3(5.0f, 5.0f, 5.0f));
	pObjectBuffer->GetControlCamera( ).SetLookAt(glm::vec3(0.0f));
	m_pcam = &(pObjectBuffer->GetControlCamera( ));

	Command* YawLeft = new LeftYawCommand( );
	Command* YawRight = new RightYawCommand( );
	Command* Exit = new ExitCommand(SystemComponent::GetInstance() );
	
	InputEvent KeyEventL, KeyEventR ,ExitEvent;
	ExitEvent.event.type = EVENT_KEYDOWN;
	ExitEvent.key.keycode = KEY_ESCAPE;
	KeyEventL.event.type = EVENT_KEYDOWN;
	KeyEventL.key.keycode = KEY_ARROW_LEFT;
	InputPair pair(KeyEventL, *YawLeft);
	KeyEventR.event.type = EVENT_KEYDOWN;
	KeyEventR.key.keycode = KEY_ARROW_RIGHT;
	InputPair pairR(KeyEventR, *YawRight);
	InputPair pair2(ExitEvent, *Exit);

	vector<InputContext>& contexts = m_pFrameWork->GetInputContextListForEditing( );
	InputContext cameracontrolcontext;
	cameracontrolcontext.m_pControl = m_pcam;
	cameracontrolcontext.m_pairs.push_back(pair);
	cameracontrolcontext.m_pairs.push_back(pairR);
	cameracontrolcontext.m_pairs.push_back(pair2);
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