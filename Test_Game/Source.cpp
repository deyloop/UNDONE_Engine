#include <Undone_Engine.h>

/******************************************************************************
Project		:	Hexagon Engine
File		:	Program.cpp
Author		:	Anurup Dey
Environment	:	IDE		-Microsoft Visual Studio 2010.
OS		-Microsoft Windows 7 Ultimate.
PC model-IBM Lenovo ThinkCentre Edge Tower.
CPU		-Intel(R) Pentium(R) CPU G680
@ 2.70Ghz,2.69Ghz.
RAM		-1935716KB (1982173184 bytes or 1.8GB).
Graphic Card	-Intel(R) HD Graphics Family
Graphic Memory	-1024MB (Integrated).
******************************************************************************/
//////////////////////////////////////////////////////////////////////////////

#include "SystemComponent.h"
#include "FrameWork.h"
#include "Application.h"
#include <iostream>
using namespace std;

#define UND_DEBUG_L5

/*-----------------------------------------------------------------------------
This is the starting point of the whole program.
-----------------------------------------------------------------------------*/
int main( ) {
	cout<<"UNDONE Engine Test Game (Debug Console).\t\n"
		   <<"By Anurup Dey.\n\n"
		   <<"Initializing\n\n\n";

	Application*	pApp = new Application( );
	FrameWork*		pUNDONE = new FrameWork(pApp);

	pApp->LinkToEngine(pUNDONE);
	pUNDONE->Initialise("UNDONE", 1000, 700);

	//time to rock n roll!
	pUNDONE->Run( );

	//Cleanup!
	pApp->Release( );
	pUNDONE->Release( );
	delete pApp;
	delete pUNDONE;

	return 0;
}