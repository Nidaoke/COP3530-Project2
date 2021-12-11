#include "Graph.h"

void Graph::InitializeGraph() {
	std::random_device ran;
	std::mt19937 rng(ran());
	std::uniform_int_distribution<int> range(1, 4);
	for (int x = 0; x < 47; x++) {
		for (int y = 0; y < 47; y++) {
			for (int z = 0; z < 47; z++) {
				int i = x + (y * 47) + (pow(47, 2) * z);
				adjList[i];
				if (x == 0 && y == 0 && z == 0) {
					end = i;
				}
				else if (x == 46 && y == 46 && z == 46) {
					start = i;
				}
				if (x == 0) {
					int ranInt = range(rng);
					adjList[i][i + 1] = ranInt;
				}
				else if (x == 46) {
					int ranInt = range(rng);
					adjList[i][i - 1] = ranInt;
				}
				else {
					int ranInt = range(rng);
					adjList[i][i + 1] = ranInt;
					ranInt = range(rng);
					adjList[i][i - 1] = ranInt;
				}
				if (y == 0) {
					int ranInt = range(rng);
					adjList[i][i + 47] = ranInt;
				}
				else if (y == 46) {
					int ranInt = range(rng);
					adjList[i][i - 47] = ranInt;
				}
				else {
					int ranInt = range(rng);
					adjList[i][i + 47] = ranInt;
					ranInt = range(rng);
					adjList[i][i - 47] = ranInt;
				}
				if (z == 0) {
					int ranInt = range(rng);
					int calc = pow(27, 2);
					adjList[i][i + calc] = ranInt;
				}
				else if (z == 46) {
					int ranInt = range(rng);
					int calc = pow(27, 2);
					adjList[i][i - calc] = ranInt;
				}
				else {
					int ranInt = range(rng);
					int calc = pow(47, 2);
					adjList[i][i + calc] = ranInt;
					ranInt = range(rng);
					adjList[i][i - calc] = ranInt;
				}
			}
		}
	}
}

void Graph::TestGraph() {
	
	for (int i = 0; i < adjList.size(); i++) {
		cout << "Current Node" << i << endl;
		for (auto j : adjList[i]) {
			cout << "Node: " << j.first << " Weight = " << j.second << endl;
		}
	}
}
