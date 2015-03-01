#pragma once

#ifndef UNDONE_DCLR_H
#define UNDONE_DCLR_H

#ifdef UNDONE_EXPORTS
	#define UNDONE_API __declspec(dllexport) 
#else
	#define UNDONE_API __declspec(dllimport) 
#endif

#endif
