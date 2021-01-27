
#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();
    virtual Agent* clone()const =0 ;
    virtual void act(Session& session)=0;
    virtual ~Agent();
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session& session);
    virtual Agent* clone()const;

};


class Virus: public Agent{
public:
    Virus(int nodeInd);

    virtual Agent* clone()const;
    virtual void act(Session& session);
    int getNodeInd();
private:
    const int nodeInd;
    int nextNeighbor;
    bool active;
};

#endif
