#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();
    virtual Agent* clone()=0;
    virtual void act(Session& session)=0;
    virtual ~Agent()=default; //check

//protected:
//    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual Agent* clone();
    virtual void act(Session& session);
};

class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual Agent* clone();
    virtual void act(Session& session);

protected:
    const int nodeInd;
};

#endif