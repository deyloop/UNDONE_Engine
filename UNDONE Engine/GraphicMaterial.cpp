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
#include "GraphicMaterial.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include <glew.h>
#include <gl\GL.h>
#include "SystemComponent.h"
#include "UNDONE_DEBUG.h"

namespace UNDONE_ENGINE {

	/*-------------------------------------------------------------------------
	Default Constructor.
	-------------------------------------------------------------------------*/
	GraphicMaterial::GraphicMaterial( ) {
		m_num_parents = 0;
		m_ppShaderProgram.m_pointer = nullptr;
		m_loaded = false;
	}

	void GraphicMaterial::OnParentSet() {
		if (m_num_parents==0) {
			++m_num_parents;
			Load( );
			return;
		} else {
			++m_num_parents;
		}

	}

	void GraphicMaterial::OnParentBeingChilded( ) {

	}

	/*-----------------------------------------------------------------------------
	Sets the shader program which must be used to render the graphic.
	Parameters:
	[IN]	pProgram	:	the pointer to the program to be used.
	-----------------------------------------------------------------------------*/
	void GraphicMaterial::SetShaderProgramToUse(Dptr<unShaderProgram> ppProgram) {
		m_ppShaderProgram = dcast<ShaderProgram,unShaderProgram>(ppProgram);
		if (m_ppShaderProgram.m_pointer!=nullptr) {
			//fill out the uniform details.
			GLuint progID = m_ppShaderProgram->GetProgramID( );

			//get the number of uniforms
			GLint numActiveUniforms = 0;
			glGetProgramiv(progID, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

			GLint maxnamelength = 20;

			for (int uniform = 0; uniform < numActiveUniforms; ++uniform) {
				MaterialProperty newProperty;

				GLsizei actualLength = 0;
				char name[20];

				glGetActiveUniform(progID,
								   uniform,
								   maxnamelength,
								   &actualLength,
								   &newProperty.datalength,
								   &newProperty.gl_type,
								   name);
				std::string sname((char*)&name, actualLength);
				newProperty.name = sname;

				newProperty.uniform_data_location = glGetUniformLocation(progID, name);

				if (newProperty.name=="gMVP") {

					newProperty.in_interface = true;
					UniformData pair;
					pair.uniformType = UNIFORMTYPE_MODELVIEWPROJECTIONMATRIX;
					newProperty.type = UNIFORMTYPE_MODELVIEWPROJECTIONMATRIX;
					m_DataInterface.pairs.push_back(pair);

				} else if (newProperty.name=="gWorld") {

					newProperty.in_interface = true;
					UniformData pair;
					newProperty.type = UNIFORMTYPE_WORLDTRANSFORMATIONMATRIX;
					pair.uniformType = UNIFORMTYPE_WORLDTRANSFORMATIONMATRIX;
					m_DataInterface.pairs.push_back(pair);

				} else newProperty.type = UNIFORMTYPE_GLTYPE;



				if (newProperty.in_interface==false) {
					//we need to allocate memory and assign data to this uniform.
					//this uniform is a personal property of the material.
					//eg. - Diffuse color, Texture, etc.

					//We check the type of data that goes into this uniform.
					switch (newProperty.gl_type) {
						case GL_FLOAT:
							newProperty.data.Data_f = 0.0f;
							break;

						case GL_FLOAT_VEC2:
						{
							glm::vec2* vec = new glm::vec2(1.0f, 1.0f);
							newProperty.data.Data_fp = &vec[0][0];
							break;
						}
						case GL_FLOAT_VEC3:
						{
							glm::vec3* vec = new glm::vec3(1.0f, 1.0f, 1.0f);
							newProperty.data.Data_fp = &vec[0][0];
							break;
						}
						case GL_FLOAT_VEC4:
						{
							glm::vec4* vec = new glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
							newProperty.data.Data_fp = &vec[0][0];
							break;
						}
						case GL_INT:
						{
							newProperty.data.Data_i = 0;
							break;
						}
						case GL_BOOL:
						{
							newProperty.data.Data_b = false;
							break;
						}
						case GL_FLOAT_MAT2:
						{
							glm::mat2* mat = new glm::mat2(1.0f);
							newProperty.data.Data_fp = (float*)&mat[0][0];
							break;
						}
						case GL_FLOAT_MAT3:
						{
							glm::mat3* mat = new glm::mat3(1.0f);
							newProperty.data.Data_fp = (float*)&mat[0][0];
							break;
						}
						case GL_FLOAT_MAT4:
						{
							glm::mat4* mat = new glm::mat4(1.0f);
							newProperty.data.Data_fp = (float*)&mat[0][0];
							break;
						}
						case GL_SAMPLER_2D:
							break;
						case GL_SAMPLER_CUBE:
							break;

						case GL_INT_VEC2:
						case GL_INT_VEC3:
						case GL_INT_VEC4:

						case GL_BOOL_VEC2:
						case GL_BOOL_VEC3:
						case GL_BOOL_VEC4:
							break;
					} //switch on type.
				}//if block for property not in interface.

				m_Properies.push_back(newProperty);

			}//for loop over next uniforms discovered.
			coutput(name+" aquired Shader Program\n");
			m_loaded = true;
		}
	}

	void GraphicMaterial::Load( ) {
		//TODO: Add texture loading code here.
		//Just a call to texture::Load(), probably.
	}

	void GraphicMaterial::Unload( ) {
		
		if (!m_loaded) return;

		for (auto& property:m_Properies) {
			if (!property.in_interface) {
				switch (property.gl_type) {

					case GL_FLOAT_VEC2:
					case GL_FLOAT_VEC3:
					case GL_FLOAT_VEC4:
					
					case GL_FLOAT_MAT2:
					case GL_FLOAT_MAT3:
					case GL_FLOAT_MAT4:
						delete property.data.Data_fp;
						break;

					case GL_SAMPLER_2D:
						break;
					case GL_SAMPLER_CUBE:
						break;

					case GL_INT_VEC2:
					case GL_INT_VEC3:
					case GL_INT_VEC4:

					case GL_BOOL_VEC2:
					case GL_BOOL_VEC3:
					case GL_BOOL_VEC4:
						break;
				} //switch on type.
			}
		}
	}

	void GraphicMaterial::SetProperty(const char* property_name, float value) {
		if (m_loaded) {
			//traverse through the list of properties to get to the 
			//requested propery.
			for (auto& property:m_Properies) {
				if (property.name==property_name) {
					//we found the property,
					//TODO: add code to check type compatibility here,
					//		so that type missmatches do not occur.
					property.data.Data_f = value;
					break;
				}
			}
			return;
		}
	}

	void GraphicMaterial::SetDiffuseColor(float r, float g, float b) {
		SetProperty("gDiffuse", r, g, b );
	}

	void GraphicMaterial::SetProperty(const char* property_name, float x, float y, float z) {
		if (m_loaded) {
			//traverse through the list of properties to get to the 
			//requested propery.
			for (auto& property:m_Properies) {
				if (property.name==property_name) {
					//we found the property,
					//TODO: add code to check type compatibility here,
					//		so that type missmatches do not occur.
					glm::vec3* vec = new glm::vec3(x,y,z);
					property.data.Data_fp = &vec[0][0];
				}
			}
		}
	}

	void GraphicMaterial::ApplyMaterial( ) {
		if (m_ppShaderProgram.m_pointer==nullptr) return;

		m_ppShaderProgram->UseProgram( );

		//update uniforms.
		unsigned data_interface_index = 0;
		for (auto& property:m_Properies) {
			if (property.in_interface) {
				//get the uniform from interface.
				switch (property.gl_type) {
					case GL_FLOAT_MAT4:
						glUniformMatrix4fv(property.uniform_data_location,
										   1,
										   GL_FALSE,
										   m_DataInterface.pairs[data_interface_index].data.Data_fp
										   );
						++data_interface_index;
						break;
				}//end switch;
			} else {
				//fill from property list.
				switch (property.gl_type) {
					case GL_FLOAT:
						glUniform1f(property.uniform_data_location,
									property.data.Data_f);
						break;

					case GL_FLOAT_VEC2:
						glUniform2fv(property.uniform_data_location,
									 1,
									property.data.Data_fp);
						break;
					case GL_FLOAT_VEC3:
						glUniform3fv(property.uniform_data_location,
									 1,
									 property.data.Data_fp);
						break;
					case GL_FLOAT_VEC4:
						glUniform4fv(property.uniform_data_location,
									 1,
									 property.data.Data_fp);
						break;

					case GL_INT:
						glUniform1i(property.uniform_data_location,
									property.data.Data_i);
						break;

					case GL_FLOAT_MAT2:
						glUniformMatrix2fv(property.uniform_data_location,
										   1,
										   GL_FALSE,
										   property.data.Data_fp);
						break;
					case GL_FLOAT_MAT3:
						glUniformMatrix3fv(property.uniform_data_location,
										   1,
										   GL_FALSE,
										   property.data.Data_fp);
						break;
					case GL_FLOAT_MAT4:
						glUniformMatrix4fv(property.uniform_data_location,
										   1,
										   GL_FALSE,
										   property.data.Data_fp);
						break;

					case GL_SAMPLER_2D:
						break;
					case GL_SAMPLER_CUBE:
						break;

				}
			}
		}
	}

}