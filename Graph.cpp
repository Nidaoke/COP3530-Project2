#include "Graph.h"

void Node::NeighborWalls() {
	for (int i = 0; i < 6; i++) {
		neighbors.push_back(nullptr);
	}
}

void Data::InitializeNodes() {

	std::random_device ran;
	std::mt19937 rng(ran());
	std::uniform_int_distribution<int> range(0, 1);

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			for (int z = 0; z < 4; z++) {
				Node* temp = new Node();
				temp->NeighborWalls();
				Cube[x][y][z] = temp;
				temp->xPos = x;
				temp->yPos = y;
				temp->zPos = z;
			}
		}
	}

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			for (int z = 0; z < 4; z++) {
				Node* temp = Cube[x][y][z];
				if (x == 0 & y == 0 && z == 0) {
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[3] = Cube[x][y][z + 1];
					temp->neighbors[5] = Cube[x][y + 1][z];
				}
				else if (x == 3 & y == 3 && z == 3) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[2] = Cube[x][y][z - 1];
					temp->neighbors[4] = Cube[x][y - 1][z];
				}
				else if (x == 3 & y == 0 && z == 0) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[3] = Cube[x][y][z + 1];
					temp->neighbors[5] = Cube[x][y + 1][z];
				}
				else if (x == 0 & y == 3 && z == 0) {
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[3] = Cube[x][y][z + 1];
					temp->neighbors[4] = Cube[x][y - 1][z];
				}
				else if (x == 0 & y == 0 && z == 3) {
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z - 1];
					temp->neighbors[5] = Cube[x][y + 1][z];
				}
				else if (x == 0 & y == 3 && z == 3) {
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z - 1];
					temp->neighbors[4] = Cube[x][y - 1][z];
				}
				else if (x == 3 & y == 0 && z == 3) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[2] = Cube[x][y][z - 1];
					temp->neighbors[5] = Cube[x][y + 1][z];
				}
				else if (x == 3 & y == 3 && z == 0) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[3] = Cube[x][y][z + 1];
					temp->neighbors[4] = Cube[x][y - 1][z];
				}
				else if (x == 0 & y == 0) {
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z + 1];
					temp->neighbors[3] = Cube[x][y][z - 1];
					temp->neighbors[5] = Cube[x][y + 1][z];
				}
				else if (x == 3 & y == 3) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[2] = Cube[x][y][z + 1];
					temp->neighbors[3] = Cube[x][y][z - 1];
					temp->neighbors[4] = Cube[x][y - 1][z];
				}
				else if (x == 0 & z == 0) {
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[3] = Cube[x][y][z + 1];
					temp->neighbors[4] = Cube[x][y + 1][z];
					temp->neighbors[5] = Cube[x][y - 1][z];
				}
				else if (x == 3 & z == 3) {
					temp->neighbors[1] = Cube[x - 1][y][z];
					temp->neighbors[3] = Cube[x][y][z - 1];
					temp->neighbors[4] = Cube[x][y + 1][z];
					temp->neighbors[5] = Cube[x][y - 1][z];
				}
				else if (y == 0 & z == 0) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[3] = Cube[x][y][z + 1];
					temp->neighbors[5] = Cube[x][y + 1][z];
				}
				else if (y == 3 & z == 3) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z - 1];
					temp->neighbors[4] = Cube[x][y - 1][z];
				}
				else if (x == 3) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[2] = Cube[x][y][z + 1];
					temp->neighbors[3] = Cube[x][y][z - 1];
					temp->neighbors[4] = Cube[x][y + 1][z];
					temp->neighbors[5] = Cube[x][y - 1][z];
				}
				else if (x == 0) {
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z + 1];
					temp->neighbors[3] = Cube[x][y][z - 1];
					temp->neighbors[4] = Cube[x][y + 1][z];
					temp->neighbors[5] = Cube[x][y - 1][z];
				}
				else if (y == 3) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z + 1];
					temp->neighbors[3] = Cube[x][y][z - 1];
					temp->neighbors[5] = Cube[x][y - 1][z];
				}
				else if (y == 0) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z + 1];
					temp->neighbors[3] = Cube[x][y][z - 1];
					temp->neighbors[5] = Cube[x][y + 1][z];
				}
				else if (z == 3) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z - 1];
					temp->neighbors[4] = Cube[x][y + 1][z];
					temp->neighbors[5] = Cube[x][y - 1][z];
				}
				else if (z == 0) {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[3] = Cube[x][y][z + 1];
					temp->neighbors[4] = Cube[x][y + 1][z];
					temp->neighbors[5] = Cube[x][y - 1][z];
				}
				else {
					temp->neighbors[0] = Cube[x - 1][y][z];
					temp->neighbors[1] = Cube[x + 1][y][z];
					temp->neighbors[2] = Cube[x][y][z - 1];
					temp->neighbors[3] = Cube[x][y][z + 1];
					temp->neighbors[4] = Cube[x][y + 1][z];
					temp->neighbors[5] = Cube[x][y - 1][z];
				}
			}
		}
	}
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			for (int z = 0; z < 4; z++) {
				Node* temp = Cube[x][y][z];
				for (int m = 0; m < temp->neighbors.size(); m++) {
					if (temp->neighbors[m] != nullptr) {
						int ranInt = range(rng);
						if (ranInt == 1 || ranInt == 0) {
							if (temp->seen[m] != true) {
								temp->seen[m] = true;
								if (m == 0) {
									temp->neighbors[m]->seen[1] = true;
									temp->neighbors[m]->noWall[1] = true;
									temp->noWall[m] = true;
								}
								else if (m == 1) {
									temp->neighbors[m]->seen[0] = true;
									temp->neighbors[m]->noWall[0] = true;
									temp->noWall[m] = true;
								}
								else if (m == 2) {
									temp->neighbors[m]->seen[3] = true;
									temp->neighbors[m]->noWall[3] = true;
									temp->noWall[m] = true;
								}
								else if (m == 3) {

									temp->neighbors[m]->seen[2] = true;
									temp->neighbors[m]->noWall[2] = true;
									temp->noWall[m] = true;

								}
								else if (m == 4) {
									temp->neighbors[m]->seen[5] = true;
									temp->neighbors[m]->noWall[5] = true;
									temp->noWall[m] = true;
								}
								else if (m == 5) {
									temp->neighbors[m]->seen[4] = true;
									temp->neighbors[m]->noWall[4] = true;
									temp->noWall[m] = true;
								}
							}

						}

						else if (ranInt == 2) {
							if (temp->seen[m] != true) {
								temp->seen[m] = true;
								if (m == 0) {
									temp->neighbors[m]->seen[1] = true;
								}
								else if (m == 1) {
									temp->neighbors[m]->seen[0] = true;
								}
								else if (m == 2) {
									temp->neighbors[m]->seen[3] = true;
								}
								else if (m == 3) {
									temp->neighbors[m]->seen[2] = true;
								}
								else if (m == 4) {
									temp->neighbors[m]->seen[5] = true;
								}
								else if (m == 5) {
									temp->neighbors[m]->seen[4] = true;
								}
							}
						}
					}
				}
			}
		}
	}
}



void Graph::InitializeGraph() {
	nodes.InitializeNodes();
	std::random_device ran;
	std::mt19937 rng(ran());
	std::uniform_int_distribution<int> range(1, 4);
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			for (int z = 0; z < 4; z++) {
				Node* temp = nodes.Cube[x][y][z];
				adjList[temp];
				if (x == 0 && y == 0 && z == 0) {
					endNode = temp;
				}
				else if (x == 3 && y == 3 && z == 3) {
					startNode = temp;
				}
				for (int i = 0; i < temp->neighbors.size(); i++) {
					if (temp->neighbors[i] != nullptr) {
						if (temp->noWall[i]) {
							int ranInt = range(rng);
							adjList[temp][temp->neighbors[i]] = ranInt;
						}
					}
				}
			}
		}
	}
}

void Graph::TestGraph() {
	/*for (int x = 0; x < 47; x++) {
		for (int y = 0; y < 47; y++) {
			for (int z = 0; z < 47; z++) {
				Node* temp = nodes.Cube[x][y][z];
				cout << "Current Node " << temp->xPos << " " << temp->yPos << " " << temp->zPos << endl;
				for (auto v : adjList[temp]) {
					cout << "XYZ: " << v.first->xPos << " " << v.first->yPos << " " << v.first->zPos << endl;
					cout << "Weight: " << v.second << endl;
				}
				cout << '\n';
			}
		}
	}*/
	/*cout << startNode->xPos << startNode->yPos << startNode->zPos << endl;
	cout << endNode->xPos << endNode->yPos << endNode->zPos << endl;*/
	/*Node* temp = nodes.Cube[0][0][0];
	for (auto v : adjList[temp]) {
		cout << "XYZ: " << v.first->xPos << " " << v.first->yPos << " " << v.first->zPos << endl;
		cout << "Weight: " << v.second << endl;
	}*/
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			for (int z = 0; z < 4; z++) {
				Node* temp = nodes.Cube[x][y][z];
				cout << "-";
			}
			
		}
	}
}

unordered_map<Node*, unordered_map<Node*, int>> Graph::getAdjList() {
	return adjList;
}

Node* Graph::getStartNode() {
	return startNode;
}

Node* Graph::getEndNode() {
	return endNode;
}
