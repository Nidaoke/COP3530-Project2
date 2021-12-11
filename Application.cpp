#include "Game.h"
#include "Graph.h"
#include "wallToBuild.h"

#include <iostream>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include "Graph.h"
#include <math.h>
#include <unordered_set> 
#include <tuple>
#include <chrono>
using namespace std;


//inspired by Aman's pseudocode
//Following PseudoCode from slides using 2set and 2array method
std::pair<std::vector<int>, std::vector<int>> dijkstra(Graph& graph, int src, int endNode) {

    //std::tuple<int, int, int> srct = std::make_tuple(src->xPos, src->yPos, src->zPos);
    //std::tuple<int, int, int> endt = std::make_tuple(endNode->xPos, endNode->yPos, endNode->zPos);

    //std::cout<<"In Dijkstra"<<std::endl;
    int numVertices = 10*10*10;
    unordered_set<int> computedVertices = {src}, nonComputedVertices;
    unordered_map<int, int> distances;
    vector<int> v;
    unordered_map<int, int> predecessors;
    for (auto i:graph.adjList) {
        distances[i.first] = INT_MAX;
    }
    for (auto i:graph.adjList) {

        if (i.first!=src) {
            nonComputedVertices.insert(i.first);
            for (auto v:graph.adjList[src])
                if (v.first == i.first) {
                    distances[i.first] = v.second;
                    break;
                }
        }
    }
    distances[src] = 0;
    v.push_back(src);
    while (!nonComputedVertices.empty()){
        //std::cout<<"NonComputed still not empty. size: "<<nonComputedVertices.size()<<std::endl;
        //Node* index = src;
        int index = src;
        int smallestVal = INT_MAX;

        for (auto v:nonComputedVertices)
            if (distances[v]<smallestVal){
                index = v;
                smallestVal = distances[v];
            }
        nonComputedVertices.erase(index);
        computedVertices.insert(index);
        v.push_back(index);
        for (auto v:graph.adjList[index]){
            if (distances[index]+v.second<distances[v.first]) {
                distances[v.first] = distances[index]+v.second;
                predecessors[v.first] = index;
            }
        }
        if (computedVertices.find(endNode)!=computedVertices.end()) {
            //return v;
            break;
        }
    }

    int checkNode = endNode;
    std::vector<int> r;

    while (predecessors[checkNode]!=src){
        r.push_back(predecessors[checkNode]);
        checkNode = predecessors[checkNode];
    }

    std::reverse(v.begin(), v.end());

    return std::make_pair(v, r);
}

/*double findH(Node* node1, Node* node2){ //sqrt((x-x2)^2  + (y-y2)^2 + (z-z2)^2) finding the distance between two points
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
    double result = sqrt(xSquared+ySquared+zSquared);
    return result;
}

vector <Node*> a_star(Graph& graph, Node* start_node, Node* target_node) { //parameters: graph, start_node, target_node
    std::cout<<std::endl<<"TargetNode: "<<target_node->xPos<<", "<<target_node->yPos<<", "<<target_node->zPos<<std::endl;
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
            if (current->xPos == target_node->xPos && current->yPos==target_node->yPos&&current->zPos==target_node->zPos) {

                finished = true;
                //copying data to visited map
                visited.insert(current);
                v.push_back(current);
                return v;
            }
            else {
                for (auto iter:graph.adjList[current]) { //something might get destroyed here
                    Node* neighbor = iter.first;
                    if (visited.find(neighbor)==visited.end()) { //if not in visited map
                        tempG = current->g_score+graph.adjList[current][neighbor]; //weight to travel to the neighbor

                        if (tempG<neighbor->g_score) { //the weight to travel is less than the weight to travel to the neighbor
                            neighbor->g_score = tempG;
                            neighbor->f_score = tempG+findH(neighbor, target_node);
                            neighbor->prev = current;
                            if (neighbor->aSeen==false) {
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
}*/

int main(){

    auto start = std::chrono::high_resolution_clock::now();

    std::cout<<"Initializing Graph...\n";

    Graph g;
    g.InitializeGraph();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    std::cout<<"Graph initialized with 1000 nodes. Took "<<duration.count()<<" milliseconds.\n";

    std::cout<<"Calculating shortest path with Dijkstra...\n";

    start = std::chrono::high_resolution_clock::now();

    //vector<Node*> aPath = a_star(g, g.getStartNode(), g.getEndNode());
    std::pair<std::vector<int>, std::vector<int>> dPath = dijkstra(g, 0, 999);

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    std::cout<<"Shortest path found with length "<<dPath.second.size()<<". Took "<<duration.count()<<" milliseconds.\n";

    std::vector<wallToBuild*> walls;

    std::cout<<"Building walls of maze...\n";

    start = std::chrono::high_resolution_clock::now();

    for (auto v:g.adjList){
        for (auto p:v.second){
            if(g.GetX(p.first))
            if (g.GetX(p.first)>g.GetX(v.first))
                walls.push_back(new wallToBuild(g.GetX(v.first)+1, g.GetY(v.first), g.GetZ(v.first), p.second, 0));
            if (g.GetX(p.first)<g.GetX(v.first))
                walls.push_back(new wallToBuild(g.GetX(v.first), g.GetY(v.first), g.GetZ(v.first), p.second, 1));

            if (g.GetY(p.first)>g.GetY(v.first))
                walls.push_back(new wallToBuild(g.GetX(v.first), g.GetY(v.first)+1, g.GetZ(v.first), p.second, 2));
            if (g.GetY(p.first)<g.GetY(v.first))
                walls.push_back(new wallToBuild(g.GetX(v.first), g.GetY(v.first), g.GetZ(v.first), p.second, 3));

            if (g.GetZ(p.first)>g.GetZ(v.first))
                walls.push_back(new wallToBuild(g.GetX(v.first), g.GetY(v.first), g.GetZ(v.first)+1, p.second, 4));
            if (g.GetZ(p.first)<g.GetZ(v.first))
                walls.push_back(new wallToBuild(g.GetX(v.first), g.GetY(v.first), g.GetZ(v.first), p.second, 5));
        }
    }

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    std::cout<<walls.size()<<" walls built. Took "<<duration.count()<<" milliseconds.\n";

    std::cout<<"Starting Render Process...\n";

    start = std::chrono::high_resolution_clock::now();

    Game game(
        walls,
        dPath.first,
        dPath.second,
        "Worm Test",
        800, 600,
        4, 5,
        false);

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    std::cout<<"Rendering Initialized. Took "<<duration.count()<<" milliseconds.\nBeginning render process";

    //MAIN LOOP
    while (!game.getWindowShouldClose()){
        //TODO UPDATE INPUT
        game.update();
        game.render();
    }

    return 0;
}