/******************************************************************************
Project	:	UNDONE Engine
File	:	GraphicMaterial.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

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
	class GraphicMaterial : public Component {
	public:
		UNDONE_API GraphicMaterial( );
		UNDONE_API ~GraphicMaterial( ) { Release( ); }

		void Release( ) { Unload( ); };

		UNDONE_API void OnParentBeingChilded( );
		UNDONE_API void SetShaderProgramToUse(DPointer<ShaderProgram> ppShaderProgram);

		UniformDataInterface& GetUniformDataInterface( ) { return m_DataInterface; };
		

		UNDONE_API void Load( );
		void ApplyMaterial( );
		UNDONE_API void Unload( );
		
		UNDONE_API void SetDiffuseColor(glm::vec3& color);
		UNDONE_API void SetProperty(string property_name, float& value);
		UNDONE_API void SetProperty(string property_name, int& value) { };
		UNDONE_API void SetProperty(string property_name, glm::vec3& value);
		UNDONE_API void SetProperty(string property_name, glm::vec4& value) { };
		//TODO: Add all types of property setters.

		static void SetCurrentlyActiveProgram(UINT uiID) { s_ActiveShaderProgram = uiID; };
	private:
		
		UNDONE_API void OnParentSet( );
		
		UniformDataInterface			m_DataInterface;
		vector<int>						m_UniformDataLocations;
		vector<MaterialProperty>		m_Properies;

		DPointer<ShaderProgram>			m_ppShaderProgram;

		int								m_num_parents;
		int								m_instances;
		bool							m_loaded;
		
		static unsigned int				s_ActiveShaderProgram;

	};
};

#endif