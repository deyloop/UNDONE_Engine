/******************************************************************************
Project	:	UNDONE Engine
File	:	_2DGraphic.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _2DGRAPHIC_H_
#define _2DGRAPHIC_H_

#include "Component.h"
#include <glm.hpp>

namespace UNDONE_ENGINE {
	
	class Texture;
	class WorldTransform;
	class ShaderProgram;
	
	struct _2DRenderParams{
		glm::mat4 ProjectionMat;
	};

	struct UNDONE_API rect {
		float x, y, width, hieght;
	};

	class _2DGraphic : public Component {
	public:
		UNDONE_API _2DGraphic( );
		UNDONE_API ~_2DGraphic( );

		static void InitVAO( );
		static void DeleteVAO( );

		UNDONE_API void Load( );
		void Render(_2DRenderParams& render_params );
		UNDONE_API void Unload( );

		void OnParentBeingChilded( ) { };
		UNDONE_API void SetTexture(DPointer<Texture> ppTex);
		UNDONE_API void SetImageRect(rect& rectref);

		static void SetShader(DPointer<ShaderProgram> ppShaderProgram);
		static void SetScreenDimentions(int h, int w) {
			screenhieght = h;
			screenwidth = w;
		}

	private:
		UNDONE_API void OnParentSet( );
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

