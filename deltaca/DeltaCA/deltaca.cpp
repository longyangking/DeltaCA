/*
Main file for Cellular Automaton, which is based on OpenGL
*/

#include "deltaca.h"
#include "kernel.cuh"

World::World(int(*func)(int own, int up, int down, int left, int right, int upright, int downright, int upleft, int downleft), int Nx, int Ny)
{
	this->cells = new int*[Nx];
	for (int i = 0; i < Nx; i++) {
		this->cells[i] = new int[Ny];
		for (int j = 0; j < Ny; j++) {
			this->cells[i][j] = 1;
		}
	}
	for (int i = 0; i < Nx; i++) {
		this->cells[i][0] = 0;
		this->cells[i][Ny - 1] = 0;
	}
	for (int j = 0; j < Ny; j++) {
		this->cells[0][j] = 0;
		this->cells[Nx-1][j] = 0;
	}

	this->func = func;
	this->Nx = Nx;
	this->Ny = Ny;
}

World::~World()
{
	for (int i = 0; i < Nx; i++) {
		delete[] cells[i];
	}
	delete[] cells;
}

void World::reset()
{

}

int ** World::get_cells()
{
	return this->cells;
}

int ** World::clone_cells()
{
	int **_cells = new int*[Nx];
	for (int i = 0; i < Nx; i++) {
		_cells[i] = new int[Ny];
		for (int j = 0; j < Ny; j++) {
			_cells[i][j] = this->cells[i][j];
		}
	}
	return _cells;
}

void World::update()
{
	int **new_cells = this->clone_cells();
	for (int i = 1; i < Nx - 1; i++) {
		for (int j = 1; j < Ny - 1; j++) {
			int own = this->cells[i][j];
			int up = this->cells[i][j+1];
			int down = this->cells[i][j-1];
			int left = this->cells[i-1][j];
			int right = this->cells[i+1][j];
			int upright = this->cells[i+1][j+1];
			int upleft = this->cells[i+1][j-1];
			int downleft = this->cells[i-1][j-1];
			int downright = this->cells[i-1][j+1];
			new_cells[i][j] = this->func(own, up, down, left, right, upright, downright, upleft, downleft);
		}
	}

	for (int i = 0; i < Nx; i++) {
		delete[] this->cells[i];
	}
	delete[] this->cells;

	this->cells = new_cells;
}
