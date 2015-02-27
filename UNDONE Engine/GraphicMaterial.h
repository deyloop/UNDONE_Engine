/******************************************************************************
Project	:	UNDONE Engine
File	:	GraphicMaterial.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma one

#ifndef _GRAPHICMATERIAL_H
#define _GRAPHICMATERIAL_H

//includes
#include "Component.h"				//GraphicMaterial IS a component
#include "UniformDataInterface.h"
#include "ShaderProgram.h"


namespace UNDONE_ENGINE {

	/*-------------------------------------------------------------------------
	THe material of the object will decide how it will appear on screen. 
	Contains the instructions on how to draw the mesh.
	-------------------------------------------------------------------------*/
	class UNDONE_API GraphicMaterial : public Component {
	public:
		GraphicMaterial( );
		~GraphicMaterial( ) { Release( ); }

		void Release( ) { UnLoad( ); };

		void SetParent(DPointer<GameObject> ppParent);
		void SetShaderProgramToUse(DPointer<ShaderProgram> ppShaderProgram);

		UniformDataInterface& GetUniformDataInterface( ) { return m_DataInterface; };
		
		void Load( );
		void ApplyMaterial( );
		void UnLoad( );
	
	private:
		UniformDataInterface	m_DataInterface;
		vector<int>				m_UniformDataLocations;

		DPointer<ShaderProgram>			m_ppShaderProgram;

		int								m_num_parents;

		static unsigned int		s_ActiveShaderProgram;
	};
};

#endif