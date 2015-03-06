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
#include "glm.hpp"

namespace UNDONE_ENGINE {
	
	class Texture;
	class WorldTransform;
	class ShaderProgram;
	
	struct _2DRenderParams{
		glm::mat4 ProjectionMat;
	};

	class UNDONE_API _2DGraphic : public Component {
	public:
		_2DGraphic( );
		~_2DGraphic( );

		void Load( );
		void Render(_2DRenderParams& render_params );
		void Unload( );

		void OnParentBeingChilded( ) { };
		void SetTexture(DPointer<Texture> ppTex );

		static void SetShader(DPointer<ShaderProgram> ppShaderProgram);
	private:
		void OnParentSet( );
		DPointer<Texture>				m_ppTexture;
		DPointer<WorldTransform>		m_ppWorldTransform;
		static DPointer<ShaderProgram>	m_ppShaderProgram;
		static unsigned					m_uiVBO[2];
		static unsigned					m_uiVAO[1];
	};
}

#endif

