#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

const int width = 32;
const int height = 32;

struct World {
    int map[width][height] = {{0}};
};

void generate_world(World *world,int w, int h){

	int random_bit;
	srand((unsigned int)time(NULL));
	for (int i=1; i<w-1; i++){
		for (int j=1; j<h-1; j++){

			random_bit = rand() % 2;

			world->map[i][j] = random_bit;
		}
	}


}

void update_world(World *world, int w, int h){
	for (int i=1; i<w-1; i++){
		for (int j=1; j<h-1; j++){

			int top_left = world->map[i-1][j-1];
			int top = world->map[i-1][j];
			int top_right = world->map[i-1][j+1];
			int bottom = world->map[i+1][j];
			int bottom_right = world->map[i+1][j+1];
			int bottom_left = world->map[i+1][j-1];
			int right = world->map[i][j+1];
			int left = world->map[i][j-1];

			int neighbour_count = top_left + top_right + top + right + left + bottom + bottom_left + bottom_right;

			if (neighbour_count < 2 && world->map[i][j] == 1){
				//Any live cell with fewer than two live neighbors dies, as if by underpopulation.
				world->map[i][j] = 0;
			}
			else if((neighbour_count == 2 || neighbour_count == 3) && world->map[i][j] == 1){
				//Any live cell with two or three live neighbors lives on to the next generation.
				world->map[i][j] = 1;
			}
			else if(neighbour_count > 3 && world->map[i][j] == 1){
				//Any live cell with more than three live neighbors dies, as if by overpopulation.
				world->map[i][j] = 0;
			}
			else if (neighbour_count == 3 && world->map[i][j] == 0){
				//Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
				world->map[i][j] = 1;
			}
		}
	}
}

void show_world(World world, int w, int h){

	for (int i=1; i<w-1; i++){
		for (int j=1; j<h-1; j++){

			if (world.map[i][j])
				cout << '+';
			else
				cout << '.';
		}
		cout << endl;

	}

	cout << "=============================\n";
}

int main(){
	World world;
	generate_world(&world, width, height);


	while (true){
		update_world(&world, width, height);
		show_world(world, width, height);
		usleep(1000000);
		//system("clear");
	}

	return 0;
}
