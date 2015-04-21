#include "UNDONE_DEBUG.h"
///////////////////////////////////////////////////////////////////////////////
string operator +(string lhs, int rhs) {
	char numstr[20];
	sprintf_s(numstr, "%i", rhs);
	return lhs+numstr;
}

string operator +(string lhs, float rhs) {
	char numstr[20];
	sprintf_s(numstr, "%f", rhs);
	return lhs+numstr;
}