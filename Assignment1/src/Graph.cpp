#include "../include/Session.h"
#include "../include/Graph.h"
#include <iostream>
using namespace std;

Graph::Graph(vector<vector<int>> matrix): infected() , edges(matrix){}

void Graph::infectNode(int nodeInd) {
    edges[nodeInd][nodeInd]=-1;
}

bool Graph::isInfected(int nodeInd) {
    return (edges[nodeInd][nodeInd]== -1);
}
Tree* Graph::bfs(Session &session, int rootLabel) {
    //creating a tree with the starting node rootLabel
    Tree* currTree = Tree::createTree(session,rootLabel);
    //reading the graph from the session
    queue<Tree*> nodeQueue;
    //starting node enter to the queue
    nodeQueue.push(currTree);
    bool isVisited[edges.size()];
    //initialize the bool array
    for(int i = 0 ; i < (int)edges.size(); i++){
        isVisited[i] = false;
    }
    isVisited[currTree->getNode()] = true;
    //starting the bfs "traveling"
    while(!nodeQueue.empty()){
        Tree* nextTree = nodeQueue.front();
        nodeQueue.pop();
        int childrenCounter = 0;
        //searching for nextTree neighbors
        for(int i = 0; i < (int)edges.size(); i++){
            if(edges[nextTree->getNode()][i] == 1 && !isVisited[i]){
                isVisited[i] = true;
                Tree* newTree = Tree::createTree(session,i);
                nextTree->addChild(*newTree);
                nodeQueue.push(nextTree->getChild(childrenCounter));
                childrenCounter++;
                delete (newTree);
            }
        }
    }
    return currTree;
}

//getters and setters
vector<vector<int>> Graph::getEdges() const {
    return edges;
}
void Graph::setEdges(int row, int col,int value) {
    edges[row][col] = value;
}
vector<int>& Graph::getInfected() {
    return infected;
}
void Graph::setInfected(int nodeInd){
    infected.push_back(nodeInd);
}

