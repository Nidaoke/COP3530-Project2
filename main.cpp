#include <iostream>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include "Graph.h"
#include <math.h>
#include <map>
#include <unordered_set> 
using namespace std;


#include <unordered_set> //Following PseudoCode from slides using 2set and 2array method
vector<int> dijkstra(Graph& graph, int src) {
    int numVertices = 47 * 47 * 47;
    unordered_set<int> computedVertices = { src }, nonComputedVertices;
    vector<int> distances(numVertices, 2147483647);
    vector<int>predecessor;
    for (int i = 0; i < graph.adjList.size(); i++)
        if (i != src) {
            nonComputedVertices.insert(i);
            for (auto v : graph.adjList[src])
                if (v.first == i) {
                    distances[i] = v.second;
                    break;
                }
        }
    distances[src] = 0;
    while (!nonComputedVertices.empty()) {
        int index = src, smallestVal = 2147483647;
        for (auto v : nonComputedVertices)
            if (distances[v] < smallestVal) {
                index = v;
                smallestVal = distances[v];
            }
        nonComputedVertices.erase(index);
        computedVertices.insert(index);
        for (auto v : graph.adjList[index])
            if (distances[index] + v.second < distances[v.first]) {
                distances[v.first] = distances[index] + v.second;
                predecessor[v.first] = index;
            }
    }
    return distances;
}
double findH(int node1, int node2){ //sqrt((x-x2)^2  + (y-y2)^2 + (z-z2)^2) finding the distance between two points
    //x,y,z of first node
    int calc = pow(47, 2);
    int x1 = (node1 % calc) % 47;
    int y1 = (node1 % calc) / 47;
    int z1 = node1 / calc;
    //x,y,z of second node
    int x2 = (node2 % calc) % 47;
    int y2 = (node2 % calc) / 47;
    int z2 = node2 / calc;
    //differences of x, y, and z
    int diffX = x1-x2;
    int diffY = y1-y2;
    int diffZ = z1-z2;
    //x,y,z squared
    int xSquared = pow(diffX, 2);
    int ySquared = pow(diffY, 2);
    int zSquared = pow(diffZ, 2);
    double result = sqrt(xSquared + ySquared + zSquared);
    return result;
}

vector <int> a_star(Graph& graph, int start, int target) { //parameters: graph, start_node, target_node
    set <int> visited = {};
    vector<int> v;
    map<double, int> uv; 
    int current;
    int numVertices = 47 * 47 * 47;
    int g_score = 0;
    double f_score = findH(start, target);
    uv[f_score] = start;
    vector<int> distances(numVertices, 2147483647);
    vector<int>predecessor;
    for (int i = 0; i < graph.adjList.size(); i++)
        if (i != start) {
            
            for (auto v : graph.adjList[start])
                if (v.first == i) {
                    distances[i] = v.second;
                    break;
                }
        }
    bool finished = false;
    while (!finished) {
        int tempG = 0;
        
        if (uv.empty()) { //if empty then they have all been visited
            
            finished = true;
        }
        else {
            auto iter = uv.begin();
            current = iter->second;
            uv.erase(iter);
            if (current == target) {
                
                finished = true;
                //copying data to visited map
                visited.insert(current);
                v.push_back(current);
            }
            else {
                for (auto iter : graph.adjList[current]) { //something might get destroyed here
                    int neighbor = iter.first;
                    if (visited.find(neighbor) == visited.end()) { //if not in visited map
                        tempG = distances[current] + graph.adjList[current][neighbor]; //weight to travel to the neighbor

                        if (tempG < distances[neighbor]) { //the weight to travel is less than the weight to travel to the neighbor
                 
                            f_score = tempG + findH(neighbor, target);

                            
                            uv[f_score] = neighbor;
                            
                        }
                    }
                }
                visited.insert(current);
                v.push_back(current);
            }
        }
    }

    return v;
}


int main(){
    Graph g;
    g.InitializeGraph();
    //g.TestGraph();

}
