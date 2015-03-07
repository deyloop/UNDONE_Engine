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
#include "MaterialProperty.h"
#include <glm.hpp>


namespace UNDONE_ENGINE {


	/*-------------------------------------------------------------------------
	THe material of the object will decide how it will appear on screen. 
	Contains the instructions on how to draw the mesh.
	-------------------------------------------------------------------------*/
	class UNDONE_API GraphicMaterial : public Component {
	public:
		GraphicMaterial( );
		~GraphicMaterial( ) { Release( ); }

		void Release( ) { Unload( ); };

		void OnParentBeingChilded( );
		void SetShaderProgramToUse(DPointer<ShaderProgram> ppShaderProgram);

		UniformDataInterface& GetUniformDataInterface( ) { return m_DataInterface; };
		
		void Load( );
		void ApplyMaterial( );
		void Unload( );
		
		void SetDiffuseColor(glm::vec3& color) { m_diffcolor = color; }
		static void SetCurrentlyActiveProgram(UINT uiID) { s_ActiveShaderProgram = uiID; };
	private:
		
		void OnParentSet( );
		
		UniformDataInterface			m_DataInterface;
		vector<int>						m_UniformDataLocations;
		vector<MaterialProperty>		m_Properies;

		DPointer<ShaderProgram>			m_ppShaderProgram;

		int								m_num_parents;
		glm::vec3						m_diffcolor;
		int								m_instances;
		static unsigned int		s_ActiveShaderProgram;

	};
};

#endif