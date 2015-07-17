#pragma once 

#ifndef _UN_COMPONENT_
#define _UN_COMPONENT_

namespace UNDONE_ENGINE{
	class unComponent{
	public:
		virtual void Rename(const char*) = 0;
	};
}

#endif