#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <unordered_map>
#include <map>
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

class Graph {
    
public:
    void InitializeGraph();
    void TestGraph();
    unordered_map<int, unordered_map<int, int>> adjList;
    int start;
    int end;
};
