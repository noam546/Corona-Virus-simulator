#ifndef SESSION_H_
#define SESSION_H_

#include "Graph.h"
#include "json.hpp"
#include <vector>
#include <string>


using json=nlohmann:: json;

using namespace std;

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session {
public:


    Session(const std::string &path);
    Session(const Session &other);
    Session(Session &&other);
    virtual ~Session();
    Session& operator=(const Session &other);
    const Session& operator=(Session &&other);

    void simulate();
    void addAgent(const Agent &agent);
    void enqueueInfected(int);
    int dequeueInfected();

    ////getters and setters
    void setGraph(const Graph &graph);
    Graph& getGraph();
    void setActiveViruses(int sign);
    TreeType getTreeType() const;
    int getCurrCycle() const;



private:
    int activeViruses = 0;
    int nextBfsStarting = 0;
    int currCycle = 0;
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
};

#endif
