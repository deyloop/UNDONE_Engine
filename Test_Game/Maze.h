/******************************************************************************
File	:	Maze.h
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