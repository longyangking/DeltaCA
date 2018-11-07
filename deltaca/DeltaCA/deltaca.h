#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>

class World
{
	public:
		World(int (*func)(int own, int up, int down, int  left, int  right, int upright, int downright, int  upleft, int downleft), int Nx, int Ny);
		~World();

		void reset();
		int** get_cells();
		void update();

	private:
		int Nx, Ny;
		int** cells;
		int** clone_cells();
		int (*func)(int own, int up, int down, int  left, int  right, int upright, int downright, int  upleft, int downleft);
};