#include "../include/Agent.h"
#include <iostream>
using namespace std;
//----------------------------Agent-----------------------------
Agent::Agent() {}
Agent::~Agent() noexcept {}

//----------------------------ContactTracer-----------------------------
ContactTracer::ContactTracer():Agent(){}
void ContactTracer::act(Session &session) {
    int vertixToIsolate = session.dequeueInfected();
    Graph g=session.getGraph();
    if(vertixToIsolate != -1){
        Tree* myTree = session.getGraph().bfs(session,vertixToIsolate);
        vertixToIsolate = myTree->traceTree();
        delete myTree;
        for (int i = 0; i < (int)g.getEdges().size(); ++i) {
            if( i != vertixToIsolate){
                g.setEdges(vertixToIsolate,i,0);
                g.setEdges(i,vertixToIsolate,0);
            }
        }
        session.setGraph(g);
    }

}
Agent* ContactTracer::clone()const{
    return new ContactTracer(*this);
}


//----------------------------Virus-----------------------------
Virus::Virus(int nodeInd): nodeInd(nodeInd),nextNeighbor(0), active(true){}
Agent* Virus::clone() const{
    return new Virus(*this);
}
void Virus::act(Session& session){
        if (active){
            Graph g=session.getGraph();
            vector<vector<int>> edges = session.getGraph().getEdges();
            if (!g.isInfected(nodeInd)) {
                g.infectNode(nodeInd);
                g.infected.push_back(nodeInd);
                session.setGraph(g);
            }
            bool foundNeighbor = false;
            int numOfvertex = session.getGraph().getEdges().size();
            while (numOfvertex > nextNeighbor && !foundNeighbor) {
                if (edges[nodeInd][nextNeighbor] == 1) {
                    if (edges[nextNeighbor][nextNeighbor] == 0) {
                        Virus newVirus = Virus(nextNeighbor);
                        session.addAgent(newVirus);
                        session.setActiveViruses(1);
                        session.getGraph().setEdges(nextNeighbor, nextNeighbor, -2);
                        foundNeighbor = true;
                    }
                }
                nextNeighbor++;
            }
            if (!foundNeighbor) {
                active = false;
                session.setActiveViruses(-1);
            }

        }

}
int Virus::getNodeInd() {
    return nodeInd;
}
