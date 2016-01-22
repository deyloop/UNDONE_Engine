/******************************************************************************
Project		:	Hexagon Engine
File		:	Program.cpp
Author		:	Anurup Dey
Environment	:	IDE		-Microsoft Visual Studio 2015 Enterprise.
				OS		-Microsoft Windows 10 pro.
				PC model-IBM Lenovo ThinkCentre Edge Tower.
				CPU		-Intel(R) Pentium(R) CPU G680
							@ 2.70Ghz,2.69Ghz.
				RAM		-1935716KB (1982173184 bytes or 1.8GB).
				Graphic Card	-Intel(R) HD Graphics Family
				Graphic Memory	-1024MB (Integrated).
******************************************************************************/
//////////////////////////////////////////////////////////////////////////////

//#include <vld.h>
#include <Undone_Engine.h>
#include "Application.h"

/*-----------------------------------------------------------------------------
This is the starting point of the whole program.
-----------------------------------------------------------------------------*/
int Dmain( ) {
	
	Application	App;
	UnFramework*	pUNDONE = Create_Un_Framwork_Inst(&App);

	App.LinkToEngine(pUNDONE);
	pUNDONE->Initialise("Test Game", 1000, 700/*,false*/);

	//time to rock n roll!
	pUNDONE->Run( );

	//Cleanup!
	App.Release( );
	SafelyDelete(pUNDONE);

	return 0;

}