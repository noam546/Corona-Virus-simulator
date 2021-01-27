#include "../include/Session.h"
#include "../include/Tree.h"
#include <queue>
#include <vector>

using namespace std;
//----------------------------Tree-----------------------------
Tree::Tree(int rootLabel): node(rootLabel),isInsereted(false), children(){}
//-----------------------Rule of five
//copy constructor
Tree::Tree(const Tree &other):node(other.node), isInsereted(other.isInsereted), children() {
    for(Tree* currTree: other.children){
        children.push_back(currTree->clone());
    }
}
//move constructor
Tree::Tree(Tree &&other):node(other.node), isInsereted(other.isInsereted), children() {
    for(Tree* currTree: other.children){
        Tree* newTree(currTree);
        children.push_back(newTree);
        delete (currTree);
    }
    other.children.clear();
}
//destructor
Tree::~Tree() {
    clear();
}
//assignment operator
Tree & Tree::operator=(const Tree &other) {
    if(this != &other){
        this->clear();
        for(Tree* curr:children)
            delete (curr);
        node = other.node;
        children=other.children;
    }
    return *this;
}
//move assignment operator
Tree& Tree::operator=(Tree &&other) {
    if(&other != this){
        this->clear();
        node = other.node;
        children = other.children;
        other.clear();
    }
    return *this;
}
void Tree::clear() {
    for(auto *i: children){
        delete i;
    }
    children.clear();
}
//----------------------------functions
void Tree::addChild(const Tree &child) {
    Tree* copyChild = child.clone();
    int counter = 0 ;
    for(Tree* iter : children){
        if(iter-> node >copyChild->node)
            break;
        else
            counter++;
    }
    children.insert(children.begin()+counter , copyChild);
}

Tree* Tree::createTree(const Session &session, int rootLabel) {
    if(session.getTreeType() == MaxRank){
        return new MaxRankTree(rootLabel);
    }
    if(session.getTreeType() == 2){
        return new RootTree(rootLabel);
    }
    else{
        int currCycle = session.getCurrCycle();
        return new CycleTree(rootLabel,currCycle);
    }
}

//getters and setters
int Tree::getNode() const {
    return node;
}
vector<Tree*> Tree::getChildren() const {
    return children;
}
Tree* Tree::getChild(int childInd) {
    return children[childInd];
}
bool Tree::isInserted()const {
    return isInsereted;
}
void Tree::setIsInserted() {
    isInsereted = true;
}


//----------------------------Cycle Tree-----------------------------
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle) {};
CycleTree* CycleTree::clone() const{
    return new CycleTree(*this);
}
int CycleTree::traceTree() {
    Tree *temp = this;
    for(int i = 0; i != currCycle; i++){
        if(!temp->getChildren().empty())
            temp = temp->getChild(0);
        else
            break;
    }
    int output = temp->getNode();
    return output;
}

//----------------------------Max Rank Tree-----------------------------
MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel) {};
MaxRankTree* MaxRankTree::clone()const{
    return new MaxRankTree(*this);
}
int MaxRankTree::traceTree() {
    int maxRankNode = -1;
    int maxRank = -1;
    Tree* temp = this;
    queue<Tree*> nodeQueue;
    nodeQueue.push(temp);
    temp->setIsInserted();
    while(!nodeQueue.empty()){
        Tree* currTree = nodeQueue.front();
        nodeQueue.pop();
        for(Tree* child: currTree->getChildren()){
            if(!child->isInserted()){
                child->setIsInserted();
                nodeQueue.push(child);
            }
        }
        int currTreeRank = currTree->getChildren().size();
        //if the currTree rank is higher
        if(currTreeRank > maxRank){
            maxRank = currTreeRank;
            maxRankNode = currTree->getNode();
        }
    }
    return maxRankNode;
}

//----------------------------Root Tree-----------------------------
RootTree::RootTree(int rootLabel): Tree(rootLabel) {};
RootTree* RootTree::clone()const{
    return new RootTree(*this);
}
int RootTree::traceTree() {
    return getNode();
}