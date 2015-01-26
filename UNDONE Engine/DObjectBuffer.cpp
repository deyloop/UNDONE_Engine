/******************************************************************************
Project	:	UNDONE Engine
File	:
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "DObjectBuffer.h"

namespace UNDONE_ENGINE {
	DObjectBuffer::DObjectBuffer( ) {
		m_empty = true;
	}

	DObjectBuffer::~DObjectBuffer( ) {
		m_storage_lists.clear( );
		m_storage_vectors.clear( );
		m_storage_types.clear( );
		m_empty = true;
	}
}