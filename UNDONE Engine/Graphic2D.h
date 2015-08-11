/******************************************************************************
Project	:	UNDONE Engine
File	:	Graphic2D.h
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

#ifndef _2DGRAPHIC_H_
#define _2DGRAPHIC_H_

#include "Component.h"
#include "unGraphic2D.h"
#include <glm.hpp>

namespace UNDONE_ENGINE {
	
	class ShaderProgram;
	class WorldTransform;
	class Texture;

	struct _2DRenderParams{
		glm::mat4 ProjectionMat;
	};

	class Graphic2D : public unGraphic2D, public Component {
	public:
		Graphic2D( );
		~Graphic2D( );

		static void InitVAO( );
		static void DeleteVAO( );

		void Load( );
		void Render(_2DRenderParams& render_params );
		void Unload( );

		void OnParentBeingChilded( ) { };
		void SetTexture(Dptr<unTexture> ppTex);
		void SetImageRect(rect& rectref);

		static void SetShader(Dptr<ShaderProgram> ppShaderProgram);
		static void SetScreenDimentions(int h, int w) {
			screenhieght = h;
			screenwidth = w;
		}

	private:
		void OnParentSet( );
		Dptr<Texture>				m_ppTexture;
		Dptr<WorldTransform>		m_ppWorldTransform;

		static int HMVP ;
		static int HSampler;
		int HRECT;

		static Dptr<ShaderProgram>	m_ppShaderProgram;
		static unsigned					m_uiVBO[3];
		static unsigned					m_uiVAO[1];
		
		static int screenwidth;
		static int screenhieght;

		glm::mat4						m_ScaleCorrection;
		glm::mat4						m_TranslateCorrection;
		rect							m_rect;
	};
}

#endif

