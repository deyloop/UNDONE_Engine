/******************************************************************************
Project	:	UNDONE Engine
File	:	GraphicMaterial.h
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
	class GraphicMaterial : public unGraphicMaterial, public Component {
	public:
		GraphicMaterial( );
		~GraphicMaterial( ) { Release( ); }

		void Release( ) { Unload( ); };

		void OnParentBeingChilded( );
		void SetShaderProgramToUse(Dptr<unShaderProgram> ppShaderProgram);

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

		Dptr<ShaderProgram>			m_ppShaderProgram;

		int								m_num_parents;
		int								m_instances;
		bool							m_loaded;
		
		static unsigned int				s_ActiveShaderProgram;

	};
};

#endif