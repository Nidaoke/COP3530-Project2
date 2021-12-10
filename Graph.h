#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <unordered_map>
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;


struct Node {
    // neighbors [0] = left
    // [1] = right
    // [2] front
    // [3] back
    // [4] up
    // [5] down
    // 1 = open
    // 2 = dirt
    // 3 = ice
    // 4 = rocks
    vector<Node*> neighbors;
    int xPos;
    int yPos;
    int zPos;
    int g_score = INT_MAX;
    double f_score = INT_MAX;
    Node* prev = nullptr;
    bool aSeen = false;
    bool seen[6] = { false };
    bool noWall[6] = { false };
    void NeighborWalls();
    bool operator>(Node* rhs) {
        return this->f_score > rhs->f_score;
    }
    //Node* prev = nullptr;
};

struct minF
{
    bool operator()(Node* lhs, Node* rhs) const
    {
        return lhs->f_score > rhs->f_score;
    }
};

struct Data {
    Node* Cube[4][4][4];
    void InitializeNodes();

};
class Graph {
    Data nodes;
    Node* startNode;
    Node* endNode;
public:
    void InitializeGraph();
    void TestGraph();
    unordered_map<Node*, unordered_map<Node*, int>> adjList;
    unordered_map<Node*, unordered_map<Node*, int>> getAdjList();
    Node* getStartNode();
    Node* getEndNode();
};
