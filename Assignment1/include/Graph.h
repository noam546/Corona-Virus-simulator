#ifndef GRAPH_H_
#define GRAPH_H_

#include "Tree.h"
#include <vector>
#include <queue>

using namespace std;

class Graph{
public:

    Graph(std::vector<std::vector<int>> matrix);

    vector<int> infected;

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Tree* bfs(Session& session,int rootLabel);

    vector<vector<int>> getEdges() const;
    void setEdges(int row, int col,int value);
    vector<int>& getInfected();
    void setInfected(int nodeInd);



private:
    vector<std::vector<int>> edges;
};

#endif
