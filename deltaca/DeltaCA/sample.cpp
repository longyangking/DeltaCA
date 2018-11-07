/*
The C/C++ template to use DeltaCA
*/

#include "deltaca.h"
#include "stdio.h"

#define Nx 50
#define Ny 50
#define Ts 200

int func(
	int own, int up, int down, int  left, int  right,
	int upright, int downright, int  upleft, int downleft
) {
	int sum = up + down + left + right + upright + downright + upleft + downleft;
	int flag = (sum == 3) || (sum == 2) || (sum==1);
	return flag;
};

int main(int argc, char **argv) {
	World world = World(func, Nx, Ny);
	int** cells = world.get_cells();

	printf("Starting to evolving...\n");
	for (int i = 0; i < Ts; i++) {
		world.update();
		cells = world.get_cells();
		if (i % 20 == 0) {
			printf("Time step: %d \n", i);
		}
	}

	FILE *fp = NULL;
	fp = fopen("result.txt", "w+");
	for (int i = 0; i < Nx; i++) {
		for (int j = 0; j < Ny; j++) {
			fprintf(fp, "%d ", cells[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	return 0;
}