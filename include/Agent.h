#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Agent{
public:
    Agent();
    virtual Agent* clone()=0;
    virtual void act(Session& session)=0;

//protected:
//    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    
    virtual void act(Session& session);

protected:
    const int nodeInd;
};

#endif
