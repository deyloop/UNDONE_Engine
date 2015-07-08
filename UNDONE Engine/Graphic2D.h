/******************************************************************************
Project	:	UNDONE Engine
File	:	Graphic2D.h
Author	:	Anurup Dey
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

	class Graphic2D : public Component, public unGraphic2D {
	public:
		Graphic2D( );
		~Graphic2D( );

		static void InitVAO( );
		static void DeleteVAO( );

		void Load( );
		void Render(_2DRenderParams& render_params );
		void Unload( );

		void OnParentBeingChilded( ) { };
		void SetTexture(DPointer<unTexture> ppTex);
		void SetImageRect(rect& rectref);

		static void SetShader(DPointer<ShaderProgram> ppShaderProgram);
		static void SetScreenDimentions(int h, int w) {
			screenhieght = h;
			screenwidth = w;
		}

	private:
		void OnParentSet( );
		DPointer<Texture>				m_ppTexture;
		DPointer<WorldTransform>		m_ppWorldTransform;

		static int HMVP ;
		static int HSampler;
		int HRECT;

		static DPointer<ShaderProgram>	m_ppShaderProgram;
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

