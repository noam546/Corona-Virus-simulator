
#include "../include/Session.h"
#include <fstream>
#include <vector>
#include <utility>
#include <iostream>
#include "../include/Graph.h"
#include "../include/Agent.h"
#include "../include/json.hpp"


using namespace std;

Session::Session(const string &path):g(vector<vector<int>>()),treeType(),agents(){
    nlohmann::json readInput;
    ifstream readInput_file(path);
    readInput_file >> readInput;
    vector<vector<int>> matrix = readInput["graph"];
    g = Graph(matrix);
    if(readInput["tree"]=="C")
        treeType = Cycle;
    if(readInput["tree"]=="M")
        treeType = MaxRank;
    if(readInput["tree"]=="R")
        treeType = Root;
    for(auto& ref : readInput["agents"]){
        if(ref[0] == "V") {
            Virus newVirus = Virus(ref[1]);
            addAgent(newVirus);
            g.setEdges(ref[1],ref[1],-2);
            activeViruses++;
        }
        else{
            ContactTracer newAgent = ContactTracer();
            addAgent(newAgent);
        }
    }


}
//-----------------------Rule of five
//copy constructor
Session::Session(const Session &other)
:activeViruses(other.activeViruses),nextBfsStarting(other.nextBfsStarting),currCycle(other.currCycle),g(other.g),treeType(other.treeType) , agents(){
    for(Agent* currAgent: other.agents){
        Agent* newAgent(currAgent);
        agents.push_back(newAgent);
    }
}
//move constructor
Session::Session(Session &&other)
:activeViruses(other.activeViruses),nextBfsStarting(other.nextBfsStarting),currCycle(other.currCycle),g(other.g),treeType(other.treeType),agents() {
    for(Agent* currAgent: other.agents){
        Agent* newAgent(currAgent);
        agents.push_back(newAgent);
        delete (currAgent);
    }
}
//destructor
Session::~Session() {
    for(Agent* i: agents){
        delete(i);
    }
}
//Assignment operator
Session& Session::operator=(const Session &other) {
    if(this != &other){
        for(Agent* curr: agents)
            delete (curr);
        activeViruses = other.activeViruses;
        nextBfsStarting = other.nextBfsStarting;
        currCycle = other.currCycle;
        treeType = other.treeType;
        g = other.g;
        for(Agent* currAgent: other.agents){
            Agent* newAgent(currAgent);
            agents.push_back(newAgent);
        }
    }
    return *this;
}
//move assignment operator
const Session& Session::operator=(Session &&other) {
    if(this != &other){
        for(Agent* curr: agents)
            delete (curr);
        activeViruses = other.activeViruses;
        nextBfsStarting = other.nextBfsStarting;
        currCycle = other.currCycle;
        treeType = other.treeType;
        g = other.g;

        for(Agent* currAgent: other.agents){
            Agent* newAgent(currAgent);
            agents.push_back(newAgent);
        }
        other.agents.~vector();
    }
    return *this;
}



//----------------------------functions
void Session::simulate() {
    while(activeViruses != 0){
        int numOfAgents = agents.size();
        for(int i=0;i<numOfAgents;i++)
        {
            Agent *newAgent=agents[i];
            newAgent->act(*this);
        }
        currCycle++;
    }
    for(int i = 0; i < (int)g.getEdges().size(); i++)
        g.setEdges(i,i,0);
    nlohmann::json writeOutput;
    writeOutput["graph"] = g.getEdges();
    writeOutput["infected"] = g.getInfected();
    ofstream output("output.json");
    output << writeOutput;
}
void Session::addAgent(const Agent &agent) {
    Agent* copy = agent.clone();
    agents.push_back(copy);

}
void Session::enqueueInfected(int nodeInd) {
    g.infected.push_back(nodeInd);
    setGraph(g);
}
int Session::dequeueInfected() {
    int output = -1;
    if(nextBfsStarting < (int)g.getInfected().size()){
        output = g.getInfected()[nextBfsStarting];
        nextBfsStarting++;
    }
    return output;
}

//getters and setters
void Session::setGraph(const Graph &graph) {
    g = graph;
    g.infected=graph.infected;
}
Graph& Session::getGraph() {
    return g;
}
void Session::setActiveViruses(int sign) {
    if(sign == -1)
        activeViruses--;
    else
        activeViruses++;

}
TreeType Session::getTreeType() const {
    return treeType;
}
int Session::getCurrCycle() const {
    return currCycle;
}




