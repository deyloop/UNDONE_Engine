#pragma once
#ifndef _MAZE_SCRIPT_H_
#define _MAZE_SCRIPT_H_

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Undone_Engine.h>
#include "Maze.h"

using namespace std;
using namespace UNDONE_ENGINE;

class MazeScript : public Behavior {
	vector<string> material;
	Dptr<unGameObject> maze_object;
	Dptr<unMesh> cube_mesh;
public:
	void Load( ) {
		Input->RegisterCallback(bind(&MazeScript::Regenerate,this),"Reg");
		srand(time(0));
		cube_mesh					= Objectbuffer->CreateNew_Mesh( );
		Regenerate( );
	}

	void UnLoad( ) {

	}

	void SetMaterials(vector<string> mats ) {
		material = mats;
	}

	void Regenerate( ) {
		Objectbuffer->Delete_GameObject(maze_object);
		#define SIZE 30

		maze_object = Objectbuffer->CreateNew_GameObject( );
		Dptr<unGameObject> Floor				= Objectbuffer->CreateNew_GameObject( );
		Dptr<unWorldTransform> Floor_Transform	= Objectbuffer->CreateNew_WorldTransform( );
		Dptr<unGraphic3D> Floor_Graphic			= Objectbuffer->CreateNew_Graphic3D( );
		
		Floor->AddWorldTransform(Floor_Transform);
		Floor->AddMesh(cube_mesh);
		Floor->AddGraphicMaterial(Objectbuffer->Get_GraphicMaterial_ByName(material.at(rand()%5).c_str()));
		Floor->AddGraphic3D(Floor_Graphic);
		
		Floor_Transform->ScaleAbs(SIZE*2, 0.05, SIZE*2);
		Floor_Transform->TranslateAbs(0,-0.5,0 );

		m_GameObject->AddGameObject(maze_object);
		maze_object->AddGameObject(Floor);
		Maze maze;
		maze.Generate(SIZE);

		for (int j = 0; j<SIZE; ++j) {
			for (int i = 0;i<SIZE; ++i) {

				if (maze.data[i+j*SIZE] == SPACE) continue;

				Dptr<unGameObject> go_scene		= Objectbuffer->CreateNew_GameObject( );
				Dptr<unWorldTransform> transform1 = Objectbuffer->CreateNew_WorldTransform( );
				Dptr<unGraphic3D> graphic1		= Objectbuffer->CreateNew_Graphic3D( );
				
				go_scene->AddWorldTransform(transform1);
				go_scene->AddMesh(cube_mesh);
				go_scene->AddGraphicMaterial(Objectbuffer->Get_GraphicMaterial_ByName(material.at(rand()%5).c_str()));
				go_scene->AddGraphic3D(graphic1);
				
				transform1->TranslateAbs((-SIZE)/2+(float)i, 0,(float)j-SIZE/2);
				transform1->ScaleAbs(0.5f, (float)1, 0.5f);

				maze_object->AddGameObject(go_scene);
			}
		}
		//maze_object->Load( );
	}
};
#endif