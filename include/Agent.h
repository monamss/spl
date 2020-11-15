#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();
    virtual Agent* clone() const=0;
    virtual void act(Session& session)=0;
    virtual ~Agent()=default; //check
    virtual int getNodeInd()=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual Agent* clone() const;
    virtual void act(Session& session);
    virtual int getNodeInd();

private:
    const int nodeInd;
};

class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual Agent* clone() const;
    virtual void act(Session& session);
    virtual int getNodeInd();

private:
    const int nodeInd;
};

#endif