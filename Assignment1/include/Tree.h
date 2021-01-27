#ifndef TREE_H_
#define TREE_H_


#include <vector>
using namespace std;
class Session;

class Tree{

public:
    ////constructors and destructors
    Tree(int rootLabel);
    Tree(const Tree &other);
    Tree(Tree &&other);
    virtual ~Tree();
    Tree& operator=(const Tree& other);
    Tree& operator=(Tree &&other);
    void clear();

    ////functions
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual Tree* clone()const = 0;
    virtual int traceTree()=0;

    ////getters and setters
    int getNode()const;
    vector<Tree*> getChildren()const;
    Tree* getChild(int childInd);
    bool isInserted()const;
    void setIsInserted();


protected:
    int node;
    bool isInsereted = false;
    vector<Tree*> children;

};


class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual CycleTree* clone()const;
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual MaxRankTree* clone()const;
    virtual int traceTree();


};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual RootTree* clone()const;
    virtual int traceTree();
};

#endif
