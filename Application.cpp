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
using namespace std;


////inspired by Aman's pseudocode
////Following PseudoCode from slides using 2set and 2array method
//vector<int> dijkstra(Graph& graph, Node* src) {
//    int numVertices = 4 * 4 * 4;
//    unordered_set<Node*> computedVertices = {src}, nonComputedVertices;
//    vector<int> distances(numVertices, 2147483647);
//    vector<Node*> predecessor;
//    for(auto i : graph.adjList)
//        if(i.first!=src){
//            nonComputedVertices.insert(i.first);
//            for(auto v : graph.adjList[src])
//                if(v.first == i.first){
//                    distances[i] = v.second;
//                    break;
//                }
//        }
//    distances[src] = 0;
//    while(!nonComputedVertices.empty()){
//        Node* index = src;
//        int smallestVal = 2147483647;
//        for (auto v:nonComputedVertices)
//            if (distances[v]<smallestVal){
//                index = v;
//                smallestVal = distances[v];
//            }
//        nonComputedVertices.erase(index);
//        computedVertices.insert(index);
//        for(auto v : graph.adjList[index])
//            if(distances[index] + v.second < distances[v.first]){
//                distances[v.first] = distances[index] + v.second;
//                predecessor[v.first] = index;
//            }
//    }
//    return distances;
//}



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
    double result = sqrt(xSquared+ySquared+zSquared);
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
            cout<<"wtf"<<endl;
            finished = true;
        }
        else {
            current = unvisited.top();
            unvisited.pop();
            if (current==target_node) {
                cout<<"hello"<<endl;
                finished = true;
                //copying data to visited map
                visited.insert(current);
                v.push_back(current);
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
}

int main(){

    Graph g;
    g.InitializeGraph();

    vector <Node*> path = a_star(g, g.getStartNode(), g.getEndNode());
    for (auto iter:path) {
        cout<<iter->xPos<<" "<<iter->yPos<<" "<<iter->zPos<<endl;
    }
    cout<<path.size();

    std::vector<wallToBuild*> walls;

    for (auto v:g.adjList){
        for (auto p:v.second){
            if (p.first->xPos>v.first->xPos)
                walls.push_back(new wallToBuild(v.first->xPos+1, v.first->yPos, v.first->zPos, p.second, 0));
            if (p.first->xPos<v.first->xPos)
                walls.push_back(new wallToBuild(v.first->xPos, v.first->yPos, v.first->zPos, p.second, 1));

            if (p.first->yPos>v.first->yPos)
                walls.push_back(new wallToBuild(v.first->xPos, v.first->yPos+1, v.first->zPos, p.second, 2));
            if (p.first->xPos<v.first->xPos)
                walls.push_back(new wallToBuild(v.first->xPos, v.first->yPos, v.first->zPos, p.second, 3));

            if (p.first->xPos>v.first->xPos)
                walls.push_back(new wallToBuild(v.first->xPos, v.first->yPos, v.first->zPos+1, p.second, 4));
            if (p.first->xPos<v.first->xPos)
                walls.push_back(new wallToBuild(v.first->xPos, v.first->yPos, v.first->zPos, p.second, 5));
        }
    }

    /*for (auto v:walls){
        std::cout<<"Wall: "<<v->x<<", "<<v->y<<", "<<v->z<<", "<<v->w<<std::endl;
    }*/

    std::cout<<std::endl<<"From Main: Path.size(): "<<path.size()<<std::endl;

    Game game(
        walls,
        path,
        "Worm Test",
        1600, 1080,
        4, 5,
        false);

    //MAIN LOOP
    while (!game.getWindowShouldClose()){
        //TODO UPDATE INPUT
        game.update();
        game.render();
    }

    return 0;
}