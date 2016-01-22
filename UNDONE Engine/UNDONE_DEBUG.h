#pragma once

#ifndef _UNDONE_DEBUG_H
#define _UNDONE_DEBUG_H
#include <string>
#include <iostream>
#include "UNDONE_Engine_declr.h"
using namespace std;

//#define UNDONE_DEBUG_OUTPUT

inline void _coutput(std::string message) {
	std::cout<<message;
};

#ifdef UNDONE_DEBUG_OUTPUT
#define coutput(message) _coutput(std::string("")+message)
#else
#define coutput(message)
#endif

string UNDONE_API operator +(string lhs, int rhs);
string UNDONE_API operator +(string lhs, float rhs);
#endif