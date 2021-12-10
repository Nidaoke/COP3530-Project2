#include <iostream>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include "Graph.h"
#include <math.h>
#include <unordered_set> 
using namespace std;


//inspired by Aman's pseudocode
//Following PseudoCode from slides using 2set and 2array method
vector<Node*> dijkstra(Graph& graph, Node* src, Node* endNode) {
    int numVertices = 47 * 47 * 47;
    unordered_set<Node*> computedVertices = {src}, nonComputedVertices;
    unordered_map<Node*, int> distances;
    vector<Node*> v;
    unordered_map<Node*, Node*> predecessors;
    for (auto i : graph.adjList) {
        distances[i.first] = INT_MAX;
    }
    for (auto i : graph.adjList) {

        if (i.first != src) {
            nonComputedVertices.insert(i.first);
            for (auto v : graph.adjList[src])
                if (v.first == i.first) {
                    distances[i.first] = v.second;
                    break;
                }
        }
    }
    distances[src] = 0;
    v.push_back(src);
    while(!nonComputedVertices.empty()){
        Node* index = src;
        int smallestVal = INT_MAX;
        
        for (auto v:nonComputedVertices)
            if (distances[v]<smallestVal){
                index = v;
                smallestVal = distances[v];
            }
        nonComputedVertices.erase(index);
        computedVertices.insert(index);
        v.push_back(index);
        for (auto v : graph.adjList[index]) {
            if (distances[index] + v.second < distances[v.first]) {
                distances[v.first] = distances[index] + v.second;
                predecessors[v.first] = index;
            }
        }
        if (computedVertices.find(endNode) != computedVertices.end()) {
            return v;
        }
    }
    return v;
}



double findH(Node* node1, Node* node2){ //sqrt((x-x2)^2  + (y-y2)^2 + (z-z2)^2) finding the distance between two points
    //x,y,z of first node
    int x1 = node1->xPos;
    int y1 = node1->yPos;
    int z1 = node1->zPos;
    //x,y,z of second node
    int x2 = node2->xPos;
    int y2 = node2->yPos;
    int z2 = node2->zPos;
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

vector <Node*> a_star(Graph& graph, Node* start_node, Node* target_node) { //parameters: graph, start_node, target_node
    set <Node*> visited = {};
    vector<Node*> v;
    priority_queue< Node*, vector<Node*>, minF > unvisited;
    Node* current;

    start_node->g_score = 0;
    start_node->f_score = findH(start_node, target_node);
    start_node->prev = nullptr;
    unvisited.push(start_node);
    start_node->aSeen = true;

    bool finished = false;
    while (!finished) {
        int tempG = 0;
        
        if (unvisited.empty()) { //if empty then they have all been visited
            
            finished = true;
        }
        else {
            current = unvisited.top();
            unvisited.pop();
            if (current == target_node) {
                
                finished = true;
                //copying data to visited map
                visited.insert(current);
                v.push_back(current);
            }
            else {
                for (auto iter : graph.adjList[current]) { //something might get destroyed here
                    Node* neighbor = iter.first;
                    if (visited.find(neighbor) == visited.end()) { //if not in visited map
                        tempG = current->g_score + graph.adjList[current][neighbor]; //weight to travel to the neighbor

                        if (tempG < neighbor->g_score) { //the weight to travel is less than the weight to travel to the neighbor
                            neighbor->g_score = tempG;
                            neighbor->f_score = tempG + findH(neighbor, target_node);
                            neighbor->prev = current;
                            if (neighbor->aSeen == false) {
                                neighbor->aSeen = true;
                                unvisited.push(neighbor);
                            }
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
    vector<Node*> aPath = a_star(g, g.getStartNode(), g.getEndNode());
    //vector <Node*> path = dijkstra(g, g.getStartNode(), g.getEndNode());
    /*for (auto iter : path) {
        cout << iter->xPos << " " << iter->yPos << " " << iter->zPos << endl;
        
    }*/
    cout << "A*: " << aPath.size() << endl;
    vector<Node*> path = dijkstra(g, g.getStartNode(), g.getEndNode());
    cout << "Dijkstras: " << path.size() << endl;;
   

}