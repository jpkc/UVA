#include <iostream>
#include <utility>
#include <deque>
#include <vector>

#define VISUAL_FEEDBACK 0

using namespace std;

//TODO:	Migrar para C puro. Implementar com BFS. Prmeiro do fogo, depois do Joe. Joe só pode avançar se a posição dele estiver com t menor que a do fogo, onde t é o valor do vetor visited.
//			Deve ser mais lenta que a iterativa pois precisa verificar todo o DFS do Fogo e não apenas o necessário

enum JOE_STATUS {
	MORTO		= 1,
	CORRENDO	= 2,
	SALVO		= 4
};

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
	JOE_STATUS status = MORTO;
	block_pos = casted_block->front();
	casted_block->pop_front();

	proxy.first = block_pos.first - 1;
	proxy.second = block_pos.second;
	if(proxy.first >= 0) {
		if((*maze)[proxy.second][proxy.first] == '.') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == MORTO) {
				status = CORRENDO;
			}
		} else if((*maze)[proxy.second][proxy.first] == 'J' && block == 'F') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == MORTO) {
				status = CORRENDO;
			}
		}
	} else {
		status = SALVO;
	}

	proxy.first = block_pos.first + 1;
	proxy.second = block_pos.second;
	if(proxy.first <  (int)(*maze)[0].size()) {
		if((*maze)[proxy.second][proxy.first] == '.') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == MORTO) {
				status = CORRENDO;
			}
		} else if((*maze)[proxy.second][proxy.first] == 'J' && block == 'F') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == MORTO) {
				status = CORRENDO;
			}
		}
	} else {
		status = SALVO;
	}

	proxy.first = block_pos.first;
	proxy.second = block_pos.second - 1;
	if(proxy.second >= 0) {
		if((*maze)[proxy.second][proxy.first] == '.') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == MORTO) {
				status = CORRENDO;
			}
		} else if((*maze)[proxy.second][proxy.first] == 'J' && block == 'F') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == MORTO) {
				status = CORRENDO;
			}
		}
	} else {
		status = SALVO;
	}

	proxy.first = block_pos.first;
	proxy.second = block_pos.second + 1;
	if(proxy.second < (int) maze->size()) {
		if((*maze)[proxy.second][proxy.first] == '.') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == MORTO) {
				status = CORRENDO;
			}
		} else if((*maze)[proxy.second][proxy.first] == 'J' && block == 'F') {
			(*maze)[proxy.second][proxy.first] = block;
			casted_block->push_back(proxy);
			if(status == MORTO) {
				status = CORRENDO;
			}
		}
	} else {
		status = SALVO;
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

	int joe_status = CORRENDO;
	int time = 1;
	for(; joe_status == CORRENDO; ++time) {
		joe_status = MORTO;
		for(unsigned int l = casted_fire.size(); l > 0; --l) {
			MazeMark(&maze, &casted_fire, 'F');
		}
		if(VISUAL_FEEDBACK) {
			cout << endl;
			MazePrint(&maze, r, c);
		}

		for(unsigned int l = casted_joe.size(); l > 0; --l) {
			int status = MazeMark(&maze, &casted_joe, 'J');
			if(status == SALVO) {
				return time;
			} else if(status == CORRENDO) {
				joe_status = CORRENDO;
			}
		}
		if(VISUAL_FEEDBACK) {
			cout << endl;
			MazePrint(&maze, r, c);
		}
	}
	return 0;
}

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
