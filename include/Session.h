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
    Session&operator=(Session&&);//move assignment
    ~Session();//destructor

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    Graph& getGraphReference();
    void enqueueInfected(int);
    void SetInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infected;
};

#endif