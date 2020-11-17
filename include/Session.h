#ifndef SESSION_H_
#define SESSION_H_
//RULE OF FIVE
#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
using namespace std;

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:

    Session(const std::string &path);//constructor
    Session(const Session&);//copy constructor
    Session& operator=(const Session&);//copy assignment
    Session(Session&&);//move constructor
    Session& operator=(Session&&);//move assignment
    virtual ~Session();//destructor

    void simulate();
    void addAgent(const Agent&);
    void setGraph(const Graph& graph);
    Graph& getGraphReference();
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getNumOfCycle() const;
    bool isFinished();
    bool isAgent(int);
    std::vector<Agent*> getAgents();
private:
    Graph g;
    int cycleNum;
    TreeType treeType;
    std::vector<Agent*> agents;
};

#endif