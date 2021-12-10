#include "Game.h"
#include "Graph.h"
#include "wallToBuild.h"

int main(){

    Graph g;
    g.InitializeGraph();

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

    for (auto v:walls){
        std::cout<<"Wall: "<<v->x<<", "<<v->y<<", "<<v->z<<", "<<v->w<<std::endl;
    }

    //g.TestGraph();
    /*for (std::pair<Node*, std::unordered_map<Node*, int>> p:g.getAdjList()){

    }*/
    /*Node* endNode = g.getEndNode();
    std::cout<<"EndNode ("<<endNode->xPos<<", "<<endNode->yPos<<", "<<endNode->zPos<<") has surrounding nodes at ";
    for (auto v:g.adjList[endNode]){
        if(v.first!=nullptr)
            std::cout<<"("<<v.first->xPos<<", "<<v.first->yPos<<", "<<v.first->zPos<<"). ";
    }*/

    Game game(
        walls,
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