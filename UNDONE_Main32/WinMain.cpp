/******************************************************************************
File	:	WinMain.cpp
Author	:	Anurup Dey

		Copyright (C) 2015 Anurup Dey 
		<anu.rup.dey98@gmail.com>

	This file is part of UNDONE-Engine.

	UNDONE-Engine can not be copied and/or distributed without the express
	permission of Anurup Dey. Unauthorized copying of this file, via any
	medium is strictly prohibited.

	Proprietary and confidential.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "WindowsSystemComponent.h"

using namespace UNDONE_ENGINE;
#ifdef _WINDOWS_OS_

#define SafelyDelete(x){x->Release();delete x;}

/*-----------------------------------------------------------------------------
Actual Statrting Point of the application on the Windows Operating system. 
This then calls the separately defined main() function after setting up[
and initialising the System Components for Windows. This clearly wierd hack
needed to be implimented to be able to switch to other platforms in the 
future.
Parameters:
[in]	hInstance		-a pionter to the current instance of this application.
[in]	hPrevInstance	-a pointer to the prevous instance of this application.
[in]	lpCmdLine		-arguments passed through command line execution.
[in]	nCmdShow		-unknown parameter. not really important.
Returns:	0 on a successfull run; any other integer on error.
-----------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPTSTR lpCmdLine, int nCmdShow){
	WindowsSystemComponent* pSysComponent = WindowsSystemComponent::GetWindowsInstance();
	if (!pSysComponent->Initialise(hInstance, "UNDONE_ENGINE")){
		SafelyDelete(pSysComponent);
		return 1;
	}
	
	pSysComponent->CreateConsole( );

	//call the main() function
	int returncode = main();

	//cleanup
	SafelyDelete(pSysComponent);
	return returncode;
}

#endif