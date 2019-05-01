//UVA problem 11624 - Fire! Solution by jpkc

#include <iostream>
#include <utility>
#include <deque>
#include <vector>

#define VISUAL_FEEDBACK 0

using namespace std;

//TODO:	Code optimization round. 
//				1: Switch to C and manually alloc memory. Avoiding <vector> allocation should drastically enhance speed.
//				2: Test a BFS approach. First fire's maze run and than Joe's. Joe can only jump to positions where his t is smaller than the fire's where t is the cell's visited vector value. Beautiful but slower because maps whole maze , not just what's necessary.

enum JOE_STATUS {
	DEAD		= 1,
	RUNNING	= 2,
	SAFE		= 4
};

void MazePrint(vector <vector <char>> *maze, unsigned int r, unsigned int c);
JOE_STATUS MazeMark(vector <vector <char> > *maze, deque<pair<int, int> > *casted_block, char block);
int MazeRun();


int main(int argc, char *argv[])
{
	unsigned int n;
	cin >> n;
	for(unsigned int k = 0; k < n; ++k) {
		if(VISUAL_FEEDBACK) {
			cout << k << endl;
		}
		int t = MazeRun();
		if(t) {
			cout << t << endl;
		} else {
			cout << "IMPOSSIBLE" << endl;
		}
	}
	return 0;
}

void MazePrint(vector <vector <char>> *maze, unsigned int r, unsigned int c) {
	for(unsigned j = 0; j < c; ++j) {
		for(unsigned i = 0; i < r; ++i) {
			cout << (*maze)[j][i] << " ";
		}
		cout << endl;
	}
}

JOE_STATUS MazeMark(vector <vector <char> > *maze, deque<pair<int, int> > *casted_block, char block) {
	pair<int, int> block_pos, proxy;
	JOE_STATUS status = DEAD;
	block_pos = casted_block->front();
	casted_block->pop_front();

	proxy.first = block_pos.first - 1;
	proxy.second = block_pos.second;
	if(proxy.first >= 0) {
		if((*maze)[proxy.second][proxy.first] == '.') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == DEAD) {
				status = RUNNING;
			}
		} else if((*maze)[proxy.second][proxy.first] == 'J' && block == 'F') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == DEAD) {
				status = RUNNING;
			}
		}
	} else {
		status = SAFE;
	}

	proxy.first = block_pos.first + 1;
	proxy.second = block_pos.second;
	if(proxy.first <  (int)(*maze)[0].size()) {
		if((*maze)[proxy.second][proxy.first] == '.') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == DEAD) {
				status = RUNNING;
			}
		} else if((*maze)[proxy.second][proxy.first] == 'J' && block == 'F') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == DEAD) {
				status = RUNNING;
			}
		}
	} else {
		status = SAFE;
	}

	proxy.first = block_pos.first;
	proxy.second = block_pos.second - 1;
	if(proxy.second >= 0) {
		if((*maze)[proxy.second][proxy.first] == '.') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == DEAD) {
				status = RUNNING;
			}
		} else if((*maze)[proxy.second][proxy.first] == 'J' && block == 'F') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == DEAD) {
				status = RUNNING;
			}
		}
	} else {
		status = SAFE;
	}

	proxy.first = block_pos.first;
	proxy.second = block_pos.second + 1;
	if(proxy.second < (int) maze->size()) {
		if((*maze)[proxy.second][proxy.first] == '.') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == DEAD) {
				status = RUNNING;
			}
		} else if((*maze)[proxy.second][proxy.first] == 'J' && block == 'F') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == DEAD) {
				status = RUNNING;
			}
		}
	} else {
		status = SAFE;
	}
	return status;
}

int MazeRun() {
	unsigned int r, c;
	vector <vector <char> >	maze;
	vector <char> maze_row;
	deque <pair <int, int> > casted_joe;
	deque <pair <int, int> > casted_fire;
	pair <int, int> joe_pos;
	pair <int, int> fire_pos;
	char cell;

	cin >> c >> r;
	for(unsigned j = 0; j < c; ++j) {
		maze_row.clear();
		for(unsigned i = 0; i < r; ++i) {
			cin >> cell;
			maze_row.push_back(cell);
			if(cell == 'J') {
				joe_pos.first = i;
				joe_pos.second = j;
				casted_joe.push_back(joe_pos);
			}
			if(cell == 'F') {
				fire_pos.first = i;
				fire_pos.second = j;
				casted_fire.push_back(fire_pos);
			}
		}
		maze.push_back(maze_row);
	}

	if(VISUAL_FEEDBACK) {
		cout << r << " " << c << endl;
		MazePrint(&maze, r, c);
	}

	int joe_status = RUNNING;
	int time = 1;
	for(; joe_status == RUNNING; ++time) {
		joe_status = DEAD;
		for(unsigned int l = casted_fire.size(); l > 0; --l) {
			MazeMark(&maze, &casted_fire, 'F');
		}
		if(VISUAL_FEEDBACK) {
			cout << endl;
			MazePrint(&maze, r, c);
		}

		for(unsigned int l = casted_joe.size(); l > 0; --l) {
			int status = MazeMark(&maze, &casted_joe, 'J');
			if(status == SAFE) {
				return time;
			} else if(status == RUNNING) {
				joe_status = RUNNING;
			}
		}
		if(VISUAL_FEEDBACK) {
			cout << endl;
			MazePrint(&maze, r, c);
		}
	}
	return 0;
}
