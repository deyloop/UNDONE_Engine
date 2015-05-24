#pragma once

#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
using std::vector;

typedef unsigned position;
#define BLACK_SPACE 0
#define WALL BLACK_SPACE
#define SPACE 1
#define at_(x,y)(x+y*(m_size))
class Maze{
public:
	vector<unsigned>	 data;

	Maze();
	void Generate(unsigned size);

private:
	vector<position> m_wall_list;
	unsigned		 m_size;

	bool In_wall_list	(position place);
	void AddSpace		(position place);
	void AddWall		(position place);
	position get_opp_side(position p);
	bool edge_condition	 (position p);
	void AddExit();
};
#endif