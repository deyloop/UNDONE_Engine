/******************************************************************************
File	:	WinMain.cpp
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