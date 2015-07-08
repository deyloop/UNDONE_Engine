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
#include "unGraphicMaterial.h"
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
	class GraphicMaterial : public Component, public unGraphicMaterial {
	public:
		GraphicMaterial( );
		~GraphicMaterial( ) { Release( ); }

		void Release( ) { Unload( ); };

		void OnParentBeingChilded( );
		void SetShaderProgramToUse(DPointer<unShaderProgram> ppShaderProgram);

		UniformDataInterface& GetUniformDataInterface( ) { return m_DataInterface; };
		

		void Load( );
		void ApplyMaterial( );
		void Unload( );
		
		void SetDiffuseColor(float r, float g, float b);
		void SetProperty(const char* property_name, float value);
		void SetProperty(const char* property_name, int value) { };
		void SetProperty(const char* property_name,float x, float y, float z);
		void SetProperty(const char* property_name, float x, float y, float z, float w) { };
		//TODO: Add all types of property setters.

		static void SetCurrentlyActiveProgram(UINT uiID) { s_ActiveShaderProgram = uiID; };
		//Why should these guys track whic program is active? 
		//cant the programs track that themselves?

	private:
		
		void OnParentSet( );
		
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